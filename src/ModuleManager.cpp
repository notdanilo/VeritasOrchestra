#include <Veritas/Orchestra/ModuleManager.h>

using namespace Veritas;
using namespace Orchestra;

thread_local ModuleManager* ModuleManager::manager = 0;
ModuleManager ModuleManager::mainManager(true);

ModuleManager::ModuleManager() {
    thread = std::thread(threadf, this);
}

ModuleManager::ModuleManager(bool MAIN_THREAD) {
    manager = this;
}

ModuleManager::~ModuleManager() {}

void ModuleManager::add(Module *module) { modules.push_back(module); }
void ModuleManager::remove(Module *module) { modules.remove(module); }

#include <chrono>
using Clock = std::chrono::high_resolution_clock;

// Make it private, so no one can call it
// Create MainModuleManager with public run
void ModuleManager::run() {
    // Implement message handling and stuff
    for (Modules::iterator it = modules.begin(); it != modules.end(); it++) {
        Module *module = *it;

        auto t1 = Clock::now();
        auto duration = t1 - module->t0;
        if (std::chrono::duration<float64>(duration).count() > module->getRunInterval()) {
            module->t0 += duration;
            module->run();
        }
    }
}

void ModuleManager::threadf(ModuleManager *mm) {
    setLocalInstance(mm);
    while (1) getLocalInstance()->run();
}

// Why don't we remove this interface and access it from the Module as its parent? :)
void ModuleManager::setLocalInstance(ModuleManager *mm) { manager = mm; }
ModuleManager* ModuleManager::getLocalInstance() { return manager; }
