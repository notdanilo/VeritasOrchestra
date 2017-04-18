#pragma once

#include <Veritas/Orchestra/Interfacing/Interface.h>

namespace Veritas {
    namespace Orchestra {
        namespace Interfacing {
            class OutputInterface : public Interface {
                public:
                    OutputInterface(const Data::String& name);
                    OutputInterface(const OutputInterface& copy);
                    OutputInterface(OutputInterface&& move);
                    ~OutputInterface();

                    OutputInterface& operator=(const OutputInterface& copy);
                    OutputInterface& operator=(OutputInterface&& move);

                    void send(const Computing::LocalModule& origin, const Computing::Module& destiny, const Messaging::Content& content) const;
                    void send(const Computing::LocalModule& origin, const Computing::Module* destiny, const Messaging::Content& content) const;
                    void send(const Computing::LocalModule* origin, const Computing::Module& destiny, const Messaging::Content& content) const;
                    void send(const Computing::LocalModule* origin, const Computing::Module* destiny, const Messaging::Content& content) const;
            };
        }
    }
}
