#include <Veritas/Orchestra/Message.h>

using Veritas::Orchestra::Message;
using Veritas::Data::String;

Message& Message::set(const String& field, const Veritas::any& data) {
    map[field] = data;
    return *this;
}

Veritas::any Message::get(const String& field) const { return const_cast<Message*>(this)->map[field]; }
