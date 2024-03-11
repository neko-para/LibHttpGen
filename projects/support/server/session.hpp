#pragma once

#include <memory>

#include "server/dispatcher.hpp"
#include "server/fail.hpp"
#include "utils/forward.hpp"

namespace lhg::server
{

// Handles an HTTP server connection
class Session : public std::enable_shared_from_this<Session>
{
public:
    // Take ownership of the stream
    Session(Dispatcher* dispatcher, tcp::socket&& socket) : dispatcher_(dispatcher), stream_(std::move(socket)) {}

    // Start the asynchronous operation
    void run()
    {
        asio::dispatch(stream_.get_executor(), beast::bind_front_handler(&Session::do_read, shared_from_this()));
    }

    void do_read()
    {
        req_ = {};

        stream_.expires_after(std::chrono::seconds(30));

        http::async_read(stream_, buffer_, req_, beast::bind_front_handler(&Session::on_read, shared_from_this()));
    }

    void on_read(beast::error_code ec, std::size_t bytes_transferred)
    {
        std::ignore = bytes_transferred;

        if (ec == http::error::end_of_stream) {
            return do_close();
        }

        if (ec) {
            return fail(ec, "read");
        }

        send_response(dispatcher_->handle_request(std::move(req_)));
    }

    void send_response(http::message_generator&& msg)
    {
        bool keep_alive = msg.keep_alive();

        // Write the response
        beast::async_write(stream_, std::move(msg),
                           beast::bind_front_handler(&Session::on_write, shared_from_this(), keep_alive));
    }

    void on_write(bool keep_alive, beast::error_code ec, std::size_t bytes_transferred)
    {
        std::ignore = bytes_transferred;

        if (ec) {
            return fail(ec, "write");
        }

        if (!keep_alive) {
            return do_close();
        }

        do_read();
    }

    void do_close()
    {
        // Send a TCP shutdown
        beast::error_code ec;
        stream_.socket().shutdown(tcp::socket::shutdown_send, ec);

        // At this point the connection is closed gracefully
    }

private:
    Dispatcher* dispatcher_;
    beast::tcp_stream stream_;
    beast::flat_buffer buffer_;
    http::request<http::string_body> req_;
};

} // namespace lhg::server
