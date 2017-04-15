#include <Veritas/Orchestra/Computing/ParallelManager.h>

using namespace Veritas;
using namespace Orchestra;
using namespace Computing;

ParallelManager::ParallelManager()
    : thread(threadf, this)
{}

ParallelManager::~ParallelManager() {
    finalize();
    thread.join();
}

void ParallelManager::threadf(ParallelManager *manager) {
    while (manager->isRunning())
        manager->run();
}
