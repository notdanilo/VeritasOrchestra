#include <Veritas/Orchestra/Interfacing/RequestInterface.h>
#include <Veritas/Orchestra/LocalModule.h>

using namespace Veritas;
using namespace Orchestra;
using namespace Interfacing;
using namespace Messaging;

using namespace Data;

RequestInterface::RequestInterface(const String &name, LocalModule *module)
    : Interface(name, module),
      inputInterface(name, module),
      outputInterface(name, module) {}
RequestInterface::RequestInterface(const RequestInterface& copy)
    : Interface(copy),
      inputInterface(copy.inputInterface),
      outputInterface(copy.outputInterface) {}
RequestInterface::RequestInterface(RequestInterface &&move)
    : Interface(std::move(move)),
      inputInterface(std::move(move.inputInterface)),
      outputInterface(std::move(move.outputInterface)) {}
RequestInterface::~RequestInterface() {}

RequestInterface& RequestInterface::setRequestCallback(std::function<void (Messaging::Message &)> callback) {
    outputInterface.setCallback(callback);
    return *this;
}
RequestInterface& RequestInterface::setReplyCallback(std::function<void (const Messaging::Message &)> callback) {
    inputInterface.setCallback(callback);
    return *this;
}

void RequestInterface::request(const Address &address, Message& message) const { request(Module(address), message); }
void RequestInterface::request(const Address &address, Message&& message) const { request(Module(address), std::move(message)); }
void RequestInterface::request(const Module& module, Message&& message) const { request(module, message); }
void RequestInterface::request(const Module &module, Message &message) const {
    outputInterface.send(module, message);
}
