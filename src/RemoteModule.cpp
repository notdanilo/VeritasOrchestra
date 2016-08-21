#include <Veritas/Orchestra/RemoteModule.h>

using namespace Veritas;
using namespace Data;
using namespace Orchestra;

RemoteModule::RemoteModule(const String &address) : address(address) {}
RemoteModule::~RemoteModule() {}

String RemoteModule::getAddress() const { return address; }
