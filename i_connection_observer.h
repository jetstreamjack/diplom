#pragma once

#include "i_connection.h"

#include <vector>
#include <string>
#include <memory>

namespace connection {

/**
 * @brief It is used to maintain current connections
 * @details as an example, close unnecessary connections
 */
class IConnectionObserver
{
public:
    virtual ~IConnectionObserver() = default;

    /**
     * @brief registers a connection for its maintenance
     * 
     * @param connection - incoming connection
     */
    virtual void ObserveConnection(std::unique_ptr<IConnection> connection) = 0;
};

} // namespace connection
