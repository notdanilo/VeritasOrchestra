#pragma once

#include "InputInterface.h"
#include "OutputInterface.h"
#include <map>

#warning Create virtual Interface::clone (check Interfacer.cpp)

namespace Veritas {
    namespace Orchestra {
        namespace Interfacing {
            class Interfacer {
                public:
                    typedef std::map<Data::String, Interface&> Interfaces;
                    typedef std::map<Data::String, Interfaces> Groups;

                    Interfacer(const Interfacer& copy);
                    Interfacer(Interfacer&& move);
                    ~Interfacer();

                    Interfacer& operator=(const Interfacer& copy);
                    Interfacer& operator=(Interfacer&& move);

                    Groups& getGroups();
                    const Groups& getGroups() const;

                    template <class T>
                    Interfacer& set(const Data::String& group, T&& t) {
                        Interface* interface = new T(std::forward<T>(t));
                        return set(group, interface);
                    }

                    const Interfaces* getInterfaces(const Data::String& group) const;
                    Interfaces* getInterfaces(const Data::String &group);
                private:
                    friend class Veritas::Orchestra::LocalModule;
                    Interfacer();

                    Groups groups;

                    void erase();
                    Interfacer& set(const Data::String& group, Interface* interface);
            };
        }
    }
}
