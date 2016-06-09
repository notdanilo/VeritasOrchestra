#include <Veritas/Orchestra/Message.h>

using Veritas::Orchestra::Message;
using Veritas::Data::String;

Message& Message::set(const String& field, void *data) {
    map[field] = data;
    return *this;
}

void* Message::get(const String& field) const { return (void*) const_cast<Message*>(this)->map[field]; }
