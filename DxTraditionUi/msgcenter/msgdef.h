#ifndef MSGDEF
#define MSGDEF

namespace MsgType {

    enum
    {
        Msg_Geometry = 0x0100,
        Msg_InOut = 0x0200
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
        KeyDown
    };
}


#endif // MSGDEF

