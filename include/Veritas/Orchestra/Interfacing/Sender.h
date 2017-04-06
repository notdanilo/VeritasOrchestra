#pragma once
#include <Veritas/Orchestra/Interfacing/OutputInterface.h>

namespace Veritas {
    namespace Orchestra {
        namespace Interfacing {
            class Sender {
                public:
                    Sender(const LocalModule& module);
                    Sender(const LocalModule* module);
                    void send(const Data::String& interface, const Module* destination, const Messaging::Message& message = Messaging::Message()) const;
                    void send(const Data::String& interface, const Module& destination, const Messaging::Message& message = Messaging::Message()) const;

                    const LocalModule& getModule() const;
                private:
                    const LocalModule& module;
            };
        }
    }
}
