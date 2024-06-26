////////////////////////
//
//  Created: Wed May 01 2024
//  File: types.hpp
//
////////////////////////

#pragma once

#include <memory>
#include <vector>
#include <any>
#include <optional>
#include <unordered_map>
#include <map>
#include <typeindex>

namespace mce
{
    class World;

    using Entity = std::size_t;
    using Entities = std::vector<Entity>;
    using ComponentContainer = std::unordered_map<std::type_index, std::any>;

    template<typename T, typename R, typename ... ARGS>
    using Method = R (T::*)(ARGS &&...);

    template<typename KEY, typename T, typename R, typename ... ARGS>
    using RequestContainer = std::vector<std::pair<KEY, Method<T, R, ARGS...>>>;

    template<typename T, typename R, typename ... ARGS>
    using MethodContainer = std::vector<Method<T, R, ARGS...>>;

    template<typename T, auto M, typename R, typename ... ARGS>
    concept HasMethod = requires(T &t, ARGS &&... args)
    {
        { (t.*M)(std::forward<ARGS>(args)...) } -> std::same_as<R>;
    };

    template<typename T, auto M, typename ... ARGS>
    concept HasCustomMethod = HasMethod<T, M, void, ARGS...>;

    template<typename T>
    concept HasInit = HasCustomMethod<T, &T::init, World &, const Entity &>;
}
