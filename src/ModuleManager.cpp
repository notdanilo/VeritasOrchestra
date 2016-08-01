#include <Veritas/Orchestra/ModuleManager.h>

using namespace Veritas;
using namespace Orchestra;

thread_local ModuleManager ModuleManager::manager;

ModuleManager::ModuleManager() {}
ModuleManager::~ModuleManager() {}

void ModuleManager::add(Module *module) { modules.push_back(module); }
void ModuleManager::remove(Module *module) { modules.remove(module); }

void ModuleManager::run() {
    for (Modules::iterator it = modules.begin(); it != modules.end(); it++) (*it)->run();
}

ModuleManager& ModuleManager::getInstance() { return manager; }

int main(int argc, char **argv) {
    Module *module = EntryPoint();
    ModuleManager::getInstance().add(module);
    while (1) ModuleManager::manager.run();
    delete module;
}
