#pragma once

#include <type_traits>
#include "graph.hpp"

template <typename T, typename = void>
struct is_size_t_constructible: std::false_type {};

template <typename T>
struct is_size_t_constructible<T, std::void_t<decltype(T(std::declval<std::size_t>()))>>: std::true_type {};

template <typename T, typename = void>
struct can_choose_color: std::false_type {};

template <typename T>
struct can_choose_color<T, std::void_t<decltype(std::declval<T>()(std::declval<const clrAlgo::UndirectedGraph&>(), std::declval<size_t>()))>> {
    using return_type = decltype(std::declval<T>()(std::declval<const clrAlgo::UndirectedGraph&>(), std::declval<size_t>()));
    static constexpr bool value = std::is_same<return_type, unsigned>::value;
};
