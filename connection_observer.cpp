// #pragma once

// #include "connection_observer.h"

// #include <vector>
// #include <string>

// namespace server_controller {

// namespace {
//     SockId GenerateTaskId()
//     {
//         std::mt19937 gen(std::chrono::system_clock::now().time_since_epoch().count());
//         std::uniform_int_distribution<int> distr(0, 1000000);
//         //TODO(odnorob): add check on unique 
//         return distr(gen);
//     }

// } // namespace

// explicit ConnectionObserver::ConnectionObserver(){}
//     //virtual ~IConnectionObserver() = default;

//     // add commentary
// void ConnectionObserver::ObserveSocket(std::unique_ptr<ISocket> socket)
// {
//     m_sockMap.insert(std::make_pair(GenerateTaskId(), std::move(socket)));
// }
// //public slots: 
// //void readyRead();

// //private:
//     SocketMap m_sockMap;
// //};

// } // server_controller
