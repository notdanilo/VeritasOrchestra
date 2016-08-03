#pragma once

#include "Module.h"
#include <thread>

namespace Veritas {
    namespace Orchestra {
        class ModuleManager : public Module {
            public:
                ModuleManager();
                ~ModuleManager();

                void add(Module *module);
                void remove(Module *module);

                void run();

                static ModuleManager* getLocalInstance();
            private:
                ModuleManager(bool MAIN_THREAD);
                static void setLocalInstance(ModuleManager *mm);

                typedef std::list<Module*> Modules;
                Modules modules;

                std::thread thread;
                static void threadf(ModuleManager *mm);

                static ModuleManager mainManager;
                thread_local static ModuleManager* manager;
        };
    }
}
