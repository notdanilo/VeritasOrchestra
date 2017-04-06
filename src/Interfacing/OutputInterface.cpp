#include <Veritas/Orchestra/Interfacing/OutputInterface.h>
#include <Veritas/Orchestra/LocalModule.h>
#include <Veritas/Orchestra/ModuleManager.h>

using namespace Veritas;

using namespace Orchestra;
using namespace Messaging;
using namespace Interfacing;

using namespace Data;

OutputInterface::OutputInterface(const String& name) : Interface(name) {}
OutputInterface::OutputInterface(const OutputInterface &copy) : Interface(copy) {}
OutputInterface::OutputInterface(OutputInterface &&move) : Interface(std::move(move)) {}
OutputInterface::~OutputInterface() {}

void OutputInterface::send(const LocalModule *origin, const Module *destiny, const Message &message) const { send(*origin, *destiny, message); }
void OutputInterface::send(const LocalModule &origin, const Module *destiny, const Message &message) const { send(origin, *destiny, message); }
void OutputInterface::send(const LocalModule *origin, const Module &destiny, const Message &message) const { send(*origin, destiny, message); }
void OutputInterface::send(const LocalModule &origin, const Module &destiny, const Message &message) const {
    ModuleManager::messageQueue.receive(Message().setInterface(getName())
                                                .setOrigin(origin.getAddress())
                                                .setDestiny(destiny.getAddress())
                                                .set(message.getContent()));
}
