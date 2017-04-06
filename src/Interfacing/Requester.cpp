#include <Veritas/Orchestra/Interfacing/Requester.h>

using namespace Veritas;
using namespace Data;
using namespace Orchestra;
using namespace Interfacing;
using namespace Messaging;

Requester::Requester(LocalModule* module) : Requester(*module) {}
Requester::Requester(LocalModule& module) : sender(module) {}

void Requester::request(const String& interface, const Module *destination, const Message &message, const any& context) { request(interface, *destination, message, context); }
void Requester::request(const String& interface, const Module &destination, const Message &message, const any& context) {
    RequestInterface& requestInterface((RequestInterface&) sender.getModule().getClassInterfacer().getInterfaces("Request")->at(interface));
    requestInterface.request(sender.getModule(), destination, message, context);
}

const LocalModule& Requester::getModule() const { return sender.getModule(); }
