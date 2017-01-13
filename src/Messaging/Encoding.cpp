#include <Veritas/Orchestra/Messaging/Encoding.h>

using namespace Veritas;
using namespace Orchestra;
using namespace Messaging;

Encoding::Encoding(TYPE type, uint8 exponent) {
    info = (type << 7) | (exponent & 0x7F);
}

Encoding::TYPE Encoding::getType() const { return (TYPE) (info >> 7); }
uint8 Encoding::getExponent() const { return info & 0x7F; }
