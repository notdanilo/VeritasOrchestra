#include <Veritas/Orchestra/Interfacing/InputInterface.h>
#include <Veritas/Orchestra/LocalModule.h>

using namespace Veritas;
using namespace Orchestra;
using namespace Messaging;
using namespace Interfacing;

InputInterface::InputInterface(const String &name, LocalModule *module, Callback callback) : Interface(name, module), callback(callback) {
    module->set(this);
}
InputInterface::InputInterface(InputInterface &&move) : Interface(std::move(move)), callback(std::move(move.callback)) {}
InputInterface::~InputInterface() {
    getModule()->unset(this);
}

void InputInterface::receive(const Message &message) { if (callback) callback(message); }
