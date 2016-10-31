#include <Veritas/Orchestra/Module.h>
#include <Veritas/Orchestra/ModuleManager.h>

using namespace Veritas;
using namespace Orchestra;

using Clock = std::chrono::high_resolution_clock;

Module::Module() {}
Module::~Module() {}

bool Module::isConnectedTo(Module *module) {
    for (Modules::iterator it = connections.begin(); it != connections.end(); it++)
        if (*it == module) return true;
    return false;
}

bool Module::connect(Module *module) {
    if (!isConnectedTo(module)) {
        connections.push_back(module);
        module->connect(this);
        return true;
    } else return false;

    return true;
}

bool Module::disconnect(Module *module) {
    if (isConnectedTo(module)) {
        // TO-DO: remove event listener

        connections.remove(module);
        return true;
    } else return false;
}
