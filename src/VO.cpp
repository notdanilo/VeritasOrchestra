#include <Veritas/Orchestra/VO.h>
#include <Veritas/Orchestra/Computing/Manager.h>

using namespace Veritas;
using namespace Orchestra;
using namespace Routing;
using namespace Computing;

VO::VO() {
    /*
    // Still need to implement more of the routing mechanism before getting into message routing to the managers
    // To consider for the dedicated managers:
    // GLContext cannot me executed on different threads because the context is attatched to the Thread.
    // A module that runs the OpenGL functions must be in the same GLContext's thread.
    parallelManagers.push_back(new ParallelManager());
    parallelManagers.push_back(new ParallelManager());
    parallelManagers.push_back(new ParallelManager());
    */
}

VO::~VO() {
    finalize();
    for (ParallelManager* parallelManager : parallelManagers)
        delete parallelManager;
}

VO& VO::getInstance() {
    static VO vo;
    return vo;
}

bool VO::isRunning() const {
    bool isrunning = false;
    for (ParallelManager* parallelManager : parallelManagers)
        isrunning |= parallelManager->isRunning();
    return isrunning || mainManager.isRunning();
}

void VO::finalize() {
    mainManager.finalize();
    for (ParallelManager* parallelManager : parallelManagers)
        parallelManager->finalize();
}

MessageQueue& VO::getMessageQueue() { return messageQueue; }
Runner& VO::getRunner() { return runner; }

void VO::run() {
    runner.run();
    mainManager.run();
}
