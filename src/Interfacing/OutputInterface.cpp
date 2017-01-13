#include <Veritas/Orchestra/Interfacing/OutputInterface.h>
#include <Veritas/Orchestra/LocalModule.h>

using namespace Veritas;

using namespace Orchestra;
using namespace Messaging;
using namespace Interfacing;

using namespace Data;

OutputInterface::OutputInterface(const String &name, LocalModule* module) : Interface(name, module), callback(0) {}
OutputInterface::OutputInterface(const OutputInterface &copy) : Interface(copy), callback(copy.callback) {}
OutputInterface::OutputInterface(OutputInterface &&move) : Interface(std::move(move)), callback(std::move(move.callback)) {}
OutputInterface::~OutputInterface() {}

OutputInterface& OutputInterface::setCallback(std::function<void (Message &)> callback) {
    this->callback = callback;
    return *this;
}

#warning Origin construction has its own complexity on publishing
void OutputInterface::publish(Message &&message) const { publish(message); }
void OutputInterface::publish(Message &message) const {
    //for (auto m: connections) send(m, Message(message));
}

void OutputInterface::send(const Address &address, Message& message) const { send(Module(address), message); }
void OutputInterface::send(const Address &address, Message&& message) const { send(Module(address), std::move(message)); }
void OutputInterface::send(const Module& module, Message&& message) const { send(module, message); }
void OutputInterface::send(const Module &module, Message &message) const {
    if (callback) callback(message);

    message.setInterface(getName());
    message.setOrigin(getModule()->getAddress().getString());
    message.setDestiny(module.getAddress().getString());

    // Implement proper routing mechanism
    Buffer buffer = Encoding::Base16().decode(module.getAddress().getString());
    LocalModule* localmodule = (LocalModule*) *(uintptr_t*) buffer.getData();
    localmodule->receive(message);
}
