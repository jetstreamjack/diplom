#include "connection_observer.h"

#include <vector>
#include <string>
#include <random>
#include <chrono>

namespace connection {

namespace {
    SockId GenerateTaskId()
    {
        std::mt19937 gen(std::chrono::system_clock::now().time_since_epoch().count());
        std::uniform_int_distribution<int> distr(0, 1000000);
        //TODO(odnorob): add check on unique 
        return distr(gen);
    }

} // namespace

ConnectionObserver::ConnectionObserver(){}

    // add commentary
void ConnectionObserver::ObserveConnection(std::unique_ptr<IConnection> connection)
{
    connection->StartObserving();
    m_connectionMap.insert(std::make_pair(GenerateTaskId(), std::move(connection)));
}

} // namespace connection
