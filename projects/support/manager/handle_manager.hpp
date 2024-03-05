#pragma once

#include <map>
#include <mutex>
#include <string>

#include "utils/uuid.hpp"

namespace lhg
{

template <typename handle_t>
struct HandleManager
{
    struct ScopedHandle
    {
        HandleManager<handle_t>& manager;
        handle_t handle;

        ScopedHandle(HandleManager<handle_t>& manager, handle_t handle, std::string& id)
            : manager(manager), handle(handle)
        {
            id = manager.add(handle);
        }
        ~ScopedHandle() { manager.del(handle); }
        ScopedHandle(const ScopedHandle&) = delete;
        ScopedHandle& operator=(const ScopedHandle&) = delete;
    };

    std::map<std::string, handle_t> handles_;
    std::map<handle_t, std::string> index_;
    std::mutex mtx_;

    std::string add(handle_t handle)
    {
        auto id = make_uuid();

        std::unique_lock<std::mutex> lock(mtx_);
        if (index_.contains(handle)) {
            return {};
        }
        index_[handle] = id;
        handles_[id] = handle;
        return id;
    }

    bool del(handle_t handle)
    {
        std::unique_lock<std::mutex> lock(mtx_);
        if (!index_.contains(handle)) {
            return false;
        }

        auto id = index_[handle];
        index_.erase(handle);
        handles_.erase(id);
        return true;
    }

    bool del(const std::string& id, handle_t& handle)
    {
        std::unique_lock<std::mutex> lock(mtx_);
        if (!handles_.contains(id)) {
            return false;
        }

        handle = handles_[id];
        index_.erase(handle);
        handles_.erase(id);
        return true;
    }

    handle_t get(const std::string& id)
    {
        std::unique_lock<std::mutex> lock(mtx_);

        if (!handles_.contains(id)) {
            return 0;
        }
        return handles_[id];
    }

    std::string find(handle_t handle)
    {
        std::unique_lock<std::mutex> lock(mtx_);

        if (!index_.contains(handle)) {
            return {};
        }
        return index_[handle];
    }

    std::map<std::string, handle_t> dump()
    {
        std::unique_lock<std::mutex> lock(mtx_);

        return handles_;
    }
};

} // namespace lhg
