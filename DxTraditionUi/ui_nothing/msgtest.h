#ifndef MSGTEST_H
#define MSGTEST_H

#include "IMsgObsever.h"


class MsgTest : public IMsgObsever
{
public:
    MsgTest();

    void RegisterMsg(IMsgMgr* obj);

    virtual unsigned long Notify(unsigned int id,void *wparam,void *lparam);
};

#endif // MSGTEST_H
