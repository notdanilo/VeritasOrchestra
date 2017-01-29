#include <Veritas/Orchestra/Interfacing/Interface.h>
#include <Veritas/Orchestra/LocalModule.h>

using namespace Veritas;
using namespace Orchestra;
using namespace Interfacing;
using namespace Data;

Interface::Interface(const String& name) : name(name) {}
Interface::Interface(const Interface &copy) : name(copy.name) {}
Interface::Interface(Interface &&move) : name(std::move(move.name))  {}
Interface::~Interface() {}

Interface& Interface::operator=(const Interface& copy) {
    name = copy.name;
    return *this;
}

Interface& Interface::operator=(Interface&& move) {
    name = std::move(move.name);
    return *this;
}

const String& Interface::getName() const { return name; }
