#pragma once

#include "LocalModule.h"
#include <thread>

namespace Veritas {
    namespace Orchestra {
        class ModuleManager : public LocalModule {
            public:
                ModuleManager();
                ~ModuleManager();

                void run(); // Only the main-thread ModuleManager should expose this

                static ModuleManager* getLocalInstance();
            protected:
            private:
                friend class LocalModule;

                ModuleManager(bool MAIN_THREAD);
                static void setLocalInstance(ModuleManager *mm);

                void add(LocalModule *module);
                void remove(LocalModule *module);

                typedef std::list<LocalModule*> LocalModules;
                LocalModules modules;

                std::thread thread;
                static void threadf(ModuleManager *mm);

                static ModuleManager mainManager;
                thread_local static ModuleManager* manager;
        };
    }
}
