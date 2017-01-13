#pragma once
#include <functional>
#include "../Messaging/Message.h"

namespace Veritas {
    namespace Orchestra {
        class LocalModule;
        namespace Interfacing {
            class Interface {
                public:
                    Interface(const Data::String& name, LocalModule* module);
                    Interface(const Interface& copy);
                    Interface(Interface&& move);
                    ~Interface();

                    Interface& operator=(const Interface& copy);
                    Interface& operator=(Interface&& move);

                    virtual void attach(LocalModule* module);

                    const Data::String& getName() const;

                    //setSignature for message x interface compatibility checking

                    LocalModule* getModule() const;
                private:
                    Data::String name;

                    friend class Orchestra::LocalModule;
                    LocalModule* module;
                    void set(LocalModule *module);
            };
        }
    }
}
