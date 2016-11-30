#pragma once
#include <functional>
#include "Message.h"

namespace Veritas {
    namespace Orchestra {
        namespace Messaging {
            class Interface {
                public:
                    Interface(const String& name);
                    Interface(const Interface& copy);
                    Interface(Interface&& move);
                    ~Interface();

                    Interface& operator=(const Interface& copy);
                    Interface& operator=(Interface&& move);

                    const String& getName() const;
                    void call(const Message& message);

                    Interface& require(const String& field);
                    Interface& setCallback(std::function<void(const Message& message)> callback);

                    template <class C>
                    Interface& setCallback(void (C::*callback)(const Message& message), C *object) { return setCallback([object, callback](const Message& message) { (object->*callback)(message); }); }
                private:
                    String name;
                    std::function<void(const Message& message)> callback;
            };
        }
    }
}
