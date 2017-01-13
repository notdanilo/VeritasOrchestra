#pragma once
#include <functional>
#include "Interface.h"

namespace Veritas {
    namespace Orchestra {
        namespace Interfacing {
            class InputInterface : public Interface {
                public:
                    InputInterface(const Data::String& name, LocalModule* module);
                    InputInterface(const InputInterface& copy);
                    InputInterface(InputInterface&& move);
                    ~InputInterface();

                    InputInterface& operator=(const InputInterface& copy);
                    InputInterface& operator=(InputInterface&& move);

                    InputInterface& setCallback(std::function<void(const Messaging::Message& message)> callback);
                    template <class C> InputInterface& setCallback(void (C::*callback)(const Messaging::Message& message)) { return setCallback([this, callback](const Messaging::Message& message) { (((C*) getModule())->*callback)(message); }); }
                    void receive(const Messaging::Message& message);
                private:
                    std::function<void(const Messaging::Message& message)> callback;
            };
        }
    }
}
