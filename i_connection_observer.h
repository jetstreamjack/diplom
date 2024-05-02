#pragma once

#include <vector>
#include <string>

namespace connection_controller {

class IConnectionObserver
{
public:
    virtual ~IConnectionObserver() = default;

    // add commentary
    virtual void ObserveConnection(std::unique_ptr<IConnection> connection) = 0;
};

} // namespace connection_controller
