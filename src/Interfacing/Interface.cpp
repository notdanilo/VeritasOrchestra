#include <Veritas/Orchestra/Interfacing/Interface.h>
#include <Veritas/Orchestra/LocalModule.h>

using namespace Veritas;
using namespace Orchestra;
using namespace Interfacing;
using namespace Data;

Interface::Interface(const String &name, LocalModule *module) : name(name), module(module) {}
Interface::Interface(Interface &&move) : name(std::move(move.name)), module(std::move(move.module)) {}
Interface::~Interface() {}

Interface& Interface::operator=(Interface&& move) {
    name = std::move(move.name);
    return *this;
}

const String& Interface::getName() const { return name; }

LocalModule* Interface::getModule() const { return module; }