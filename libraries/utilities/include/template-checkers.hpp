#pragma once

#include <type_traits>

template<typename T, typename = void>
struct is_functor : std::false_type {};

template<typename T>
struct is_functor<T, std::void_t<decltype(std::declval<T>()())>> : std::true_type {};
