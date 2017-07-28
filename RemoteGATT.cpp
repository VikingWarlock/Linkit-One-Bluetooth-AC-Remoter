#include "vmbtgatt.h"
#include "RemoteGATT.h"

//IR Control service



static LGATTServiceInfo g_abc_decl[] =
{
    {TYPE_SERVICE, "0000ffe1-0000-1000-8000-00805f9b3434", TRUE, 0, 0, 0},
    {TYPE_CHARACTERISTIC, "00003344-0000-1000-8000-00805f9b34fb", FALSE, VM_GATT_CHAR_PROP_WRITE, VM_GATT_PERM_WRITE, 0},
    {TYPE_END, 0, 0, 0, 0, 0}
};


LGATTServiceInfo *RemoteGATT::onLoadService(int32_t index)
{
    return g_abc_decl;
}


boolean RemoteGATT::onConnection(const LGATTAddress &addr, boolean connected)
{
    _connected = connected;
    APP_LOG("LGATTSUart::onConnection connected [%d], [%x:%x:%x:%x:%x:%x]", _connected, 
        addr.addr[5], addr.addr[4], addr.addr[3], addr.addr[2], addr.addr[1], addr.addr[0]);
    return true;
}

// void RemoteGATT::setIR(MideaIR &ir){
// 	mideaIR=ir;
// }


boolean RemoteGATT::onWrite(LGATTWriteRequest &data){
    if (_connected)
    {
        // if need to rsp to central.
        if (data.need_rsp)
        {
            LGATTAttributeValue value;
            value.len = 0;
            data.ackOK();
        }

        if (data.offset + data.value.len <= 5)
        {
        	LGATTAttributeValue _value;
            _value.len = data.value.len;
            memcpy(&_value.value, data.value.value + data.offset, data.value.len);
			if(_value.value[0]==1&&data.value.len>=4){
				Serial.println("receive cmds");
				// digitalWrite(7,HIGH);
                state.power=true;
                // Serial.print(_value.value[0]);
                state.mode=_value.value[1];
                // Serial.print(_value.value[1]);
                state.fan=_value.value[2];
                // Serial.print(_value.value[2]);
                state.temp=_value.value[3];
                // Serial.print(_value.value[3]);
			    has_cmd=true;
			}else{
				Serial.println("bt cmd 0");
                state.power=false;
				has_cmd=true;
				// digitalWrite(7,LOW);
			}
        }
        APP_LOG("central data on peripheral rx[%s][%d]", data.value.value, data.value.len);
    }
    return true;

}