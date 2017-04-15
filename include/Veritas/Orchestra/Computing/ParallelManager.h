#pragma once

#include <Veritas/Orchestra/Computing/Manager.h>

namespace Veritas {
    namespace Orchestra {
        namespace Computing {
            class ParallelManager : public Manager {
                public:
                    ParallelManager();
                    ~ParallelManager();
                private:
                    std::thread thread;
                    static void threadf(ParallelManager *manager);
            };
        }
    }
}
