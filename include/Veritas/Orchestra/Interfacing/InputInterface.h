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
                    InputInterface(const InputInterface& copy);
                    InputInterface(InputInterface&& move);
                    template <class C> InputInterface(const Data::String& name, void (C::*callback)(const Messaging::Message& message)) : InputInterface(name, [callback](const Messaging::Message& message) { (((C*) message.getDestiny().getLocalAddress())->*callback)(message); }) {}
                    ~InputInterface();

                    InputInterface& operator=(const InputInterface& copy);
                    InputInterface& operator=(InputInterface&& move);

                    // should only be accessible by LocalModule
                    void receive(const Messaging::Message& message) const;
                private:
                    Callback callback;
            };
        }
    }
}
