#pragma once

#include <vector>

namespace connection {

enum class ConnectionState : uint8_t
{
    Disconnected,
    Connected
}

class IConnection
{
public:
    virtual ~IConnection() = default;

    // add commentary
    virtual void StopConnection() = 0;

    virtual void StartObserving() = 0;

    virtual ConnectionState GetConnectionState() = 0;
};

} // connection
