#pragma once

#include <chrono>
#include <condition_variable>
#include <map>
#include <mutex>
#include <string>

#include "manager/data_manager.hpp"
#include "manager/manager.hpp"
#include "utils/uuid.hpp"

namespace lhg
{

namespace callback
{

    struct context_info : public std::enable_shared_from_this<context_info>
    {
        struct call_context
        {
            std::mutex mtx;
            std::condition_variable cond;

            const json::object& req;
            json::object& res;
            bool ret = false;

            call_context(const json::object& req, json::object& res) : req(req), res(res) {}
        };

        ManagerProvider* provider = nullptr;
        std::function<void(json::object& res, const json::object& req)> process;

        std::mutex mtx;
        std::map<std::string, std::shared_ptr<call_context>> pending;

        std::mutex cond_mtx;
        std::condition_variable cond;

        context_info()
        {
            process = [this](auto& res, const auto& req) {
                auto self_holder = this->shared_from_this();

                auto cid = make_uuid();
                auto call_ctx = std::make_shared<call_context>(req, res);

                {
                    std::unique_lock<std::mutex> lock(mtx);

                    pending[cid] = call_ctx;

                    std::lock_guard<std::mutex> cond_lock(cond_mtx);
                    cond.notify_all();
                }

                {
                    std::unique_lock<std::mutex> lock(call_ctx->mtx);
                    call_ctx->cond.wait(lock, [call_ctx]() { return call_ctx->ret; });
                }
            };
        }

        void take(std::vector<std::string>& cids)
        {
            cids.clear();

            std::unique_lock<std::mutex> lock(mtx);
            for (const auto& [id, _] : pending) {
                cids.push_back(id);
            }
        }

        bool take_wait(std::vector<std::string>& cids, unsigned sec = 5)
        {
            std::unique_lock<std::mutex> cond_lock(cond_mtx);
            auto timeout = std::chrono::system_clock::now() + std::chrono::seconds(sec);

            if (cond.wait_until(cond_lock, timeout, [this]() {
                    std::unique_lock<std::mutex> lock(mtx);
                    return pending.size() > 0;
                })) {
                take(cids);
                return cids.size() > 0;
            }
            else {
                cids.clear();
                return false;
            }
        }

        bool get_req(const std::string& cid, json::object& req)
        {
            std::unique_lock<std::mutex> lock(mtx);
            if (pending.contains(cid)) {
                req = pending[cid]->req;
                return true;
            }
            else {
                return false;
            }
        }

        bool set_res(const std::string& cid, const json::object& res)
        {
            std::shared_ptr<call_context> call_ctx;
            {
                std::unique_lock<std::mutex> lock(mtx);
                if (pending.contains(cid)) {
                    call_ctx = pending[cid];
                    pending.erase(cid);
                }
                else {
                    return false;
                }
            }
            {
                std::unique_lock<std::mutex> lock(call_ctx->mtx);
                call_ctx->ret = true;
                call_ctx->res = res;
            }
            call_ctx->cond.notify_one();
            return true;
        }
    };

} // namespace callback

template <typename callback_tag>
class CallbackManager
{
public:
    std::shared_ptr<callback::context_info> alloc(std::string& id, ManagerProvider* provider)
    {
        id = make_uuid();
        auto ctx = std::make_shared<callback::context_info>();
        ctx->provider = provider;

        std::unique_lock<std::mutex> lock(mtx);
        contexts[id] = ctx;
        return ctx;
    }

    bool free(const std::string& id, ManagerProvider* provider)
    {
        std::unique_lock<std::mutex> lock(mtx);
        if (contexts.contains(id)) {
            auto ctx = contexts[id];
            contexts.erase(id);
            provider->get<DataManager, void>()->free(id);
            return true;
        }
        else {
            return false;
        }
    }

    std::shared_ptr<callback::context_info> query(const std::string& id)
    {
        std::unique_lock<std::mutex> lock(mtx);
        if (contexts.contains(id)) {
            return contexts[id];
        }
        else {
            return nullptr;
        }
    }

    std::vector<std::string> dump()
    {
        std::unique_lock<std::mutex> lock(mtx);
        std::vector<std::string> ids;
        for (const auto& [key, val] : contexts) {
            ids.push_back(key);
        }
        return ids;
    }

private:
    std::mutex mtx;
    std::map<std::string, std::shared_ptr<callback::context_info>> contexts;
};

} // namespace lhg