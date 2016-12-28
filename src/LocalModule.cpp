#include <Veritas/Orchestra/LocalModule.h>
#include <Veritas/Orchestra/ModuleManager.h>

using namespace Veritas;
using namespace Orchestra;
using namespace Data;
using namespace Messaging;

LocalModule::LocalModule() : Module(this), runInterval(0.0f), t0(Clock::now()) {
    set(InputInterface("RequestConnection").setCallback(&LocalModule::RequestConnection, this));
    set(InputInterface("NotifyConnection").setCallback(&LocalModule::NotifyConnection, this));
    set(InputInterface("RequestDisconnection").setCallback(&LocalModule::RequestDisconnection, this));
    set(InputInterface("NotifyDisconnection").setCallback(&LocalModule::NotifyDisconnection, this));

    ModuleManager *mm = ModuleManager::getLocalInstance();
    if (mm) mm->add(this);
    // ModuleManager is also a Module, so when it's instantiated, mm == 0
}

LocalModule::~LocalModule() {
    publish(Message("RequestDisconnection"));

    ModuleManager *mm = ModuleManager::getLocalInstance();
    if (mm != this) mm->remove(this);
}

void LocalModule::run() {}

void LocalModule::set(const InputInterface &interface) {
    inputInterfaces.emplace(interface.getName(), interface);
}
void LocalModule::set(InputInterface &&interface) {
    inputInterfaces.emplace(interface.getName(), std::move(interface));
}
void LocalModule::set(const OutputInterface &interface) {
    outputInterfaces.emplace(interface.getName(), interface);
}

void LocalModule::set(OutputInterface &&interface) {
    outputInterfaces.emplace(interface.getName(), std::move(interface));
}

//Origin construction has its own complexity on publishing
void LocalModule::publish(Message &&message) { publish(message); }
void LocalModule::publish(Message &message) {
    for (auto m: connections) send(m, Message(message));
}

void LocalModule::send(const String &address, Message&& message) { send(address, message); }
void LocalModule::send(const String &address, Message &message) {
    Module module(address);
    send(module, message);
}
void LocalModule::send(const Module *module, Message& message) { send(*module, message); }
void LocalModule::send(const Module *module, Message&& message) { send(*module, std::move(message)); }
void LocalModule::send(const Module& module, Message&& message) { send(module, message); }
void LocalModule::send(const Module &module, Message &message) {
    try {
        outputInterfaces.at(message.getName()).send(message);
    } catch (...) {
        // No OutputInterface
    }

    // Implement routing :)
    // Verify address existence
    // Build a better and coherent origin construction
    message.setOrigin(getAddress());
    Buffer buffer = Encoding::Base16().decode(module.getAddress());
    LocalModule* localmodule = (LocalModule*) *(uintptr_t*) buffer.getData();
    localmodule->receive(message);
}

void LocalModule::receive(const Message &message) {
    try {
        inputInterfaces.at(message.getName()).receive(message);
    } catch (...) {
        // infinite loop if the module doesn't has the NotifyReport InputInterface
        // send(message.getOrigin(), Message("NotifyReport").set("Report", "Interface not found."));
    }
}

void LocalModule::setRunInterval(float64 seconds) { runInterval = seconds; }
float64 LocalModule::getRunInterval() const { return runInterval; }

void LocalModule::RequestConnection(const Message &message) {
    Module module(message.getOrigin());
    connections.push_back(std::move(module));
    send(module, Message("NotifyConnection"));
}
void LocalModule::NotifyConnection(const Message& message) {
    connections.push_back(Module(message.getOrigin()));
}

void LocalModule::RequestDisconnection(const Message &message) {
    Module module(message.getOrigin());
    send(module, Message("NotifyDisconnection"));
    connections.remove(module);
}
void LocalModule::NotifyDisconnection(const Message& message) {
    connections.remove(Module(message.getOrigin()));
}
