#include <Veritas/Orchestra/Interfacing/Context.h>

using namespace Veritas;
using namespace Orchestra;
using namespace Interfacing;
using namespace Messaging;

Context::Context(uint32 requestID) : requestID(requestID) {}
Context::Context(const Context& copy) : requestID(copy.requestID), content(copy.content) {}
Context::Context(Context&& copy) : requestID(std::move(copy.requestID)), content(std::move(copy.content)) {}

Context& Context::operator=(const Context& copy) {
    requestID = copy.requestID;
    content = copy.content;
    return *this;
}

Context& Context::operator=(Context&& move) {
    requestID = std::move(move.requestID);
    content = std::move(move.content);
    return *this;
}

uint32 Context::getRequestID() const { return requestID; }
void Context::setContent(const Content &content) { this->content = content; }
void Context::setContent(Content&& content) { this->content = std::move(content); }
const Content& Context::getContent() const { return content; }
