#pragma once

#include "Message.h"
#include <chrono>

namespace Veritas {
    namespace Orchestra {
        class Module : public Message::Listener {
            public:
                Module();
                virtual ~Module();

                bool isConnectedTo(Module* module);
                bool connect(Module* module);
                bool disconnect(Module* module);

                void setRunInterval(float64 runInterval);
                float64 getRunInterval() const;

                virtual void run();
            private:
                friend class ModuleManager;

                float64 runInterval;
                std::chrono::high_resolution_clock::time_point t0;

                typedef std::list<Module*> Modules;
                Modules connections;
        };
    }
}
