#include <Veritas/Orchestra/Computing/LocalModule.h>
#include <Veritas/Orchestra/Computing/Manager.h>
#include <Veritas/Orchestra/VO.h>

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
                                               .set("Reply", ReplyInterface("InterfaceGroups", &LocalModule::InterfaceGroupsRequest))
                                               .set("Reply", ReplyInterface("Interfaces", &LocalModule::InterfacesRequest));
    return interfacer;
}

LocalModule& LocalModule::from(const Address &address) {
    return *((LocalModule*) address.getLocalAddress());
}

LocalModule::LocalModule() : LocalModule(getInterfacer()) {}

LocalModule::LocalModule(const Interfacer& interfacerRef) : Module(this), interfacerRef(interfacerRef) {}

LocalModule::~LocalModule() {}

void LocalModule::receive(const Message &message) {
    try {
        String interfaceName = message.getInterface();
        const Interfacer::Interfaces* interfaces = getClassInterfacer().getInterfaces("Input");
        if (interfaces) ((InputInterface&) interfaces->at(interfaceName)).receive(message);
    } catch (...) {}
}

const Interfacer& LocalModule::getClassInterfacer() const { return interfacerRef; }


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

void LocalModule::InterfaceGroupsRequest(const Message& message, const Replier& replier) {
    List list;

    const Interfacer& interfacer = getClassInterfacer();
    const Interfacer::Groups& groups = interfacer.getGroups();

    list.setSize(groups.size());
    uint32 i = 0;
    for (auto& group : groups)
        list[i++] = group.first;

    replier.reply(Message().set(list));
}

void LocalModule::InterfacesRequest(const Message &message, const Replier &replier) {
    const Form& contents = message.getContent();
    const String& group = contents.get("Group");

    const Interfacer& interfacer = getClassInterfacer();
    const Interfacer::Interfaces* interfaces = interfacer.getInterfaces(group);

    List list;
    list.setSize(interfaces->size());
    uint32 i = 0;
    for (auto interface : *interfaces)
        list[i++] = interface.first;

    Form form;
    form.set("Group", group);
    form.set("Interfaces", std::move(list));

    replier.reply(Message().set(std::move(form)));
}

const LocalModule::Modules& LocalModule::getSubscribers() const { return subscribers; }
