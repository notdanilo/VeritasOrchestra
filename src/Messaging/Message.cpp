#include <Veritas/Orchestra/Messaging/Messaging.h>
#include <cstdlib>

using namespace Veritas::Orchestra;
using namespace Messaging;
using namespace Veritas::Data;

Message::Message(const Buffer &serializedMessage) : name(serializedMessage) {
    uint32 offset = name.getSerialSize();
    while (serializedMessage.get<uint8>(offset++)) {
        Content field(Buffer(serializedMessage, offset)); offset += field.getSerialSize();
        Content content(Buffer(serializedMessage, offset)); offset += content.getSerialSize();
        set(field.getString(), content);
    }
}

Message::Message(const String& name) : name(name) {}
Message::~Message() {}

String Message::getName() const {
    return name.getString();
}

Message& Message::setOrigin(const String &origin) { this->origin = origin; }
const String& Message::getOrigin() const { return origin; }

Message& Message::set(const String &field, const String &content) { return set(field, Content(content)); }
Message& Message::set(const String &field, const Content &content) {
    contents[field] = content;
    return *this;
}

const Content& Message::get(const String &field) const {
    try { return contents.at(field); }
    catch (...) { return Content::Empty; }
}

Buffer Message::serialize() const {
    Buffer buffer;
    buffer.append(name.serialize());

    uint8 fields;
    for (auto i : contents) {
        fields = 1;
        buffer.append(&fields, 1);
        buffer.append(Content(i.first).serialize());
        buffer.append(i.second.serialize());
    }

    fields = 0;
    buffer.append(&fields, 1);
    return buffer;
}
