#include <Veritas/Orchestra/Message.h>

using namespace Veritas::Orchestra;
using Veritas::Data::String;

Message::Listener::~Listener() {
    for (CallbacksMap::iterator it = map.begin(); it != map.end(); it++) {
        CallbacksMap::value_type pair = *it;
        delete ((Callbacks*) pair.second);
    }
}

Message::Listener::Callback::Callback(void (*f)(const Message &), const any &callbackData) : f(f), callbackData(callbackData) {}
void Message::Listener::Callback::operator()(Message &m) {
    m.set("Callback-Data", callbackData);
    f(m);
}

void Message::Listener::on(const Veritas::Data::String &message, void (*callback)(const Message&), const any& callbackData) {
    Callbacks* callbacks = map[message];
    if (!callbacks) {
        callbacks = new Callbacks();
        map[message] = callbacks;
    }
    callbacks->push_back(Callback(callback, callbackData));
}
void Message::Listener::dispatch(const Veritas::Data::String& messageName) const {
    Message m(messageName);
    dispatch(m);
}

void Message::Listener::dispatch(Message &message) const {
    Callbacks* callbacks = const_cast<Listener*>(this)->map[message.getName()];
    if (callbacks)
        for (Callbacks::iterator it = callbacks->begin(); it != callbacks->end(); it++) {
            Callback f = *it;
            f(message);
        }
}
