#pragma once

#include "Handle/Context.hpp"
#include "Helper/UrlSegments.hpp"

bool handle_request(Context& ctx, UrlSegments segs);

http::message_generator handle_request(http::request<http::string_body>&& req);
