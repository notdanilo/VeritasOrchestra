#pragma once

#include "Module.h"
#include "Messaging/Messaging.h"
#include <chrono>

namespace Veritas {
    namespace Orchestra {
        class LocalModule : public Module {
            public:
                LocalModule();
                ~LocalModule();

                void setRunInterval(float64 runInterval);
                float64 getRunInterval() const;

                void publish(const Messaging::Message& message);
                void send(const Module* module, const Messaging::Message& message);

                void virtual run();
            private:
                friend class ModuleManager;

                float64 runInterval;
                using Clock = std::chrono::high_resolution_clock;
                Clock::time_point t0;
        };
    }
}
