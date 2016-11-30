#include <Veritas/Orchestra/Messaging/Content.h>
#include <Veritas/Data/Array.h>

using namespace Veritas;
using namespace Orchestra;
using namespace Messaging;
using namespace Data;

const Content Content::Empty;

Content::Content() : encoding(Encoding::INT, 0) {}
Content::Content(const  int8 content) : encoding(Encoding::INT, 0), buffer(1) { this->buffer.get<int8>(0) = content; }
Content::Content(const int16 content) : encoding(Encoding::INT, 1), buffer(2) { this->buffer.get<int16>(0) = content; }
Content::Content(const int32 content) : encoding(Encoding::INT, 2), buffer(4) { this->buffer.get<int32>(0) = content; }
Content::Content(const int64 content) : encoding(Encoding::INT, 3), buffer(8) { this->buffer.get<int64>(0) = content; }
Content::Content(const String& content) : encoding(Encoding::INT, 0), buffer(content.getBuffer()) {}

Content::Content(const Buffer &buffer, const Encoding &encoding) : encoding(encoding), buffer(buffer) {}
Content::Content(const Array<int8 > &content) : Content(content.getBuffer(), Encoding(Encoding::INT, 0)) {}
Content::Content(const Array<int16> &content) : Content(content.getBuffer(), Encoding(Encoding::INT, 1)) {}
Content::Content(const Array<int32> &content) : Content(content.getBuffer(), Encoding(Encoding::INT, 2)) {}
Content::Content(const Array<int64> &content) : Content(content.getBuffer(), Encoding(Encoding::INT, 3)) {}
Content::Content(const Array<float32> &content) : Content(content.getBuffer(), Encoding(Encoding::FLOAT, 2)) {}
Content::Content(const Array<float64> &content) : Content(content.getBuffer(), Encoding(Encoding::FLOAT, 3)) {}
Content::Content(const Buffer& serializedContent) : encoding(serializedContent) {
    uint32 elements = 0;
    for (uint32 i = 0; i < 4; i++)
        elements |= serializedContent.get<uint8>(i + 1) << i;
    buffer.setSize(elements * (1 << getEncoding().getExponent()));
    buffer.copy(serializedContent, buffer.getSize(), 5);
}

Messaging::Encoding Content::getEncoding() const { return encoding; }
uint32 Content::getElements() const { return buffer.getSize() / (1 << getEncoding().getExponent()); }

int8  Content::getInt8(uint32 index) const { return buffer.get<int8>(index); }
int16 Content::getInt16(uint32 index) const { return buffer.get<int16>(index); }
int32 Content::getInt32(uint32 index) const { return buffer.get<int32>(index); }
int64 Content::getInt64(uint32 index) const { return buffer.get<int64>(index); }
float32 Content::getFloat32(uint32 index) const { return buffer.get<float32>(index); }
float64 Content::getFloat64(uint32 index) const { return buffer.get<float64>(index); }
String Content::getString() const {
    String ret;
    ret.getBuffer() = getBuffer();
    return ret;
}

Buffer& Content::getBuffer() { return buffer; }
const Buffer& Content::getBuffer() const { return buffer; }

Buffer Content::serialize() const {
    Buffer buffer;
    buffer.append(&encoding, 1);

    uint32 elements = getElements();
    for (uint32 i = 0; i < 4; i++) {
        uint8 belements = elements >> i;
        buffer.append(&belements, 1);
    }

    #warning Implement it with bit shifting so it's endianness independent
    buffer.append(this->buffer);
    return buffer;
}
uint32 Content::getSerialSize() const { return sizeof(Encoding) + sizeof(uint32) + buffer.getSize(); }
