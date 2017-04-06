#pragma once

#include <Veritas/Orchestra/Interfacing/Interface.h>

namespace Veritas {
    namespace Orchestra {
        class Module;
        namespace Interfacing {
            class OutputInterface : public Interface {
                public:
                    OutputInterface(const Data::String& name);
                    OutputInterface(const OutputInterface& copy);
                    OutputInterface(OutputInterface&& move);
                    ~OutputInterface();

                    OutputInterface& operator=(const OutputInterface& copy);
                    OutputInterface& operator=(OutputInterface&& move);
                public:
                    void send(const LocalModule& origin, const Module& destiny, const Messaging::Message& message) const;
                    void send(const LocalModule& origin, const Module* destiny, const Messaging::Message& message) const;
                    void send(const LocalModule* origin, const Module& destiny, const Messaging::Message& message) const;
                    void send(const LocalModule* origin, const Module* destiny, const Messaging::Message& message) const;
                    void publish(const LocalModule& origin, const Messaging::Message& message) const;
                    void publish(const LocalModule* origin, const Messaging::Message& message) const;
            };
        }
    }
}
