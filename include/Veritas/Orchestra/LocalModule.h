#pragma once

#include "Module.h"
#include "Messaging/Messaging.h"
#include "Messaging/InputInterface.h"
#include "Messaging/OutputInterface.h"
#include <chrono>

namespace Veritas {
    namespace Orchestra {
        using Data::String;
        using Messaging::Message;
        using Messaging::InputInterface;
        using Messaging::OutputInterface;
        class LocalModule : public Module {
            public:
                typedef std::map<String, InputInterface> InputInterfaces;
                typedef std::map<String, OutputInterface> OutputInterfaces;

                LocalModule();
                ~LocalModule();

                void set(const InputInterface& interface);
                void set(InputInterface&& interface);
                const InputInterfaces& getInputInterfaces() const;

                void set(const OutputInterface& interface);
                void set(OutputInterface&& interface);
                const OutputInterfaces& getOutputInterfaces() const;

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

                void RequestConnection(const Messaging::Message& message);
                void NotifyConnection(const Messaging::Message& message);

                void RequestDisconnection(const Messaging::Message& message);
                void NotifyDisconnection(const Messaging::Message& message);

                void RequestInterfaces(const Messaging::Message& message);
        };
    }
}
