#pragma once

#include <Veritas/Orchestra/Computing/Module.h>
#include <Veritas/Orchestra/Messaging/Messaging.h>
#include <Veritas/Orchestra/Interfacing/InputInterface.h>
#include <Veritas/Orchestra/Interfacing/OutputInterface.h>
#include <Veritas/Orchestra/Interfacing/Interfacer.h>
#include <Veritas/Orchestra/Interfacing/Replier.h>
#include <chrono>
#include <map>

namespace Veritas {
    namespace Orchestra {
        namespace Computing {
            class LocalModule : public Module {
                public:
                    typedef std::vector<Module> Modules;

                    LocalModule();
                    LocalModule(const Interfacing::Interfacer& interfacer);
                    ~LocalModule();

                    const Interfacing::Interfacer& getClassInterfacer() const;
                    const Modules& getSubscribers() const;
                protected:
                    static const Interfacing::Interfacer& getInterfacer();
                private:
                    friend class Manager;
                    Modules subscribers;
                    void receive(const Messaging::Message& message);

                    void InterfaceGroupsRequest(const Messaging::Message& message, const Interfacing::Replier& replier);
                    void InterfacesRequest(const Messaging::Message& message, const Interfacing::Replier& replier);
                    void SubscriptionRequest(const Messaging::Message& message, const Interfacing::Replier& replier);
                    void UnsubscriptionRequest(const Messaging::Message& message, const Interfacing::Replier& replier);

                    const Interfacing::Interfacer& interfacerRef;
            };
        }
    }
}
