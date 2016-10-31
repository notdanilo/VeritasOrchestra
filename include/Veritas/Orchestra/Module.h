#pragma once

#include <Veritas/Data/String.h>
#include <list>

namespace Veritas {
    namespace Orchestra {
        class Module {
            public:
                virtual ~Module();

                bool isConnectedTo(Module* module);
                bool connect(Module* module);
                bool disconnect(Module* module);
            private:
                friend class LocalModule;
                friend class RemoteModule;

                Module();

                typedef std::list<Module*> Modules;
                Modules connections;
        };
    }
}
