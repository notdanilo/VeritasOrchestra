#include <Veritas/Orchestra/Interfacing/Publisher.h>
#include <Veritas/Orchestra/Computing/LocalModule.h>

using namespace Veritas;
using namespace Orchestra;
using namespace Interfacing;
using namespace Messaging;

Publisher::Publisher(const LocalModule *module) : Sender(module) {}
Publisher::Publisher(const LocalModule& module) : Sender(module) {}

void Publisher::publish(const String& interface, const Message &message) const {
    for (const Module& subscriber : getModule().getSubscribers())
        send(interface, subscriber, message);
}
