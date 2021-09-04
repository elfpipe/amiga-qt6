#ifndef AMIGAMESSAGEHANDLER_H
#define AMIGAMESSAGEHANDLER_H

struct Window;
struct MsgPort;
class AmigaIntuitionMessageHandler {
public:
    virtual void processIntuiMessage(struct IntuiMessage *message) = 0;
    virtual struct Window * intuitionWindow() = 0;
    virtual struct MsgPort * messagePort() = 0;
};
#endif