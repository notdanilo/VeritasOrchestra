#include <Veritas/Orchestra/LocalModule.h>
#include <Veritas/Orchestra/ModuleManager.h>

#include <Veritas/Orchestra/Interfacing/Interfacing.h>

#include <algorithm>

using namespace Veritas;
using namespace Orchestra;
using namespace Data;
using namespace Messaging;
using namespace Interfacing;

const Interfacer& LocalModule::getInterfacer() {
    static Interfacer interfacer = Interfacer().set("Request", RequestInterface("Subscription"))
                                               .set("Request", RequestInterface("Unsubscription"))
                                               .set("Reply", ReplyInterface("Subscription", &LocalModule::SubscriptionRequest))
                                               .set("Reply", ReplyInterface("Unsubscription", &LocalModule::UnsubscriptionRequest))
                                               .set("Reply", ReplyInterface("Interfaces", &LocalModule::InterfacesRequest));
    return interfacer;
}

LocalModule::LocalModule() : LocalModule(getInterfacer()) {}

LocalModule::LocalModule(const Interfacer& interfacerRef) : Module(this), interfacerRef(interfacerRef), runInterval(0.0f), t0(Clock::now()) {
    ModuleManager *mm = ModuleManager::getLocalInstance();
    mm->add(this);
}

LocalModule::~LocalModule() {
    ModuleManager *mm = ModuleManager::getLocalInstance();
    mm->remove(this);
}

void LocalModule::run() {}

void LocalModule::receive(const Message &message) {
    try {
        String interfaceName = message.getInterface();
        const Interfacer::Interfaces* interfaces = getClassInterfacer().getInterfaces("Input");
        if (interfaces) ((InputInterface&) interfaces->at(interfaceName)).receive(message);
    } catch (...) {}
}

const Interfacer& LocalModule::getClassInterfacer() const { return interfacerRef; }

void LocalModule::setRunInterval(float64 seconds) { runInterval = seconds; }
float64 LocalModule::getRunInterval() const { return runInterval; }


void LocalModule::SubscriptionRequest(const Message &message, const Replier &replier) {    
    Module module(message.getOrigin());

    if (std::find(subscribers.begin(), subscribers.end(), module) == subscribers.end())
        subscribers.push_back(module);

    replier.reply();
}
void LocalModule::UnsubscriptionRequest(const Message& message, const Replier& replier) {
    Module module(message.getOrigin());

    auto it = std::find(subscribers.begin(), subscribers.end(), module);
    if (it != subscribers.end())
        subscribers.erase(it);

    replier.reply();
}

void LocalModule::InterfacesRequest(const Message &message, const Replier &replier) {
    replier.reply();
}

const LocalModule::Modules& LocalModule::getSubscribers() const { return subscribers; }
