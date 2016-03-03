#ifndef __MSGOBSEVER_H__
#define __MSGOBSEVER_H__

#define DEF_QUI_RCV_VIDEO_DATA		((unsigned int)(0xffffff00))
#define DEF_QUI_RCV_AUDIO_DATA		((unsigned int)(0xffffff01))
#define DEF_QUI_RCV_SRCCAP_VIDEO	((unsigned int)(0xffffff02))

class IMsgObsever
{
public:
	virtual unsigned long Notify(unsigned int auMsgID,void *apWParam,void *apLParam) = 0;
};

class IMsgMgr
{
public:
	virtual bool RegMsg(unsigned int auMsgID,IMsgObsever *apObsever,bool abReg) = 0;
	virtual long SendMsg(unsigned int auMsgID,void *apWParam,void *apLParam) = 0;
	virtual void PostMsg(unsigned int auMsgID,void *apWParam,void *apLParam) = 0;
};

#endif
