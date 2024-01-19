#include "Helper/Forward.hpp"
#include "Server/Listener.hpp"

int main()
{
    int threads = 8;

    asio::io_context ioc { threads };

    // Create and launch a listening port
    std::make_shared<Listener>(ioc, tcp::endpoint { asio::ip::make_address("127.0.0.1"), 13126u })->run();

    // Run the I/O service on the requested number of threads
    std::vector<std::thread> v;
    v.reserve(threads);
    for (auto i = threads; i > 0; --i)
        v.emplace_back([&ioc] { ioc.run(); });
    ioc.run();

    return EXIT_SUCCESS;
}
