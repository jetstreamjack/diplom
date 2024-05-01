// #pragma once

// #include <vector>
// #include <string>

// namespace server_controller {

// using SockId = int;
// //using SockPair = std::pair<SockId, std::unique_ptr>
// using SocketMap = std::unordored_map<SockId, std::unique_ptr<ISocket>>;

// class ConnectionObserver : public IConnectionObserver
// {
// public:
//     explicit ConnectionObserver();
//     //virtual ~IConnectionObserver() = default;

//     // add commentary
//     void ObserveSocket(std::unique_ptr<ISocket> socket) override;
// // public slots: 
// //     void readyRead();

// private:
//     SocketMap m_sockMap;
// };

// } // server_controller
