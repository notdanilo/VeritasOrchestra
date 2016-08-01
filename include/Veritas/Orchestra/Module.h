#pragma once

#include "Message.h"

namespace Veritas {
    namespace Orchestra {
        class Module : public Message::Listener {
            public:
                Module();
                virtual ~Module();

                bool isConnectedTo(Module* module);
                bool connect(Module* module);
                bool disconnect(Module* module);

                virtual void run();
            private:
                typedef std::list<Module*> Modules;
                Modules connections;
        };
    }
}

Veritas::Orchestra::Module* EntryPoint();
#define SET_ENTRY_POINT(EP) Veritas::Orchestra::Module* EntryPoint() { return new EP(); }
