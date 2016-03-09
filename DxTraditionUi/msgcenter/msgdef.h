#ifndef MSGDEF
#define MSGDEF

namespace MsgType {

    enum
    {
        Msg_Screen = 0x0100,
        Msg_InOut = 0x0200
    };

}


namespace InOut
{
    enum
    {
        StringInput = MsgType::Msg_InOut + 1,
        MousePress,
        MouseRelease,
        MouseMove,
        KeyDown
    };
}


#endif // MSGDEF

