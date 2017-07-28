#ifndef __REMOTE_GATT_H__
#define __REMOTE_GATT_H__

#include "LGATTServer.h"


class ACState
{
public:
	boolean power=false;
	int mode=0;
	int temp=26;
	int fan=9;
};

class RemoteGATT : public LGATTService
{
public:
	boolean hasCmd(){return has_cmd;}
	ACState *getState(){has_cmd=false; return &state;}

protected:
    // prepare the data for profile
    virtual LGATTServiceInfo *onLoadService(int32_t index);
    virtual boolean onWrite(LGATTWriteRequest &data);
    virtual boolean onConnection(const LGATTAddress &addr, boolean connected);

    // virtual void setIR(MideaIR &ir);
private:
	boolean has_cmd;
	boolean cmd;
    boolean _connected;
    ACState state;

};


#endif