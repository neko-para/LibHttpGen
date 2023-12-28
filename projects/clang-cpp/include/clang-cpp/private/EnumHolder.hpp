#pragma once

#include <concepts>

namespace clangpp::__private
{

template <typename Type>
struct CXXEnumHolder
{
    Type raw_;

    CXXEnumHolder(Type raw) : raw_(raw) {}
    explicit operator Type() const { return raw_; }
};

template <typename Type, typename Target>
concept __IsEnumHolder = std::derived_from<Target, CXXEnumHolder<Type>>;

template <typename Type, typename Target>
concept __IsEnumOrEnumHolder = __IsEnumHolder<Type, Target> || std::same_as<Target, Type>;

template <typename Type, typename Left>
requires __IsEnumHolder<Type, Left>
inline bool operator==(const Left& a, Type b)
{
    return a.raw_ == b;
}

template <typename Type, typename Right>
requires __IsEnumHolder<Type, Right>
inline bool operator==(Type a, const Right& b)
{
    return a == b.raw_;
}

template <typename Type, typename Both>
requires __IsEnumHolder<Type, Both>
inline bool operator==(const Both& a, const Both& b)
{
    return a.raw_ == b.raw_;
}

template <typename Type, typename Left, typename Right>
requires __IsEnumHolder<Type, Left> || __IsEnumHolder<Type, Right>
inline bool operator!=(const Left& a, const Right& b)
{
    return !(a == b);
}

}
