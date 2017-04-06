#include <Veritas/Orchestra/Messaging/Messaging.h>
#include <Veritas/Orchestra/Messaging/Form.h>

#include <cstdlib>

using namespace Veritas::Orchestra;
using namespace Messaging;
using namespace Veritas::Data;

Message::Message() {}
Message::Message(const Message& message) : origin(message.origin), destiny(message.destiny), content(message.content), interface(message.interface) {}
Message::Message(Message&& message) : origin(std::move(message.origin)), destiny(std::move(message.destiny)), content(std::move(message.content)), interface(std::move(message.interface)) {}
Message::~Message() {}

Message& Message::set(const Content &content) {
    this->content = content;
    return *this;
}

Message& Message::set(Content&& content) {
    this->content = std::move(content);
    return *this;
}

Message& Message::set(const String& field, const Content& content) {
    if (getContent().getType() != Content::FORM) set(Form());
    ((Form&) this->content).set(field, content);
    return *this;
}
Message& Message::set(const String& field, Content&& content) {
    if (getContent().getType() != Content::FORM) set(Form());
    ((Form&) this->content).set(field, std::move(content));
    return *this;
}

Content& Message::getContent() { return content; }
const Content& Message::getContent() const { return content; }
const Content& Message::get(const String& field) const {
    return content.getType() ? ((const Form&) content).get(field) : Content::Empty;
}

Message& Message::setOrigin(const Address& origin) {
    this->origin = origin;
    return *this;
}
const Address& Message::getOrigin() const { return origin; }

Message& Message::setDestiny(const Address& destiny) {
    this->destiny = destiny;
    return *this;
}
const Address& Message::getDestiny() const { return destiny; }

Message& Message::setInterface(const String& interface) {
    this->interface = interface;
    return *this;
}
const String& Message::getInterface() const { return interface; }

Message& Message::operator=(const Message& message) {
    content = message.content;
    origin = message.origin;
    destiny = message.destiny;
    interface = message.interface;
    return *this;
}
Message& Message::operator=(Message&& message) {
    content = std::move(message.content);
    origin = std::move(message.origin);
    destiny = std::move(message.destiny);
    interface = std::move(message.interface);
    return *this;
}
