#pragma once
#include <Veritas/Orchestra/Interfacing/OutputInterface.h>

namespace Veritas {
    namespace Orchestra {
        namespace Interfacing {
            class Sender {
                public:
                    Sender(const Computing::LocalModule& module);
                    Sender(const Computing::LocalModule* module);
                    void send(const Data::String& interface, const Computing::Module* destination, const Messaging::Message& message = Messaging::Message()) const;
                    void send(const Data::String& interface, const Computing::Module& destination, const Messaging::Message& message = Messaging::Message()) const;

                    const Computing::LocalModule& getModule() const;
                private:
                    const Computing::LocalModule& module;
            };
        }
    }
}
