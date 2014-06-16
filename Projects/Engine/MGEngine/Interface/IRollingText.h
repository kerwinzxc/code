//**********************************************************************************************************
#ifndef _H_IROLLINGTEXT_
#define _H_IROLLINGTEXT_
//**********************************************************************************************************
#include "MGEngineInterfacePreqs.h"
#include "IWidget.h"
//**********************************************************************************************************
//�����б��ӿ�
namespace MG
{
    class IRollingText
    {
    public:
        virtual IWidget*    getWidget() = 0;

        virtual void        addMsg(Str16 msg, U32 rollingTime, Byte priority) = 0;

    public: //�¼�
        //��������Ϣ��������ϡ�
        virtual void        setEventRollingTextNone(PVOID_CALLBACK pFunc) = 0;

    };
}

//**********************************************************************************************************
#endif
//**********************************************************************************************************