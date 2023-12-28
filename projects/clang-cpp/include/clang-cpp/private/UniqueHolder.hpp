#pragma once

namespace clangpp::__private
{

template <typename Type, void (*Free)(Type)>
struct CXXUniqueHolder
{
    Type raw_ = nullptr;

    void set(Type other)
    {
        if (raw_) {
            Free(raw_);
        }
        raw_ = other;
    }

    CXXUniqueHolder() = default;
    CXXUniqueHolder(const CXXUniqueHolder&) = delete;
    CXXUniqueHolder(CXXUniqueHolder&& other)
    {
        raw_ = other.raw_;
        other.raw_ = nullptr;
    }
    CXXUniqueHolder& operator=(const CXXUniqueHolder&) = delete;
    CXXUniqueHolder& operator=(CXXUniqueHolder&& other)
    {
        if (this == &other) {
            return *this;
        }
        if (raw_) {
            Free(raw_);
        }
        raw_ = other.raw_;
        other.raw_ = nullptr;
        return *this;
    }
    virtual ~CXXUniqueHolder()
    {
        if (raw_) {
            Free(raw_);
        }
    }
};

}
