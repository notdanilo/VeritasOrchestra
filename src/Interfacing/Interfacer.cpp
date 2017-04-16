#include <Veritas/Orchestra/Interfacing/Interfacer.h>

using namespace Veritas;
using namespace Orchestra;
using namespace Interfacing;
using namespace Data;

Interfacer::Interfacer() {}

Interfacer::Interfacer(const Interfacer& copy) {
    for (const Groups::value_type& group : copy.groups)
        for (const Interfaces::value_type& interface : group.second)
            #warning virtual Interface::clone needs to be implemented (take 'any' as reference) so delete can be called
            set(group.first, &interface.second);
}
Interfacer::Interfacer(Interfacer&& move) {
    groups = std::move(move.groups);
}
Interfacer::~Interfacer() {
    for (Groups::value_type& group : groups)
        for (Interfaces::value_type interface : group.second)
            ;//delete &interface.second;
}

Interfacer& Interfacer::set(const String& group, Interface *interface) {
    interface->onSet(this);
    Interfaces& interfaces = groups[group];
    interfaces.emplace(interface->getName(), *interface);
    return *this;
}

Interfacer::Groups& Interfacer::getGroups() { return groups; }
const Interfacer::Groups& Interfacer::getGroups() const { return groups; }

Interfacer::Interfaces* Interfacer::getInterfaces(const String& group) {
    try { return &groups.at(group); }
    catch (...) { return 0; }
}
const Interfacer::Interfaces* Interfacer::getInterfaces(const String& group) const {
    try { return &groups.at(group); }
    catch (...) { return 0; }
}
