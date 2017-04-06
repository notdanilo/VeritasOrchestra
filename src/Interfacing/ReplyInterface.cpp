#include <Veritas/Orchestra/Interfacing/ReplyInterface.h>
#include <Veritas/Orchestra/LocalModule.h>

using namespace Veritas;
using namespace Orchestra;
using namespace Interfacing;
using namespace Messaging;

using namespace Data;

#warning Beautify lambda capture.

ReplyInterface::ReplyInterface(const String &name, Callback callback)
    : Interface(name)
    , callback(callback)
    , inputInterface(String("Request-") + name, [this](const Message& message) { Request(message); })
    , outputInterface(String("Reply-") + name)
{}
ReplyInterface::ReplyInterface(const ReplyInterface &copy)
    : Interface(copy)
    , callback(copy.callback)
    , inputInterface(copy.inputInterface.getName(), [this](const Message& message) { Request(message); })
    , outputInterface(copy.outputInterface)
{}
ReplyInterface::ReplyInterface(ReplyInterface &&move)
    : Interface(std::move(move))
    , callback(std::move(move.callback))
    , inputInterface(std::move(move.inputInterface))
    , outputInterface(std::move(move.outputInterface))
{
    inputInterface = InputInterface(inputInterface.getName(), [this](const Message& message) { Request(message); });
}
ReplyInterface::~ReplyInterface() {}

void ReplyInterface::onSet(Interfacer *interfacer) {
    interfacer->set("Input", (InputInterface) inputInterface);
    interfacer->set("Output", (OutputInterface) outputInterface);
}

void ReplyInterface::Request(const Message &message) {
    if (callback) callback(Message(message).set(message.get("Content")), Replier(message));
}
