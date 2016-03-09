#ifndef __MSGOBSEVER_H__
#define __MSGOBSEVER_H__

class IMsgObsever
{
public:
    virtual unsigned long Notify(unsigned int id,void *wparam,void *lparam) = 0;
};

class IMsgMgr
{
public:
    virtual bool RegMsg(unsigned int id,IMsgObsever *obj,bool regist = true) = 0;
    virtual long SendMsg(unsigned int id,void *wparam = NULL,void *lparam = NULL) = 0;
    virtual void PostMsg(unsigned int id,void *wparam = NULL,void *lparam = NULL) = 0;
};

#endif
