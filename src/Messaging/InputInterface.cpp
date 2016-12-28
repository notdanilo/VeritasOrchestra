#include <Veritas/Orchestra/Messaging/InputInterface.h>

using namespace Veritas;
using namespace Orchestra;
using namespace Messaging;

InputInterface::InputInterface(const String &name) : Interface(name), callback(0) {}
InputInterface::InputInterface(const InputInterface &copy) : Interface(copy.getName()), callback(copy.callback) {}
#warning How to call parent's move constructor?
InputInterface::InputInterface(InputInterface &&move) : Interface(std::move(move.getName())), callback(std::move(move.callback)) {}
InputInterface::~InputInterface() {}

InputInterface& InputInterface::setCallback(std::function<void (const Message &)> callback) {
    this->callback = callback;
    return *this;
}

void InputInterface::receive(const Message &message) { if (callback) callback(message); }
