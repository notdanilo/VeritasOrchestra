#include <Veritas/Orchestra/Interfacing/ReplyInterface.h>
#include <Veritas/Orchestra/LocalModule.h>

using namespace Veritas;
using namespace Orchestra;
using namespace Interfacing;
using namespace Messaging;

using namespace Data;

ReplyInterface::ReplyInterface(const String &name, LocalModule *module, RequestCallback requestCallback, ReplyCallback replyCallback)
    : Interface(name, module),
      requestCallback(requestCallback),
      replyCallback(replyCallback),
      inputInterface(name, module, [this](const Message& message) { Request(message); }),
      outputInterface(name, module, [this](Message& message) { Reply(message); }) {}
ReplyInterface::ReplyInterface(ReplyInterface &&move)
    : Interface(std::move(move)),
      requestCallback(std::move(requestCallback)),
      replyCallback(std::move(replyCallback)),
      inputInterface(std::move(move.inputInterface)),
      outputInterface(std::move(move.outputInterface)) {}
ReplyInterface::~ReplyInterface() {}

void ReplyInterface::Request(const Message &incoming) {
    Message originalMessage = incoming;
    originalMessage.set(incoming.get("OriginalContent"));

    uint32 requestID = (Number) incoming.get("RequestID");
    if (requestCallback) requestCallback(originalMessage, contextes[requestID]);
    Message message = Message().set(requestID);
    outputInterface.send(incoming.getOrigin(), message);
}

void ReplyInterface::Reply(Message &message) {
    uint32 requestID = (Number) message.getContent();
    Message originalMessage;
    if (replyCallback) replyCallback(originalMessage, contextes[requestID]);
    contextes.erase(requestID);

    message.set(Form().set("RequestID", requestID).set("OriginalContent", originalMessage.getContent()));

}
