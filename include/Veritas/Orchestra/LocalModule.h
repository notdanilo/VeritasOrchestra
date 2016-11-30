#pragma once

#include "Module.h"
#include "Messaging/Messaging.h"
#include "Messaging/Interface.h"
#include <chrono>

namespace Veritas {
    namespace Orchestra {
        using Data::String;
        using Messaging::Message;
        using Messaging::Interface;
        class LocalModule : public Module {
            public:
                typedef std::list<Interface> Interfaces;

                LocalModule();
                ~LocalModule();

                void set(const Interface& interface);
                void set(Interface&& interface);
                const Interfaces& getInterfaces() const;

                void send(const Module* module, Message& message);
                void send(const Module* module, Message&& message);
                void send(const Module& module, Message& message);
                void send(const Module& module, Message&& message);
                void send(const String& address, Message& message);
                void send(const String& address, Message&& message);
                void publish(Message& message);
                void publish(Message&& message);
                void receive(const Message& message);

                void setRunInterval(float64 runInterval);
                float64 getRunInterval() const;
                void virtual run();

                bool isConnectedTo(Module* module);
                bool connect(Module* module);
                bool disconnect(Module* module);
                friend class LocalModule;
                friend class RemoteModule;

                typedef std::list<Module*> Modules;
                Modules connections;
            private:
                friend class ModuleManager;

                float64 runInterval;
                using Clock = std::chrono::high_resolution_clock;
                Clock::time_point t0;

                Interfaces interfaces;
        };
    }
}
