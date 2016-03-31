#ifndef MSGDEF
#define MSGDEF

namespace MsgType {

    enum
    {
        Msg_Geometry = 0x0100,
        Msg_InOut = 0x0200,
        Msg_Btn = 0x0300,
        Msg_State = 0x0400
    };

}

namespace Geometry
{
    enum
    {
        ScreenResize = MsgType::Msg_Geometry + 1
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
        KeyDown,
        KeyUp
    };
}

namespace Btn {
    enum
    {
        Back = MsgType::Msg_Btn + 1,
        Home,
        More,
        Full,
        Shake,
        Shot
    };

}

namespace State {
    enum
    {
        Close = MsgType::Msg_State + 1

    };

}


#endif // MSGDEF

