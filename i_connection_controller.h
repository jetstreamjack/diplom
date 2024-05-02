#pragma once

#include <vector>
#include <string>

namespace connection_controller {

using ClientHandle = uint32_t;

class IConnectionController
{
public:
    virtual ~IConnectionController() = default;

    virtual ClientHandle RegisterClient() = 0;

    virtual void UnregisterClient(ClientHandle clientHandle) = 0;

    virtual void ProcessNewTask(ClientHandle clientHandle, std::string taskRequest) = 0;

    virtual double GetTaskResult(ClientHandle clientHandle) = 0;
};

} // balancer
