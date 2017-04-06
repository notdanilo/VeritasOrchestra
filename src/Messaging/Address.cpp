#include <Veritas/Orchestra/Messaging/Address.h>
#include <Veritas/Data/Data.h>

using namespace Veritas;
using namespace Orchestra;
using namespace Messaging;
using namespace Data;
using namespace Encoding;

Address::Address() {}
Address::Address(const void* address) : Address(Base16().encode(&address, sizeof(address))) {}
Address::Address(const String &address) : string(address) {}
Address::Address(const Address &address) : string(address.string) {}
Address::Address(Address &&address) : string(std::move(address.string)) {}
Address::~Address() {}

Address& Address::setString(const String &string) {
    this->string = string;
    return *this;
}
const String& Address::getString() const { return string; }

bool Address::operator==(const Address& address) const { return string == address.string; }
Address& Address::operator=(const Address& address) {
    string = address.string;
    return *this;
}
Address& Address::operator=(Address&& address) {
    string = std::move(address.string);
    return *this;
}

void* Address::getLocalAddress() const {
    return (void*) *(uintptr_t*) Encoding::Base16().decode(getString()).getData();
}
