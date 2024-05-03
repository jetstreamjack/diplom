#pragma once

#include <vector>
//#include <cstdin.h>
#include <string>

namespace server {

class IServer
{
public:
    virtual ~IServer() = default;

    // add commentary
    virtual void Run(std::string listenOn) = 0;

    virtual void Stop() = 0;
};

} // server
