#pragma once
#include <functional>
#include "Interface.h"

namespace Veritas {
    namespace Orchestra {
        namespace Interfacing {
            class InputInterface : public Interface {
                public:
                    typedef std::function<void(const Messaging::Message& message)> Callback;
                    InputInterface(const Data::String &name, Callback callback);
                    template <class C> InputInterface(const Data::String& name, void (C::*callback)(const Messaging::Message& message)) : Interface(name), callback([callback](const Messaging::Message& message, LocalModule* from) { (((C*) from)->*callback)(message); }) {} // using internals on template seems so wrong

                    InputInterface(const InputInterface& copy);
                    InputInterface(InputInterface&& move);
                    ~InputInterface();

                    InputInterface& operator=(const InputInterface& copy);
                    InputInterface& operator=(InputInterface&& move);

                    // should only be accessible by LocalModule
                    void receive(const Messaging::Message& message) const;
                    void receive(const Messaging::Message& message, LocalModule* from) const;
                private:
                    std::function<void(const Messaging::Message& message, LocalModule* from)> callback;
            };
        }
    }
}
