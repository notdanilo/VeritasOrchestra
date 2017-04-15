#include <Veritas/Orchestra/Computing/Runner.h>

using namespace Veritas;
using namespace Orchestra;
using namespace Computing;
using namespace Interfacing;

const Interfacer& Runner::getInterfacer() {
    static Interfacer interfacer = Interfacer(LocalModule::getInterfacer()).set("Output", OutputInterface("Run"));
    return interfacer;
}

Runner::Runner()
    : LocalModule(getInterfacer())
    , publisher(this)
{}

void Runner::run() {
    publisher.publish("Run");
}
