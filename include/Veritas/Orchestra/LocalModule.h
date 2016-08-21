#pragma once

#include "Module.h"
#include <chrono>

namespace Veritas {
    namespace Orchestra {
        class LocalModule : public Module {
            public:
                LocalModule();
                ~LocalModule();

                void setRunInterval(float64 runInterval);
                float64 getRunInterval() const;

                void virtual run();
            protected:
                void publish(const Message& message);
            private:
                friend class ModuleManager;

                float64 runInterval;
                using Clock = std::chrono::high_resolution_clock;
                Clock::time_point t0;
        };
    }
}
