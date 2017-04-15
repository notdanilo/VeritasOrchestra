#pragma once

#include <Veritas/Orchestra/Computing/LocalModule.h>
#include <Veritas/Orchestra/Routing/Routing.h>
#include <thread>
#include <queue>
#include <mutex>
#include <atomic>

namespace Veritas {
    namespace Orchestra {
        class Manager {
            public:
                Manager();
                Manager(const Manager& copy) = delete;
                Manager(Manager&& move);
                virtual ~Manager();

                void operator=(const Manager& copy) = delete;

                bool isRunning() const;
            protected:
                virtual Routing::MessageQueue& getMessageQueue();
                void finalize();
                void run();
            private:
                friend class LocalModule;
                friend class Interfacing::OutputInterface;
                friend class VO;

                volatile std::atomic<bool> isrunning;
        };
    }
}
