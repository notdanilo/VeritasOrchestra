#include <Veritas/Orchestra/Interfacing/RequestInterface.h>
#include <Veritas/Orchestra/Computing/LocalModule.h>

using namespace Veritas;
using namespace Orchestra;
using namespace Interfacing;
using namespace Messaging;

using namespace Data;

RequestInterface::RequestInterface(const String& name, Callback callback)
    : Interface(name)
    , callback(callback)
    , outputInterface(String("Request-") + name)
    , inputInterface(String("Reply-") + name, [this](const Message& message) { Reply(message); })
    , requestID(0)
{}
RequestInterface::RequestInterface(const RequestInterface& copy)
    : Interface(copy)
    , callback(copy.callback)
    , outputInterface(copy.outputInterface)
    , inputInterface(copy.inputInterface.getName(), [this](const Message& message) { Reply(message); })
    , contextes(copy.contextes)
    , requestID(copy.requestID)
{}
RequestInterface::RequestInterface(RequestInterface&& move)
    : Interface(std::move(move))
    , callback(std::move(move.callback))
    , outputInterface(std::move(move.outputInterface))
    , inputInterface(std::move(move.inputInterface))
    , contextes(std::move(move.contextes))
    , requestID(std::move(move.requestID))
{
    inputInterface = InputInterface(inputInterface.getName(), [this](const Message& message) { Reply(message); });
}
RequestInterface::~RequestInterface() {}

void RequestInterface::onSet(Interfacer *interfacer) {
    interfacer->set("Output", (OutputInterface) outputInterface);
    interfacer->set("Input", (InputInterface) inputInterface);
}

uint32 RequestInterface::getRequestID() { return requestID++; }

void RequestInterface::request(const LocalModule *origin, const Module *destiny, const Message &message, const any& context) { request(*origin, *destiny, message, context); }
void RequestInterface::request(const LocalModule &origin, const Module *destiny, const Message &message, const any& context) { request(origin, *destiny, message, context); }
void RequestInterface::request(const LocalModule *origin, const Module &destiny, const Message &message, const any& context) { request(*origin, destiny, message, context); }
void RequestInterface::request(const LocalModule &origin, const Module &destiny, const Message &message, const any& context) {
    uint32 requestID = getRequestID();
    contextes.emplace(requestID, context);

    const OutputInterface& outputInterface = (const OutputInterface&) origin.getClassInterfacer().getInterfaces("Output")->at(String("Request-") + getName());
    outputInterface.send(origin, destiny,
                        Message().setOrigin(message.getOrigin())
                                 .setDestiny(message.getDestiny())
                                 .set(Form().set("RequestID", requestID)
                                            .set("Content", message.getContent())));
}

void RequestInterface::Reply(const Message &message) {
    if (callback) {
        try {
            const Form& form = message.getContent();
            uint32 requestID = (Number) form.get("RequestID");
            const any& context = contextes.at(requestID);
            callback(Message().setDestiny(message.getDestiny())
                            .setOrigin(message.getOrigin())
                            .setInterface(message.getInterface())
                            .set(form.get("Content")), context);
            contextes.erase(requestID);
        } catch (...) {}
    }
}
