#include <Veritas/Orchestra/Messaging/List.h>
#include <Veritas/Orchestra/Messaging/Content.h>

using namespace Veritas;
using namespace Orchestra;
using namespace Messaging;

List::List() {}
List::List(uint32 size) : list(size) {}
List::List(const std::initializer_list<Content> &il) : list(il) {}

List& List::setSize(uint32 size) {
    list.setSize(size);
    return *this;
}
uint32 List::getSize() const { return list.getSize(); }

Content& List::operator[](uint32 index) { return list[index]; }
const Content& List::operator[](uint32 index) const { return list[index]; }
