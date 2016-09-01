#include <Veritas/Orchestra/Interfaceable.h>

using namespace Veritas::Orchestra;

Interfaceable::Interfaceable() {
    on("", [=](const Message& m) { // Move it to Interfaceable constructor
        if (any_cast<void*>(m.getSource()) != any_cast<void*>(m.getDestiny())) {
            any_method *am = methodMap[m.getName()];
            if (am) {
                const Message::SetOrder& order = m.getSetOrder();
                any_args args;
                for (auto i : order) args.push_back(m.get(i));
                try { (*am)(args); } catch (...) { /* Wrong number of arguments */ }
            }
        }
    });
}

Interfaceable::~Interfaceable() {
    for (auto i : methodMap) delete i.second;
}
