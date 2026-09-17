/*
 * Copyright (c) 2026-present Thomas Baricault
 *
 * SPDX-License-Identifier: MIT
 */


#pragma once


#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>


namespace tbaricault::templates
{

    /**
     * @brief Base case for an non container types
     * 
     * @tparam T Type to inspect
     */
    template<typename T>
    struct ContainerTraits
    {

        /**
         * @brief Whether the type is recognized as a container
         */
        static constexpr bool isContainer = false;

    };

    /**
     * @brief Type traits specialization for `std::map`
     * 
     * @tparam Key Key type
     * @tparam T Mapped value type
     * @tparam Compare Key comparison functor
     * @tparam Alloc Allocator type
     */
    template<typename Key, typename T, typename Compare, typename Alloc>
    struct ContainerTraits<std::map<Key, T, Compare, Alloc>>
    {

        /**
         * @brief Container key type
         */
        using KeyType = Key;

        /**
         * @brief Container value type
         */
        using ValueType = T;


        /**
         * @brief Whether the type is recognized as a container
         */
        static constexpr bool isContainer = true;

        /**
         * @brief Whether this container store key/value pairs
         */
        static constexpr bool isAssociative = true;

    };

    /**
     * @brief Type traits specialization for `std::set`
     * 
     * @tparam T Element type
     * @tparam Compare Comparison functor
     * @tparam Alloc Allocator type
     */
    template<typename T, typename Compare, typename Alloc>
    struct ContainerTraits<std::set<T, Compare, Alloc>>
    {

        /**
         * @brief Container value type
         */
        using ValueType = T;


        /**
         * @brief Whether the type is recognized as a container
         */
        static constexpr bool isContainer = true;

        /**
         * @brief Whether this container store key/value pairs
         */
        static constexpr bool isAssociative = false;

    };

    /**
     * @brief Type traits specialization for `std::unordered_map`
     * 
     * @tparam Key Key type
     * @tparam T Mapped value type
     * @tparam Hash Hash functor
     * @tparam Pred Equality predicate
     * @tparam Alloc Allocator type
     */
    template<typename Key, typename T, typename Hash, typename Pred, typename Alloc>
    struct ContainerTraits<std::unordered_map<Key, T, Hash, Pred, Alloc>>
    {

        /**
         * @brief Container key type
         */
        using KeyType = Key;

        /**
         * @brief Container value type
         */
        using ValueType = T;


        /**
         * @brief Whether the type is recognized as a container
         */
        static constexpr bool isContainer = true;

        /**
         * @brief Whether this container store key/value pairs
         */
        static constexpr bool isAssociative = true;

    };

    /**
     * @brief Type traits specialization for `std::unordered_set`
     * 
     * @tparam T Element type
     * @tparam Hash Hash functor
     * @tparam Pred Equality predicate
     * @tparam Alloc Allocator type
     */
    template<typename Key, typename Hash, typename Pred, typename Alloc>
    struct ContainerTraits<std::unordered_set<Key, Hash, Pred, Alloc>>
    {

        /**
         * @brief Container value type
         */
        using ValueType = Key;


        /**
         * @brief Whether the type is recognized as a container
         */
        static constexpr bool isContainer = true;

        /**
         * @brief Whether this container store key/value pairs
         */
        static constexpr bool isAssociative = false;

    };

    /**
     * @brief Type traits specialization for `std::vector`
     * 
     * @tparam T Element type
     * @tparam Alloc Allocator type
     */
    template<typename T, typename Alloc>
    struct ContainerTraits<std::vector<T, Alloc>>
    {

        /**
         * @brief Container value type
         */
        using ValueType = T;


        /**
         * @brief Whether the type is recognized as a container
         */
        static constexpr bool isContainer = true;

        /**
         * @brief Whether this container store key/value pairs
         */
        static constexpr bool isAssociative = false;

    };

}
