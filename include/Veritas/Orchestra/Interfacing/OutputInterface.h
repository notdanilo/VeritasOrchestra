#pragma once

#include <Veritas/Orchestra/Interfacing/Interface.h>

namespace Veritas {
    namespace Orchestra {
        class Module;
        namespace Interfacing {
            class OutputInterface : public Interface {
                public:
                    typedef std::function<void(Messaging::Message& message)> Callback;
                    OutputInterface(const Data::String& name, LocalModule* module, Callback callback = 0);
                    template <class C> OutputInterface(const Data::String& name, C* module, void (C::*callback)(Messaging::Message& message)) : OutputInterface(name, module, [module, callback](Messaging::Message& message) { (module->*callback)(message); }) {}
                    OutputInterface(const OutputInterface& copy) = delete;
                    OutputInterface(OutputInterface&& move);
                    ~OutputInterface();

                    OutputInterface& operator=(const OutputInterface& copy) = delete;
                    OutputInterface& operator=(OutputInterface&& move);

                    void send(const Module& module, Messaging::Message& message) const;
                    void send(const Module& module, Messaging::Message&& message = Messaging::Message()) const;
                    void send(const Messaging::Address& address, Messaging::Message& message) const;
                    void send(const Messaging::Address& address, Messaging::Message&& message = Messaging::Message()) const;
                    void publish(Messaging::Message& message) const;
                    void publish(Messaging::Message&& message = Messaging::Message()) const;
                private:
                    Callback callback;
            };
        }
    }
}
