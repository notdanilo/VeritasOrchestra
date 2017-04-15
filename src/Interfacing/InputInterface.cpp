#include <Veritas/Orchestra/Interfacing/InputInterface.h>
#include <Veritas/Orchestra/Computing/LocalModule.h>

using namespace Veritas;
using namespace Orchestra;
using namespace Messaging;
using namespace Interfacing;

InputInterface::InputInterface(const String &name, Callback callback) : Interface(name), callback(callback) {}
InputInterface::InputInterface(const InputInterface &copy) : Interface(copy), callback(copy.callback) {}
InputInterface::InputInterface(InputInterface &&move) : Interface(std::move(move)), callback(std::move(move.callback)) {}
InputInterface::~InputInterface() {}

InputInterface& InputInterface::operator=(const InputInterface& copy) {
    Interface::operator=(copy);
    callback = copy.callback;
}

InputInterface& InputInterface::operator=(InputInterface&& move) {
    Interface::operator=(std::move(move));
    callback = std::move(move.callback);
}

void InputInterface::receive(const Message& message) const {
    if (callback) callback(message);
}
