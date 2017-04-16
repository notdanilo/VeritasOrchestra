#pragma once
#include <functional>
#include <Veritas/Orchestra/Messaging/Message.h>

namespace Veritas {
    namespace Orchestra {
        namespace Computing {
            class Module;
            class LocalModule;
        }
        namespace Interfacing {
            class Interfacer;
            class Interface {
                public:
                    Interface(const Data::String& name);
                    Interface(const Interface& copy);
                    Interface(Interface&& move);
                    virtual ~Interface();

                    Interface& operator=(const Interface& copy);
                    Interface& operator=(Interface&& move);

                    const Data::String& getName() const;

                    //setSignature for message x interface compatibility checking
                protected:
                    friend class Interfacer;
                    virtual void onSet(Interfacer* interfacer);
                private:
                    Data::String name;

                    friend class Orchestra::Computing::LocalModule;
            };
        }
    }
}
