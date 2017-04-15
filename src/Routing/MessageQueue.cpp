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

Message MessageQueue::consume() throw(std::exception) {
    std::lock_guard<std::mutex> lock(mutex);
    if (!queue.size()) throw std::exception();
    Message ans = queue.front();
    queue.pop();
    return ans;
}
