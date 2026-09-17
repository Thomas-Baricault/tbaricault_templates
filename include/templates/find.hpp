/*
 * Copyright (c) 2026-present Thomas Baricault
 *
 * SPDX-License-Identifier: MIT
 */


#pragma once


#include <cstddef>
#include <limits>

#include "FixedString.hpp"


namespace tbaricault::templates
{

    /**
     * @brief Finds a type by its compile-time name in a list of types
     * 
     * Searches through a list of types and returns the first type whose static `name` member matches the specified `Name`.
     * 
     * @tparam Name Compile-time name used to identify the type
     * @tparam List List of types to search within
     */
    template<FixedString Name, typename... List>
    struct find;

    /**
     * @brief Base case for an empty type list
     * 
     * When no type matches the requested name, `type` is set to `void` and `index` is set to `std::size_t` max.
     * 
     * @tparam Name Compile-time name used to identify the type
     */
    template<FixedString Name>
    struct find<Name>
    {

        /**
         * @brief Type found by the search
         * 
         * Always evaluates to `void` for an empty type list.
         */
        using type = void;


        /**
         * @brief Index of the found type
         * 
         * Always evaluates to `std::size_t` max for an empty type list.
         */
        static constexpr std::size_t index = std::numeric_limits<std::size_t>::max();

    };

    /**
     * @brief Recursive case for searching through a type list
     * 
     * Checks whether the first type has a `name` member matching `Name`. If they are not the same, the search continues recursively through the remaining types.
     * 
     * @tparam Name Compile-time name being searched for
     * @tparam First Current type being compared
     * @tparam Rest Remaining types to search through
     */
    template<FixedString Name, typename First, typename... Rest>
    struct find<Name, First, Rest...>
    {

        private:

            /**
             * @brief Result of the next check
             */
            using _next = find<Name, Rest...>;


        public:

            /**
             * @brief Type found by the search
             */
            using type = std::conditional_t<
                First::name == Name,
                First,
                typename find::_next::type
            >;


            /**
             * @brief Index of the found type
             */
            static constexpr std::size_t index = (
                First::name == Name
                    ? 0
                    : (
                        find::_next::index == std::numeric_limits<std::size_t>::max()
                            ? std::numeric_limits<std::size_t>::max()
                            : 1 + find::_next::index
                    )
            );

    };

}
