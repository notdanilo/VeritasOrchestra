#pragma once

#include <Veritas/Orchestra/Messaging/Interface.h>

namespace Veritas {
    namespace Orchestra {
        namespace Messaging {
            class OutputInterface : public Interface {
                public:
                    OutputInterface(const String& name);
                    OutputInterface(const OutputInterface& copy);
                    OutputInterface(OutputInterface&& move);
                    ~OutputInterface();

                    OutputInterface& operator=(const OutputInterface& copy);
                    OutputInterface& operator=(OutputInterface&& move);

                    OutputInterface& require(const Data::String &field);

                    OutputInterface& setCallback(std::function<void(Message& message)> callback);
                    template <class C> OutputInterface& setCallback(void (C::*callback)(Message& message), C *object) { return setCallback([object, callback](Message& message) { (object->*callback)(message); }); }
                    void send(Message& message);
                private:
                    std::function<void(Message& message)> callback;

            };
        }
    }
}
