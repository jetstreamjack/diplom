#pragma once

#include "i_connection.h"

#include <vector>
#include <string>
#include <memory>

namespace connection {

class IConnectionObserver
{
public:
    virtual ~IConnectionObserver() = default;

    // add commentary
    virtual void ObserveConnection(std::unique_ptr<IConnection> connection) = 0;
};

} // namespace connection
