#pragma once

#include <vector>
#include <string>

namespace socket {

using PathVec = std::vector<double>;
using TaskId = unsigned int;

class ISocket
{
public:
    virtual ~ISocket() = default;

    // add commentary
    virtual std::string ReadAll() = 0;

    virtual void WriteAll(std::string message) = 0;
};

} // socket
