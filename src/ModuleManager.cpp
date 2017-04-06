#include <Veritas/Orchestra/ModuleManager.h>
#include <Veritas/Orchestra/Routing/Routing.h>

using namespace Veritas;
using namespace Orchestra;
using namespace Routing;

using namespace Messaging;

thread_local ModuleManager* ModuleManager::manager = 0;
ModuleManager ModuleManager::mainManager(true);

MessageQueue ModuleManager::messageQueue;

ModuleManager::ModuleManager() {
    thread = std::thread(threadf, this);
}

ModuleManager::ModuleManager(bool MAIN_THREAD) {
    manager = this;
}

ModuleManager::~ModuleManager() {}

void ModuleManager::add(LocalModule *module) { modules.push_back(module); }
void ModuleManager::remove(LocalModule *module) { modules.remove(module); }

#include <chrono>
using Clock = std::chrono::high_resolution_clock;

// Make it private, so no one can call it
// Create MainModuleManager with public run (maybe we should name it Orchestra)
void ModuleManager::run() {
    // Implement message handling and stuff
    for (LocalModules::iterator it = modules.begin(); it != modules.end(); it++) {
        LocalModule *module = *it;

        auto t1 = Clock::now();
        auto duration = t1 - module->t0;
        if (std::chrono::duration<float64>(duration).count() > module->getRunInterval()) {
            module->t0 += duration;
            module->run();
        }
    }

    while (ModuleManager::messageQueue.getAmmount()) {
        Message message = ModuleManager::messageQueue.consume();
        LocalModule* localmodule = (LocalModule*) message.getDestiny().getLocalAddress();
        localmodule->receive(message);
    }
}

void ModuleManager::threadf(ModuleManager *mm) {
    setLocalInstance(mm);
    while (1) getLocalInstance()->run();
}

#warning Why don't we remove this interface and access it from the Module as its parent? :)
void ModuleManager::setLocalInstance(ModuleManager *mm) { manager = mm; }
ModuleManager* ModuleManager::getLocalInstance() { return manager; }
