// Copyright (c) 2018-2022 iFarbod and other contributors. All Rights Reserved.
//
// SPDX-License-Identifier: MIT

#pragma once

#include <type_traits>

namespace zsl
{

// Example usage:
// template <>
// struct zsl::EnumFlags<zg::FooEnum>
// {
//     static constexpr bool is_flags = true;
// };

template <typename T>
struct EnumFlags
{
};

template <typename T, typename = void>
struct HasIsFlags : std::false_type
{
};

template <typename T>
struct HasIsFlags<T, std::void_t<decltype(EnumFlags<T>::is_flags)>>
    : std::bool_constant<std::is_same_v<bool, std::decay_t<decltype(EnumFlags<T>::is_flags)>>>
{
};

template <typename T>
constexpr auto IsFlagsEnum() -> bool
{
    if constexpr (HasIsFlags<T>::value)
    {
        return EnumFlags<T>::is_flags;
    }
    return false;
}

template <typename T>
inline constexpr bool IsFlagsV = IsFlagsEnum<T>();

template <typename T>
constexpr auto EnumIsSet(T e) -> std::enable_if_t<std::is_enum_v<T> && zsl::IsFlagsV<T>, bool>
{
    return static_cast<bool>(e);
}

}  // namespace zsl

template <typename T, std::enable_if_t<std::is_enum_v<T> && zsl::IsFlagsV<T>, int> = 0>
constexpr auto operator&(T lhs, T rhs) -> T
{
    using UnderlyingType = std::underlying_type_t<T>;
    return static_cast<T>(static_cast<UnderlyingType>(lhs) & static_cast<UnderlyingType>(rhs));
}

template <typename T, std::enable_if_t<std::is_enum_v<T> && zsl::IsFlagsV<T>, int> = 0>
constexpr auto operator|(T lhs, T rhs) -> T
{
    using UnderlyingType = std::underlying_type_t<T>;
    return static_cast<T>(static_cast<UnderlyingType>(lhs) | static_cast<UnderlyingType>(rhs));
}

template <typename T, std::enable_if_t<std::is_enum_v<T> && zsl::IsFlagsV<T>, int> = 0>
constexpr auto operator^(T lhs, T rhs) -> T
{
    using UnderlyingType = std::underlying_type_t<T>;
    return static_cast<T>(static_cast<UnderlyingType>(lhs) | static_cast<UnderlyingType>(rhs));
}

template <typename T, std::enable_if_t<std::is_enum_v<T> && zsl::IsFlagsV<T>, int> = 0>
constexpr auto operator~(T lhs) -> T
{
    using UnderlyingType = std::underlying_type_t<T>;
    return static_cast<T>(~static_cast<UnderlyingType>(lhs));
}

template <typename T, std::enable_if_t<std::is_enum_v<T> && zsl::IsFlagsV<T>, int> = 0>
constexpr auto operator&=(T lhs, T rhs) -> T
{
    using UnderlyingType = std::underlying_type_t<T>;
    return lhs = static_cast<T>(static_cast<UnderlyingType>(lhs) & static_cast<UnderlyingType>(rhs));
}

template <typename T, std::enable_if_t<std::is_enum_v<T> && zsl::IsFlagsV<T>, int> = 0>
constexpr auto operator|=(T lhs, T rhs) -> T
{
    using UnderlyingType = std::underlying_type_t<T>;
    return lhs = static_cast<T>(static_cast<UnderlyingType>(lhs) | static_cast<UnderlyingType>(rhs));
}

template <typename T, std::enable_if_t<std::is_enum_v<T> && zsl::IsFlagsV<T>, int> = 0>
constexpr auto operator^=(T lhs, T rhs) -> T
{
    using UnderlyingType = std::underlying_type_t<T>;
    return lhs = static_cast<T>(static_cast<UnderlyingType>(lhs) ^ static_cast<UnderlyingType>(rhs));
}
