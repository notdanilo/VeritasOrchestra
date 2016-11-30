#include <Veritas/Orchestra/Messaging/Interface.h>

using namespace Veritas;
using namespace Orchestra;
using namespace Messaging;
using namespace Data;

Interface::Interface(const String &name) : name(name), callback(0) {}
Interface::Interface(const Interface &copy) : name(copy.name), callback(copy.callback) {}
Interface::Interface(Interface &&move) : name(std::move(move.name)), callback(std::move(move.callback)) {}
Interface::~Interface() {}

Interface& Interface::operator=(const Interface& copy) {
    name = copy.name;
    callback = copy.callback;
    return *this;
}

Interface& Interface::operator=(Interface&& move) {
    name = std::move(move.name);
    callback = std::move(move.callback);
    return *this;
}

const String& Interface::getName() const { return name; }

Interface& Interface::require(const String &field) {
    return *this;
}

Interface& Interface::setCallback(std::function<void (const Message &)> callback) {
    this->callback = callback;
    return *this;
}

void Interface::call(const Message &message) { if (callback) callback(message); }
