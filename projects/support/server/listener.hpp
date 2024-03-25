#pragma once

#include <memory>

#include "server/fail.hpp"
#include "server/session.hpp"
#include "utils/boost.hpp"

namespace lhg::server
{

class Dispatcher;

// Accepts incoming connections and launches the sessions
class Listener : public std::enable_shared_from_this<Listener>
{
public:
    Listener(Dispatcher* dispatcher, asio::io_context& ioc, tcp::endpoint endpoint)
        : dispatcher_(dispatcher)
        , ioc_(ioc)
        , acceptor_(asio::make_strand(ioc))
    {
        beast::error_code ec;

        // Open the acceptor
        acceptor_.open(endpoint.protocol(), ec);
        if (ec) {
            fail(ec, "open");
            return;
        }

        // Allow address reuse
        acceptor_.set_option(asio::socket_base::reuse_address(true), ec);
        if (ec) {
            fail(ec, "set_option");
            return;
        }

        // Bind to the server address
        acceptor_.bind(endpoint, ec);
        if (ec) {
            fail(ec, "bind");
            return;
        }

        // Start listening for connections
        acceptor_.listen(asio::socket_base::max_listen_connections, ec);
        if (ec) {
            fail(ec, "listen");
            return;
        }
    }

    // Start accepting incoming connections
    void run() { do_accept(); }

    unsigned short port()
    {
        beast::error_code ec;

        auto endpoint = acceptor_.local_endpoint(ec);
        if (ec) {
            fail(ec, "port");
            return 0;
        }

        return endpoint.port();
    }

private:
    void do_accept()
    {
        // The new connection gets its own strand
        acceptor_.async_accept(
            asio::make_strand(ioc_),
            beast::bind_front_handler(&Listener::on_accept, shared_from_this()));
    }

    void on_accept(beast::error_code ec, tcp::socket socket)
    {
        if (ec) {
            fail(ec, "accept");
            return;
        }
        else {
            std::make_shared<Session>(dispatcher_, std::move(socket))->run();
        }

        do_accept();
    }

    Dispatcher* dispatcher_;
    asio::io_context& ioc_;
    tcp::acceptor acceptor_;
};

} // namespace lhg::server
