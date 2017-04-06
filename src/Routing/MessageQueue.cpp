#include <Veritas/Orchestra/Routing/MessageQueue.h>

using namespace Veritas;
using namespace Orchestra;
using namespace Routing;
using namespace Messaging;

void MessageQueue::receive(const Message &message) {
    std::lock_guard<std::mutex> lock(mutex);
    queue.push(message);
}

void MessageQueue::receive(Message&& message) {
    std::lock_guard<std::mutex> lock(mutex);
    queue.emplace(std::move(message));
}

Message MessageQueue::consume() {
    std::lock_guard<std::mutex> lock(mutex);
    Message ans = queue.front();
    queue.pop();
    return ans;
}

uint32 MessageQueue::getAmmount() const { return queue.size(); }
