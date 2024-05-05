#pragma once

#include <vector>
#include <string>

namespace server {

class IServer
{
public:
    virtual ~IServer() = default;

    /**
     * @brief Run server
     * 
     * @param listenOn - the ip on which the server is listening
     */
    virtual void Run(std::string listenOn) = 0;

    /**
     * @brief Stop server
     */
    virtual void Stop() = 0;
};

} // server
