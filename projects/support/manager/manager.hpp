#pragma once

#include <memory>
#include <typeindex>
#include <unordered_map>

namespace lhg
{

class ManagerProvider
{
private:
    struct holder_base
    {
        virtual ~holder_base() {}
    };
    template <typename type>
    struct holder : public holder_base
    {
        type* ptr;
        holder(type* p) : ptr(p) {}
        holder(const holder&) = delete;
        holder& operator=(const holder&) = delete;
        virtual ~holder() override { delete ptr; }
    };

public:
    template <typename Manager, typename Tag>
    Manager* get()
    {
        std::type_index tag_id(typeid(Tag));
        std::type_index manager_id(typeid(Manager));

        auto& sub_manager = managers[manager_id];
        auto it = sub_manager.find(tag_id);
        if (it == sub_manager.end()) {
            auto ptr = std::make_unique<holder<Manager>>(new Manager());
            auto raw_ptr = ptr.get()->ptr;
            sub_manager[tag_id] = std::move(ptr);
            return raw_ptr;
        }
        else {
            return dynamic_cast<holder<Manager>*>(it->second.get())->ptr;
        }
    }

private:
    std::unordered_map<std::type_index, std::unordered_map<std::type_index, std::unique_ptr<holder_base>>> managers;
};

}
