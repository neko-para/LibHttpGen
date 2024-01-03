#pragma once

#include <map>
#include <mutex>
#include <string>

#include "Helper/Uuid.hpp"

template <typename Handle>
struct HandleManager
{
    std::map<std::string, Handle> handles_;
    std::map<Handle, std::string> index_;
    std::mutex mtx_;

    std::string add(Handle handle)
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

    bool del(Handle handle)
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

    bool del(const std::string& id, Handle& handle)
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

    Handle get(const std::string& id)
    {
        std::unique_lock<std::mutex> lock(mtx_);

        if (!handles_.contains(id)) {
            return 0;
        }
        return handles_[id];
    }

    std::string find(Handle handle)
    {
        std::unique_lock<std::mutex> lock(mtx_);

        if (!index_.contains(handle)) {
            return {};
        }
        return index_[handle];
    }
};
