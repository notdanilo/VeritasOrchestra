#pragma once

#include "Module.h"
#include "Messaging/Messaging.h"
#include "Interfacing/InputInterface.h"
#include "Interfacing/OutputInterface.h"
#include "Interfacing/Interfacer.h"
#include "Interfacing/Replier.h"
#include <chrono>
#include <map>

namespace Veritas {
    namespace Orchestra {
        class LocalModule : public Module {
            public:
                typedef std::map<Data::String, Interfacing::InputInterface*> InputInterfaces;
                typedef std::map<Data::String, Interfacing::OutputInterface*> OutputInterfaces;
                typedef std::vector<Module> Modules;

                LocalModule();
                LocalModule(const Interfacing::Interfacer& interfacer);
                ~LocalModule();

                const Interfacing::Interfacer& getClassInterfacer() const;

                void receive(const Messaging::Message& message);

                void setRunInterval(float64 runInterval);
                float64 getRunInterval() const;

                const Modules& getSubscribers() const;
            protected:
                static const Interfacing::Interfacer& getInterfacer();
                void virtual run();
            private:

                friend class ModuleManager;

                float64 runInterval;
                using Clock = std::chrono::high_resolution_clock;
                Clock::time_point t0;

                Modules subscribers;

                void InterfacesRequest(const Messaging::Message& message, const Interfacing::Replier& replier);
                void SubscriptionRequest(const Messaging::Message& message, const Interfacing::Replier& replier);
                void UnsubscriptionRequest(const Messaging::Message& message, const Interfacing::Replier& replier);

                const Interfacing::Interfacer& interfacerRef;
        };
    }
}
