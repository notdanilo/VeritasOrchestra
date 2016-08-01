#pragma once

#include "Module.h"

int main(int argc, char **argv);

namespace Veritas {
    namespace Orchestra {
        class ModuleManager : public Module {
            public:
                void add(Module *module);
                void remove(Module *module);

                static ModuleManager& getInstance();
            private:
                friend int ::main(int argc, char **argv);

                ModuleManager();
                ~ModuleManager();

                void run();

                typedef std::list<Module*> Modules;
                Modules modules;

                thread_local static ModuleManager manager;
        };
    }
}

Veritas::Orchestra::Module* EntryPoint();
#define SET_ENTRY_POINT(EP) Veritas::Orchestra::Module* EntryPoint() { return new EP(); }
