#include <Veritas/Orchestra/Messaging/OutputInterface.h>

using namespace Veritas;
using namespace Orchestra;
using namespace Messaging;

OutputInterface::OutputInterface(const String &name) : Interface(name), callback(0) {}
OutputInterface::OutputInterface(const OutputInterface &copy) : Interface(copy.getName()), callback(copy.callback) {}
#warning How to call parent's move constructor?
OutputInterface::OutputInterface(OutputInterface &&move) : Interface(std::move(move.getName())), callback(std::move(move.callback)) {}
OutputInterface::~OutputInterface() {}

OutputInterface& OutputInterface::setCallback(std::function<void (Message &)> callback) {
    this->callback = callback;
    return *this;
}

void OutputInterface::send(Message &message) { if (callback) callback(message); }
