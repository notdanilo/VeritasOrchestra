#include <Veritas/Orchestra/Interfacing/ReplyInterface.h>
#include <Veritas/Orchestra/LocalModule.h>

using namespace Veritas;
using namespace Orchestra;
using namespace Interfacing;
using namespace Messaging;

using namespace Data;

ReplyInterface::ReplyInterface(const String &name, Callback callback)
    : Interface(name),
      callback(callback),
      inputInterface(String("Request-") + name, [this](const Message& message) { Request(message); }),
      outputInterface(String("Reply-") + name) {}
ReplyInterface::ReplyInterface(ReplyInterface &&move)
    : Interface(std::move(move)),
      callback(std::move(callback)),
      inputInterface(std::move(move.inputInterface)),
      outputInterface(std::move(move.outputInterface)) {}
ReplyInterface::~ReplyInterface() {}

void ReplyInterface::Request(const Message &message) {
    uint32 requestID = (Number) message.get("RequestID");
    addresses.emplace(requestID, message.getOrigin());
    if (callback) callback(Message(message).set(message.get("Content")), Context(requestID));
}

/*
void ReplyInterface::reply(uint32 requestID, const Message& message) {
    try {
        const Address& address = addresses.at(requestID);
        outputInterface.send(address, Message().set("RequestID", requestID).set("Content", message.getContent()));
        addresses.erase(requestID);
    } catch (...) {}
}
*/
