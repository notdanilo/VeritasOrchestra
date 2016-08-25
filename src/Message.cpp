#include <Veritas/Orchestra/Message.h>

using Veritas::Orchestra::Message;
using Veritas::Data::String;

Message::Message(const String& name) : name(name) {}

void Message::setName(const String &name) { this->name = name; }
String Message::getName() const { return name; }

Message& Message::add(const Veritas::any& data) { return set(String::format("%d", order.size()), data); }

Message& Message::set(const String& field, const Veritas::any& data) {
    map[field] = data;

    for (auto& i : order) if (i == field) return *this; // Already exists
    order.push_back(field);

    return *this;
}
Veritas::any Message::get(const String& field) const { return const_cast<Message*>(this)->map[field]; }

const Message::SetOrder& Message::getSetOrder() const { return order; }

Message& Message::setDestiny(Veritas::any destiny) { this->destiny = destiny; return *this; }
Veritas::any Message::getDestiny() const { return destiny; }

Message& Message::setSource(Veritas::any source) { this->source = source; return *this; }
Veritas::any Message::getSource() const { return source; }

Message& Message::setCallbackData(Veritas::any callbackData) { this->callbackData = callbackData; return *this; }
Veritas::any Message::getCallbackData() const { return callbackData; }
