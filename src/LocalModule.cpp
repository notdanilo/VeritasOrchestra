#include <Veritas/Orchestra/LocalModule.h>
#include <Veritas/Orchestra/ModuleManager.h>

using namespace Veritas::Orchestra;
using namespace Messaging;

LocalModule::LocalModule() : runInterval(0.0f), t0(Clock::now()) {
    ModuleManager *mm = ModuleManager::getLocalInstance();
    if (mm) mm->add(this);
    // ModuleManager is also a Module, so when it's instantiated, mm == 0
}

LocalModule::~LocalModule() {
    ModuleManager *mm = ModuleManager::getLocalInstance();
    if (mm != this) mm->remove(this);
}

void LocalModule::run() {}

void LocalModule::setRunInterval(float64 seconds) { runInterval = seconds; }
float64 LocalModule::getRunInterval() const { return runInterval; }

void LocalModule::publish(const Message &message) {}
void LocalModule::send(const Module *module, const Message &message) {}
