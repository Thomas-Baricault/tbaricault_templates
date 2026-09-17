/*
 * Copyright (c) 2026-present Thomas Baricault
 *
 * SPDX-License-Identifier: MIT
 */


#pragma once


#include <cstddef>
#include <string_view>


namespace tbaricault::templates
{

    /**
     * @brief Compile-time fixed-size string wrapper
     * 
     * This type stores a string literal in a fixed-size character array and can be used as a non-type template parameter (NTTP) in C++23.
     * 
     * @tparam N Size of the character array, including the null terminator
     */
    template<std::size_t N>
    struct FixedString
    {

        /**
         * @brief Underlying character storage
         */
        char data[N];


        /**
         * @brief Constructs a fixed string from a string literal
         * 
         * @param s String literal to copy
         */
        constexpr FixedString(const char (&s)[N]);

        /**
         * @brief Compares two fixed strings for equality
         * 
         * @param other String to compare with
         * 
         * @return `true` if both strings contain identical characters, `false` otherwise
         */
        template <std::size_t M>
        constexpr bool operator==(const FixedString<M>& other) const;

        /**
         * @brief Converts the fixed string to a `std::string_view`
         * 
         * @return `std::string_view` referencing the stored characters
         */
        constexpr operator std::string_view() const;

    };

}


#include "FixedString.tpp"
