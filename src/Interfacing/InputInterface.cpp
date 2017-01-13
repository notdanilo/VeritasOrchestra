#include <Veritas/Orchestra/Interfacing/InputInterface.h>

using namespace Veritas;
using namespace Orchestra;
using namespace Messaging;
using namespace Interfacing;

InputInterface::InputInterface(const String &name, LocalModule *module) : Interface(name, module), callback(0) {}
InputInterface::InputInterface(const InputInterface &copy) : Interface(copy), callback(copy.callback) {}
InputInterface::InputInterface(InputInterface &&move) : Interface(std::move(move)), callback(std::move(move.callback)) {}
InputInterface::~InputInterface() {}

InputInterface& InputInterface::setCallback(std::function<void (const Message &)> callback) {
    this->callback = callback;
    return *this;
}

void InputInterface::receive(const Message &message) { if (callback) callback(message); }
