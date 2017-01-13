#include <Veritas/Orchestra/Messaging/Number.h>

using namespace Veritas;
using namespace Data;
using namespace Orchestra;
using namespace Messaging;

Number::Number(int8 n) : buffer(sizeof(n)), encoding(Encoding::INT, 1) { buffer.set(0, n); }
Number::Number(int16 n) : buffer(sizeof(n)), encoding(Encoding::INT, 2) { buffer.set(0, n); }
Number::Number(int32 n) : buffer(sizeof(n)), encoding(Encoding::INT, 4) { buffer.set(0, n); }
Number::Number(int64 n) : buffer(sizeof(n)), encoding(Encoding::INT, 8) { buffer.set(0, n); }

Number::Number(uint8 n) : buffer(sizeof(n)), encoding(Encoding::INT, 1) { buffer.set(0, n); }
Number::Number(uint16 n) : buffer(sizeof(n)), encoding(Encoding::INT, 2) { buffer.set(0, n); }
Number::Number(uint32 n) : buffer(sizeof(n)), encoding(Encoding::INT, 4) { buffer.set(0, n); }
Number::Number(uint64 n) : buffer(sizeof(n)), encoding(Encoding::INT, 8) { buffer.set(0, n); }

Number::Number(float32 n) : buffer(sizeof(n)), encoding(Encoding::FLOAT, 4) { buffer.set(0, n); }
Number::Number(float64 n) : buffer(sizeof(n)), encoding(Encoding::FLOAT, 8) { buffer.set(0, n); }

Number::~Number() {}

Encoding Number::getEncoding() const { return encoding; }

Buffer& Number::getBuffer() { return buffer; }
const Buffer& Number::getBuffer() const { return buffer; }

Number::operator int8() const { return buffer.get<int8>(0); }
Number::operator int16() const { return buffer.get<int16>(0); }
Number::operator int32() const { return buffer.get<int32>(0); }
Number::operator int64() const { return buffer.get<int64>(0); }

Number::operator uint8() const { return buffer.get<uint8>(0); }
Number::operator uint16() const { return buffer.get<uint16>(0); }
Number::operator uint32() const { return buffer.get<uint32>(0); }
Number::operator uint64() const { return buffer.get<uint64>(0); }

Number::operator float32() const { return buffer.get<float32>(0); }
Number::operator float64() const { return buffer.get<float64>(0); }
