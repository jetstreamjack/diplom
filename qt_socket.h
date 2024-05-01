#pragma once

#include "i_socket.h"

#include <vector>
#include <string>

namespace socket {

class QtSocket : public ISocket
{
public:
    virtual ~ISocket() = default;

    // add commentary
    std::string ReadAll() override;

    void WriteAll(std::string message) override;

private:
    QTcpSocket *m_socket;
};

} // socket
