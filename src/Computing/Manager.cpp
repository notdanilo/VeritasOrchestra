#include <Veritas/Orchestra/Computing/Manager.h>
#include <Veritas/Orchestra/Routing/Routing.h>
#include <Veritas/Orchestra/VO.h>

using namespace Veritas;
using namespace Orchestra;
using namespace Routing;

using namespace Messaging;

Manager::Manager() : isrunning(true) {}

Manager::~Manager() {
    finalize();
}

void Manager::finalize() {
    if (isRunning())
        isrunning = false;
}

bool Manager::isRunning() const { return isrunning; }

MessageQueue& Manager::getMessageQueue() { return VO::getInstance().getMessageQueue(); }

void Manager::run() {
    MessageQueue& messageQueue = getMessageQueue();
    while (isRunning()) {
        try {
            Message message = messageQueue.consume();
            LocalModule* localmodule = (LocalModule*) message.getDestiny().getLocalAddress();
            localmodule->receive(message);
        } catch (...) { break; }
    }
}
