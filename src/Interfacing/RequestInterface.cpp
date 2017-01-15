#include <Veritas/Orchestra/Interfacing/RequestInterface.h>
#include <Veritas/Orchestra/LocalModule.h>

using namespace Veritas;
using namespace Orchestra;
using namespace Interfacing;
using namespace Messaging;

using namespace Data;

RequestInterface::RequestInterface(const String &name, LocalModule *module, ReplyCallback replyCallback, RequestCallback requestCallback)
    : Interface(name, module),
      requestID(0),
      requestCallback(requestCallback),
      replyCallback(replyCallback),
      inputInterface(name, module, [this](const Message& message) { Reply(message); }),
      outputInterface(name, module, [this](Message& message) { Request(message); }) {}
RequestInterface::RequestInterface(RequestInterface &&move)
    : Interface(std::move(move)),
      requestID(std::move(move.requestID)),
      requestCallback(std::move(move.requestCallback)),
      replyCallback(std::move(move.replyCallback)),
      inputInterface(std::move(move.inputInterface)),
      outputInterface(std::move(move.outputInterface)) {}
RequestInterface::~RequestInterface() {}

void RequestInterface::request(const Address &address, Message& message) const { request(Module(address), message); }
void RequestInterface::request(const Address &address, Message&& message) const { request(Module(address), std::move(message)); }
void RequestInterface::request(const Module& module, Message&& message) const { request(module, message); }
void RequestInterface::request(const Module &module, Message &message) const {
    outputInterface.send(module, message);
}

void RequestInterface::Request(Message &message) {
    if (requestCallback) requestCallback(message, contextes[requestID]);
    uint32 requestID = getRequestID();
    Form form = Form().set("OriginalContent", message.getContent())
                      .set("RequestID", requestID);
    message.set(form);
}

void RequestInterface::Reply(const Message &message) {
    uint32 requestID = (Number) message.get("RequestID");
    Message originalMessage = message;
    originalMessage.set(message.get("OriginalContent"));
    if (replyCallback) replyCallback(originalMessage, contextes[requestID]);
    contextes.erase(requestID);
}

uint32 RequestInterface::getRequestID() { return requestID++; }
