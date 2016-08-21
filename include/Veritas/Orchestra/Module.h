#pragma once

#include "Message.h"

namespace Veritas {
    namespace Orchestra {
        class Module : public Message::Listener {
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
