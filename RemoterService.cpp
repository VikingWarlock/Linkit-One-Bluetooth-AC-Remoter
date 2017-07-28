#include "vmbtgatt.h"
#include "RemoterService.h"

#ifdef APP_LOG
#undef APP_LOG
#define APP_LOG(...) Serial.printf(__VA_ARGS__); \
    Serial.println();
#endif


static LGATTServiceInfo g_uart_decl[] =
{
    {TYPE_SERVICE, "0000ffe0-0000-1000-8000-00805f9b3434", TRUE, 0, 0, 0},
    {TYPE_CHARACTERISTIC, "00003434-0000-1000-8000-00805f9b34fb", FALSE, VM_GATT_CHAR_PROP_NOTIFY | VM_GATT_CHAR_PROP_READ|VM_GATT_CHAR_PROP_WRITE, VM_GATT_PERM_READ|VM_GATT_PERM_WRITE, 0}, // tx for periphral; rx for central
    {TYPE_END, 0, 0, 0, 0, 0}

};

void RemoterService::setTempData(float temperature,float humidity){
    inner_temperature=temperature;
    inner_humidity=humidity;
}

// uint16_t RemoterService::getHandle(int32_t type)
// {
//     if (0 == type)
//     {
//         return _handle_notify;
//     }
//     else if (1 == type)
//     {
//         return _handle_write;
//     }

//     return 0;
// }

// prepare the data for profile
LGATTServiceInfo *RemoterService::onLoadService(int32_t index)
{
    
    return g_uart_decl;
}

// characteristic added
boolean RemoterService::onCharacteristicAdded(LGATTAttributeData &data)
{
    const VM_BT_UUID *uuid = &(data.uuid);
    APP_LOG("LGATTSUart::onCharacteristicAdded f[%d] uuid[12] = [0x%x] len[%d]", data.failed, uuid->uuid[12], uuid->len);
    if (!data.failed)
    {
        if (0x7E == uuid->uuid[12])
        {
            _handle_notify = data.handle;
        }
        else if (0x7F == uuid->uuid[12])
        {
            _handle_write = data.handle;
        }
        
    }
    return true;
}
// connected or disconnected
boolean RemoterService::onConnection(const LGATTAddress &addr, boolean connected)
{
    _connected = connected;
    APP_LOG("LGATTSUart::onConnection connected [%d], [%x:%x:%x:%x:%x:%x]", _connected, 
        addr.addr[5], addr.addr[4], addr.addr[3], addr.addr[2], addr.addr[1], addr.addr[0]);


    return true;
}
// read action comming from master
boolean RemoterService::onRead(LGATTReadRequest &request)
{
    APP_LOG("LGATTSUart::onRead _connected [%d]", _connected);
    if (_connected)
    {
        LGATTAttributeValue value = {0};
        uint8_t data[4];
        long t=(long)(inner_temperature*10);
        data[0]=(uint8_t)(t>>8);
        data[1]=(uint8_t)(t&0xff);
        long h=(long)(inner_humidity*10);
        data[2]=(uint8_t)(h>>8);
        data[3]=(uint8_t)(h&0xff);
        memcpy(value.value, data, 4);
        value.len = 4;
        // APP_LOG("LGATTSUart::onRead onRead [%d][%s]", value.len, value.value);
        request.ackOK(value);
        
    }
    return true;
}

void RemoterService::sendNotification(){
        LGATTAttributeValue value = {0};
        uint8_t data[4];
        long t=(long)(inner_temperature*10);
        data[0]=(uint8_t)(t>>8);
        data[1]=(uint8_t)(t&0xff);
        long h=(long)(inner_humidity*10);
        data[2]=(uint8_t)(h>>8);
        data[3]=(uint8_t)(h&0xff);
        memcpy(value.value, data, 4);
        value.len = 4;
    if(sendIndication(value,_handle_notify,false)){
        APP_LOG("Notification sent");
    }else{
        APP_LOG("Notification fail");        
    }
}


// // write action comming from master
// boolean RemoterService::onWrite(LGATTWriteRequest &data)
// {
//     APP_LOG("LGATTSUart::onWrite _connected [%d]", _connected);
//     // todo read UART data.
//     if (_connected)
//     {
//         // if need to rsp to central.
//         if (data.need_rsp)
//         {
//             LGATTAttributeValue value;
//             value.len = 0;
//             data.ackOK();
//         }

//         /*
//         if (data.offset + data.value.len <= ATT_MAX_VALUE_LEN)
//         {
//             _value.len = data.value.len;
//             memcpy(&_value.value, data.value.value + data.offset, data.value.len);
//         }
//         */
//         APP_LOG("central data on peripheral rx[%s][%d]", data.value.value, data.value.len);
//     }
//     return true;
// }



