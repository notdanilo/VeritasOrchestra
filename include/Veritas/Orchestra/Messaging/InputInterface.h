#pragma once
#include <functional>
#include "Interface.h"

namespace Veritas {
    namespace Orchestra {
        namespace Messaging {
            class InputInterface : public Interface {
                public:
                    InputInterface(const String& name);
                    InputInterface(const InputInterface& copy);
                    InputInterface(InputInterface&& move);
                    ~InputInterface();

                    InputInterface& operator=(const InputInterface& copy);
                    InputInterface& operator=(InputInterface&& move);

                    InputInterface& require(const Data::String &field);

                    InputInterface& setCallback(std::function<void(const Message& message)> callback);
                    template <class C> InputInterface& setCallback(void (C::*callback)(const Message& message), C *object) { return setCallback([object, callback](const Message& message) { (object->*callback)(message); }); }
                    void receive(const Message& message);
                private:
                    std::function<void(const Message& message)> callback;
            };
        }
    }
}
