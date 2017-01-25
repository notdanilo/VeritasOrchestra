#include <Veritas/Orchestra/Interfacing/RequestInterface.h>
#include <Veritas/Orchestra/LocalModule.h>

using namespace Veritas;
using namespace Orchestra;
using namespace Interfacing;
using namespace Messaging;

using namespace Data;

RequestInterface::RequestInterface(const String &name, LocalModule *module, Callback callback)
    : Interface(name, module)
    , requestID(0)
    , callback(callback)
    , inputInterface(String("Reply-") + name, module, [this](const Message& message) { Reply(message); })
    , outputInterface(String("Request-") + name, module) {}
RequestInterface::RequestInterface(RequestInterface &&move)
    : Interface(std::move(move))
    , requestID(std::move(move.requestID))
    , callback(std::move(move.callback))
    , inputInterface(std::move(move.inputInterface))
    , outputInterface(std::move(move.outputInterface)) {}
RequestInterface::~RequestInterface() {}

void RequestInterface::request(const Address &address, const Message& message, const Content& content) { request(Module(address), message, content); }
void RequestInterface::request(const Module* module, const Message& message, const Content& content) { request(*module, message, content); }
void RequestInterface::request(const Module& module, const Message &message, const Content& content) {
    uint32 requestID = getRequestID();

    auto emplace_pair = contextes.emplace(requestID, Context(requestID));
    Context& context = (*emplace_pair.first).second;
    context.setContent(content);

    outputInterface.send(module, Message().set("RequestID", requestID).set("Content", message.getContent()));
}

void RequestInterface::Reply(const Message &message) {
    uint32 requestID = (Number) message.get("RequestID");
    try {
        Context& context = contextes.at(requestID);

        Message originalMessage = message;
        originalMessage.set(message.get("Content"));

        if (callback) callback(originalMessage, context);

        contextes.erase(requestID);
    } catch (...) {}
}

uint32 RequestInterface::getRequestID() { return requestID++; }
