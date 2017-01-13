#pragma once

#include <Veritas/Orchestra/Interfacing/Interface.h>

namespace Veritas {
    namespace Orchestra {
        class Module;
        namespace Interfacing {
            class OutputInterface : public Interface {
                public:
                    OutputInterface(const Data::String& name, LocalModule* module);
                    OutputInterface(const OutputInterface& copy);
                    OutputInterface(OutputInterface&& move);
                    ~OutputInterface();

                    OutputInterface& operator=(const OutputInterface& copy);
                    OutputInterface& operator=(OutputInterface&& move);

                    OutputInterface& setCallback(std::function<void(Messaging::Message& message)> callback);
                    template <class C> OutputInterface& setCallback(void (C::*callback)(Messaging::Message& message)) { return setCallback([this, callback](Messaging::Message& message) { (((C*) getModule())->*callback)(message); }); }

                    void send(const Module& module, Messaging::Message& message) const;
                    void send(const Module& module, Messaging::Message&& message = Messaging::Message()) const;
                    void send(const Messaging::Address& address, Messaging::Message& message) const;
                    void send(const Messaging::Address& address, Messaging::Message&& message = Messaging::Message()) const;
                    void publish(Messaging::Message& message) const;
                    void publish(Messaging::Message&& message = Messaging::Message()) const;
                private:
                    std::function<void(Messaging::Message& message)> callback;
            };
        }
    }
}
