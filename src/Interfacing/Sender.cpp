#include <Veritas/Orchestra/Interfacing/Sender.h>
#include <Veritas/Orchestra/Computing/LocalModule.h>

using namespace Veritas;
using namespace Orchestra;
using namespace Interfacing;
using namespace Messaging;
using namespace Computing;

using namespace Data;

Sender::Sender(const LocalModule *module) : Sender(*module) {}
Sender::Sender(const LocalModule& module) : module(module) {}

void Sender::send(const String& interface, const Module *destination, const Message &message) const { send(interface, *destination, message); }
void Sender::send(const String& interface, const Module &destination, const Message &message) const {
    const OutputInterface& outputInterface = (const OutputInterface&) module.getClassInterfacer().getInterfaces("Output")->at(interface);
    outputInterface.send(this->module, destination, message);
}

const LocalModule& Sender::getModule() const { return module; }
