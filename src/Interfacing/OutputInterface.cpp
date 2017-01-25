#include <Veritas/Orchestra/Interfacing/OutputInterface.h>
#include <Veritas/Orchestra/LocalModule.h>

using namespace Veritas;

using namespace Orchestra;
using namespace Messaging;
using namespace Interfacing;

using namespace Data;

OutputInterface::OutputInterface(const String &name, LocalModule* module) : Interface(name, module) {}
OutputInterface::OutputInterface(OutputInterface &&move) : Interface(std::move(move)) {}
OutputInterface::~OutputInterface() {}

#warning Origin construction has its own complexity on publishing
void OutputInterface::publish(const Message &message) const {
    //for (auto m: connections) send(m, Message(message));
}

void OutputInterface::send(const Address &address, const Message& message) const { send(Module(address), message); }
void OutputInterface::send(const Module* module, const Message& message) const { send(*module, message); }
void OutputInterface::send(const Module& module, const Message& message) const {
    // Implement proper routing mechanism
    Buffer buffer = Encoding::Base16().decode(module.getAddress().getString());
    LocalModule* localmodule = (LocalModule*) *(uintptr_t*) buffer.getData();
    localmodule->receive(Message().setInterface(getName())
                         .setOrigin(getModule()->getAddress())
                         .setDestiny(module.getAddress())
                         .set(message.getContent()));
}
