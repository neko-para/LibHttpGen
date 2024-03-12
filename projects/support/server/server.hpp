#pragma once

#include "server/listener.hpp"
#include "utils/forward.hpp"

namespace lhg::server
{

class Dispatcher;

class Server
{
public:
    Server(Dispatcher* dispatcher, unsigned short port, int threads = 8) : ioc(threads), threads(threads)
    {
        listener =
            std::make_shared<Listener>(dispatcher, ioc, tcp::endpoint { asio::ip::make_address("127.0.0.1"), port });
    }

    void run()
    {
        listener->run();

        // Run the I/O service on the requested number of threads
        v.reserve(threads);
        for (auto i = threads; i > 0; --i)
            v.emplace_back([&ioc = this->ioc] { ioc.run(); });
    }

    void sync_run()
    {
        run();
        ioc.run();
    }

    void stop() { ioc.stop(); }

private:
    asio::io_context ioc;
    std::shared_ptr<Listener> listener;
    int threads;
    std::vector<std::thread> v;
};

}
