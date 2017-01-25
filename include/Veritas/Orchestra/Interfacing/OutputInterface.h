#pragma once

#include <Veritas/Orchestra/Interfacing/Interface.h>

namespace Veritas {
    namespace Orchestra {
        class Module;
        namespace Interfacing {
            class OutputInterface : public Interface {
                public:
                    typedef std::function<void(Messaging::Message& message)> Callback;
                    OutputInterface(const Data::String& name, LocalModule* module);
                    OutputInterface(const OutputInterface& copy) = delete;
                    OutputInterface(OutputInterface&& move);
                    ~OutputInterface();

                    OutputInterface& operator=(const OutputInterface& copy) = delete;
                    OutputInterface& operator=(OutputInterface&& move);

                    void send(const Module& module, const Messaging::Message& message) const;
                    void send(const Module* module, const Messaging::Message& message) const;
                    void send(const Messaging::Address& address, const Messaging::Message& message) const;
                    void publish(const Messaging::Message& message) const;
            };
        }
    }
}
