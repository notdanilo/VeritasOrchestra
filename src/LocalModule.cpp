#include <Veritas/Orchestra/LocalModule.h>
#include <Veritas/Orchestra/ModuleManager.h>

using namespace Veritas;
using namespace Orchestra;
using namespace Data;
using namespace Messaging;

LocalModule::LocalModule() : Module(this), runInterval(0.0f), t0(Clock::now()) {
    ModuleManager *mm = ModuleManager::getLocalInstance();
    if (mm) mm->add(this);
    // ModuleManager is also a Module, so when it's instantiated, mm == 0
}

LocalModule::~LocalModule() {
    ModuleManager *mm = ModuleManager::getLocalInstance();
    if (mm != this) mm->remove(this);
}

void LocalModule::run() {}

void LocalModule::set(const Interface &interface) { interfaces.push_back(interface); }
void LocalModule::set(Interface &&interface) { interfaces.push_back(std::move(interface)); }

//Origin construction has its own complexity on publishing
void LocalModule::publish(Message &message) {
    for (auto m: connections) send(m, Message(message));
}
void LocalModule::send(const Module *module, Message& message) { send(*module, message); }
void LocalModule::send(const Module *module, Message&& message) { send(*module, std::move(message)); }
void LocalModule::send(const Module& module, Message&& message) { send(module, message); }
void LocalModule::send(const Module &module, Message &message) {
    // Implement routing :)
    // Verify address existence
    // Build a better and coherent origin construction
    message.setOrigin(getAddress());
    Buffer buffer = Encoding::Base16().decode(module.getAddress());
    LocalModule* localmodule = (LocalModule*) *(uintptr_t*) buffer.getData();
    localmodule->receive(message);
}

void LocalModule::send(const String &address, Message&& message) { send(address, message); }
void LocalModule::send(const String &address, Message &message) {
    Module module(address);
    send(module, message);
}

void LocalModule::receive(const Message &message) {
    for (auto &i : interfaces) {
        if (i.getName() == message.getName()) {
            i.call(message);
        }
    }
}

void LocalModule::setRunInterval(float64 seconds) { runInterval = seconds; }
float64 LocalModule::getRunInterval() const { return runInterval; }

/*
bool LocalModule::isConnectedTo(Module *module) {
    for (Modules::iterator it = connections.begin(); it != connections.end(); it++)
        if (*it == module) return true;
    return false;
}

bool LocalModule::connect(Module* module) {
    if (!isConnectedTo(module)) {
        connections.push_back(module);
        //module->connect(this);
        return true;
    } else return false;

    return true;
}

bool LocalModule::disconnect(Module *module) {
    if (isConnectedTo(module)) {
        connections.remove(module);
        return true;
    } else return false;
}
*/
