/*
 * Copyright (c) 2026-present Thomas Baricault
 *
 * SPDX-License-Identifier: MIT
 */


#pragma once


#include "FixedString.hpp"


namespace tbaricault::templates
{

    template<std::size_t N>
    constexpr FixedString<N>::FixedString(const char (&s)[N])
    {
        for (std::size_t i = 0; i < N; ++i)
            data[i] = s[i];
        return;
    }

    template <std::size_t N>
    template <std::size_t M>
    constexpr bool FixedString<N>::operator==(const FixedString<M>& other) const
    {
        if constexpr (N != M)
            return (false);
        else
        {
            for (std::size_t i = 0; i < N; ++i)
                if (data[i] != other.data[i])
                    return (false);
            return (true);
        }
    }

    template<std::size_t N>
    constexpr FixedString<N>::operator std::string_view() const
    {
        return {data, N - 1};
    }

}
