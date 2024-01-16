
#pragma once

#include <chrono>
#include <condition_variable>
#include <map>
#include <mutex>
#include <string>
#include <tuple>

#include "Helper/Uuid.hpp"

template <typename T>
struct FixVoid
{
    using type = T;
};

template <>
struct FixVoid<void>
{
    using type = int;
};

template <typename Ret, typename... Args>
struct CallbackManager
{
    struct CallbackContext : public std::enable_shared_from_this<CallbackContext>
    {
        using args_type = typename std::tuple<Args...>;
        using real_return_type = Ret;
        using return_type = typename FixVoid<Ret>::type;

        struct InstanceContext
        {
            std::condition_variable cond_;
            std::mutex mtx_;
            args_type args_;
            bool returned_ = false;
            return_type result_;

            InstanceContext(const Args&... args) : args_(args...) {}
        };

        std::string id_;
        std::map<std::string, std::shared_ptr<InstanceContext>> pendings_;
        std::mutex mtx_;

        std::mutex cond_mtx_;
        std::condition_variable cond_;

        std::string push(const Args&... args)
        {
            auto cid = make_uuid();

            std::unique_lock<std::mutex> lock(mtx_);
            pendings_[cid] = std::make_shared<InstanceContext>(args...);

            std::lock_guard<std::mutex> clock(cond_mtx_);
            cond_.notify_all();

            return cid;
        }

        void wait(const std::string& cid, return_type& result)
        {
            std::shared_ptr<InstanceContext> ctx;
            {
                std::unique_lock<std::mutex> lock(mtx_);
                ctx = pendings_[cid];
            }
            {
                std::unique_lock<std::mutex> lock(ctx->mtx_);
                ctx->cond_.wait(lock, [ctx]() { return ctx->returned_; });
            }
        }

        void take(std::vector<std::string>& cids)
        {
            cids.clear();

            std::unique_lock<std::mutex> lock(mtx_);
            for (const auto& [id, _] : pendings_) {
                cids.push_back(id);
            }
        }

        bool take_wait(std::vector<std::string>& cids)
        {
            auto timeout = std::chrono::system_clock::now() + std::chrono::seconds(5);
            std::unique_lock<std::mutex> clock(cond_mtx_);
            if (cond_.wait_until(clock, timeout, [this]() {
                    std::unique_lock<std::mutex> lock(mtx_);

                    return pendings_.size() > 0;
                })) {

                take(cids);
                return true;
            }
            else {
                cids.clear();
                return false;
            }
        }

        bool resp(const std::string& cid, const return_type& result)
        {
            std::shared_ptr<InstanceContext> ctx;
            {
                std::unique_lock<std::mutex> lock(mtx_);
                if (!pendings_.contains(cid)) {
                    return false;
                }
                ctx = pendings_[cid];
                pendings_.erase(cid);
            }
            {
                std::unique_lock<std::mutex> lock(ctx->mtx_);
                ctx->returned_ = true;
                ctx->result_ = result;
            }
            ctx->cond_.notify_one();
            return true;
        }

        bool get_args(const std::string& cid, args_type& args)
        {
            std::unique_lock<std::mutex> lock(mtx_);
            if (!pendings_.contains(cid)) {
                return false;
            }
            args = pendings_[cid]->args_;
            return true;
        }
    };

    std::map<std::string, std::shared_ptr<CallbackContext>> contexts_;
    std::mutex mtx_;

    std::shared_ptr<CallbackContext> alloc(std::string& id)
    {
        id = make_uuid();
        auto ctx = std::make_shared<CallbackContext>();
        ctx->id_ = id;

        std::unique_lock<std::mutex> lock(mtx_);
        contexts_[id] = ctx;
        return ctx;
    }

    std::shared_ptr<CallbackContext> find(const std::string& id)
    {
        std::unique_lock<std::mutex> lock(mtx_);
        if (contexts_.contains(id)) {
            return contexts_[id];
        }
        return nullptr;
    }

    bool free(const std::string& id)
    {
        std::unique_lock<std::mutex> lock(mtx_);
        if (contexts_.contains(id)) {
            contexts_.erase(id);
            return true;
        }
        return false;
    }

    std::vector<std::string> dump()
    {
        std::unique_lock<std::mutex> lock(mtx_);
        std::vector<std::string> ids;
        for (const auto& [key, val] : contexts_) {
            ids.push_back(key);
        }
        return ids;
    }
};
