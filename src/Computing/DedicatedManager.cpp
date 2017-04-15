#include <Veritas/Orchestra/Computing/DedicatedManager.h>

using namespace Veritas;
using namespace Orchestra;
using namespace Routing;
using namespace Computing;

MessageQueue& DedicatedManager::getMessageQueue() { return messageQueue; }
