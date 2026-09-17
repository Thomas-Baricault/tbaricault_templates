/*
 * Copyright (c) 2026-present Thomas Baricault
 *
 * SPDX-License-Identifier: MIT
 */


#pragma once


namespace tbaricault::templates
{

    /**
     * @brief Checks whether a type is contained in a list of types
     * 
     * @tparam T Type to search for
     * @tparam List List of types to search within
     */
    template<typename T, typename... List>
    struct contains;

    /**
     * @brief Base case for an empty type list
     * 
     * When no more types are available to check, the queried type cannot be found.
     * 
     * @tparam T Type being searched for
     */
    template<typename T>
    struct contains<T>
    {

        /**
         * @brief Indicates whether the type was found
         * 
         * Always evaluates to `false` for an empty type list.
         */
        static constexpr bool value = false;

    };

    /**
     * @brief Recursive case for checking a type list
     * 
     * Compares `T` with the first type in the list. If they are not the same, the search continues recursively through the remaining types.
     * 
     * @tparam T Type to search for
     * @tparam First Current type being compared
     * @tparam Rest Remaining types to check
     */
    template<typename T, typename First, typename... Rest>
    struct contains<T, First, Rest...>
    {

        /**
         * @brief Indicates whether the type exists in the type list
         * 
         * Evaluates to `true` if `T` matches `First` or if it is found in the remaining types.
         */
        static constexpr bool value = std::is_same_v<T, First> || contains<T, Rest...>::value;

    };

}
