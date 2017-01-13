#pragma once

#include "Module.h"
#include "Messaging/Messaging.h"
#include "Interfacing/InputInterface.h"
#include "Interfacing/OutputInterface.h"
#include <chrono>
#include <map>

namespace Veritas {
    namespace Orchestra {
        class LocalModule : public Module {
            public:
                typedef std::map<Data::String, Interfacing::InputInterface*> InputInterfaces;
                typedef std::map<Data::String, Interfacing::OutputInterface*> OutputInterfaces;

                LocalModule();
                ~LocalModule();

                void set(Interfacing::InputInterface *interface);
                void set(Interfacing::OutputInterface *interface);
                const InputInterfaces& getInputInterfaces() const;
                const OutputInterfaces& getOutputInterfaces() const;

                void receive(const Messaging::Message& message);

                void setRunInterval(float64 runInterval);
                float64 getRunInterval() const;

                typedef std::list<Module> Modules;
                Modules connections;
            protected:
                void virtual run();
            private:
                friend class ModuleManager;

                float64 runInterval;
                using Clock = std::chrono::high_resolution_clock;
                Clock::time_point t0;

                InputInterfaces inputInterfaces;
                OutputInterfaces outputInterfaces;

                /*
                void RequestConnection(const Messaging::Message& message);
                void NotifyConnection(const Messaging::Message& message);

                void RequestDisconnection(const Messaging::Message& message);
                void NotifyDisconnection(const Messaging::Message& message);

                void RequestInterfaces(const Messaging::Message& message);
                */
        };
    }
}
