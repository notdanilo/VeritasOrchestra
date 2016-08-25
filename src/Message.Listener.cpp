#include <Veritas/Orchestra/Message.h>

using namespace Veritas::Orchestra;
using Veritas::Data::String;
using Veritas::any;

Message::Listener::~Listener() {
    for (CallbacksMap::iterator it = map.begin(); it != map.end(); it++) {
        CallbacksMap::value_type pair = *it;
        delete ((Callbacks*) pair.second);
    }
}

Message::Listener::Callback::Callback(std::function<void(const Message& m)> callback, const any &callbackData) : callback(callback), callbackData(callbackData) {}
void Message::Listener::Callback::operator()(Message &m) {
    m.setCallbackData(callbackData);
    callback(m);
}

void Message::Listener::on(const Veritas::Data::String &message, std::function<void(const Message& m)> callback, const any& callbackData) {
    Callbacks* callbacks = map[message];
    if (!callbacks) {
        callbacks = new Callbacks();
        map[message] = callbacks;
    }
    callbacks->push_back(Callback(callback, callbackData));
}

void Message::Listener::receive(Message &message) const {
    Callbacks* callbacks = const_cast<Listener*>(this)->map[message.getName()];
    if (callbacks)
        for (Callbacks::iterator it = callbacks->begin(); it != callbacks->end(); it++) {
            Callback f = *it;
            f(message);
        }

    // Everything will be redirected to ""
    callbacks = const_cast<Listener*>(this)->map[""];
    if (callbacks)
        for (Callbacks::iterator it = callbacks->begin(); it != callbacks->end(); it++) {
            Callback f = *it;
            f(message);
        }
}
