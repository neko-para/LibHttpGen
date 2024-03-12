#pragma once

#include <map>
#include <memory>
#include <string>
#include <unordered_set>
#include <vector>

namespace lhg
{

class DataManager
{
private:
    struct base_holder
    {
        virtual ~base_holder() {}
    };

    template <typename T>
    struct holder : public base_holder
    {
        std::vector<std::string> dep;
        T data;

        template <typename... Ids>
        holder(Ids&&... ids) : dep(std::forward<Ids>(ids)...)
        {}
        holder(const holder&) = delete;
        holder& operator=(const holder&) = delete;

        T* get() { return &data; }
    };
    std::map<std::string, std::unordered_set<std::shared_ptr<base_holder>>> data;

public:
    template <typename T, typename... Ids>
    T* alloc(Ids&&... ids)
    {
        auto h = std::make_shared<holder<T>>(std::forward<Ids>(ids)...);
        for (const auto& id : h->dep) {
            data[id].insert(h);
        }
        return h->get();
    }

    void free(const std::string& id) { data.erase(id); }
};

}