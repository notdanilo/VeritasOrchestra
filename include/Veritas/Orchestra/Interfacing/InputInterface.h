#pragma once
#include <functional>
#include "Interface.h"

namespace Veritas {
    namespace Orchestra {
        namespace Interfacing {
            class InputInterface : public Interface {
                public:
                    typedef std::function<void(const Messaging::Message& message)> Callback;
                    InputInterface(const Data::String& name, LocalModule* module, Callback callback);
                    template <class C> InputInterface(const Data::String& name, C* module, void (C::*callback)(const Messaging::Message& message)) : InputInterface(name, module, [module, callback](const Messaging::Message& message) { (module->*callback)(message); }) {}
                    InputInterface(const InputInterface& copy) = delete;
                    InputInterface(InputInterface&& move);
                    ~InputInterface();

                    InputInterface& operator=(const InputInterface& copy) = delete;
                    InputInterface& operator=(InputInterface&& move);

                    // should only be accessible by LocalModule
                    void receive(const Messaging::Message& message);
                private:
                    Callback callback;
            };
        }
    }
}
