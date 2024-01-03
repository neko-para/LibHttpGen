#include "Handle/Dispatcher.hpp"
#include "Helper/Format.hpp"
#include <iostream>

http::message_generator handle_request(http::request<http::string_body>&& req)
{
    http::response<http::string_body> res { http::status::ok, req.version() };

    std::string url = req.target();

    std::vector<std::string_view> url_segs;
    size_t left = 0;
    while (left < url.length()) {
        size_t right = url.find('/', left);
        if (right == std::string::npos) {
            url_segs.emplace_back(url.c_str() + left, url.length() - left);
            break;
        }
        if (left == right) {
            left = right + 1;
            continue;
        }
        url_segs.emplace_back(url.c_str() + left, right - left);
        left = right + 1;
    }

    Context ctx(req, res);
    ctx.init();

    if (!handle_request(ctx, url_segs)) {
        ctx.bad_request(FMT::format("unknown path {}", std::string_view(ctx.req_.target())));
    }

    res.prepare_payload();

    return res;
}
