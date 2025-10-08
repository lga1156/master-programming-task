#ifndef IOMANIP_HPP
#define IOMANIP_HPP

#include <iostream>
#include <string>
#include <string_view>

namespace detail
{
    struct http_proxy
    {
        std::ostream& os;
    };

    inline std::ostream& operator<<(http_proxy p, std::string_view value)
    {
        return p.os << "http://" << value;
    }

    struct http_manip_t {};
}

inline detail::http_proxy operator<<(std::ostream& os, detail::http_manip_t)
{
    return {os};
}

inline constexpr detail::http_manip_t http;

namespace detail
{
    struct squares_proxy
    {
        std::ostream& os;
    };

    template <typename T>
    std::ostream& operator<<(squares_proxy p, const T& value)
    {
        return p.os << "[" << value << "]";
    }

    struct squares_manip_t {};
}

inline detail::squares_proxy operator<<(std::ostream& os, detail::squares_manip_t)
{
    return {os};
}

inline constexpr detail::squares_manip_t squares;

namespace detail
{
    template <typename T>
    struct add_second_arg_proxy
    {
        std::ostream& os;
        T first_value;
    };
    
    template <typename T1, typename T2>
    std::ostream& operator<<(add_second_arg_proxy<T1> p, const T2& second_value)
    {
        return p.os << (p.first_value + second_value);
    }

    struct add_first_arg_proxy
    {
        std::ostream& os;
    };

    template <typename T>
    add_second_arg_proxy<T> operator<<(add_first_arg_proxy p, const T& first_value)
    {
        return {p.os, first_value};
    }

    struct add_manip_t {};
}

inline detail::add_first_arg_proxy operator<<(std::ostream& os, detail::add_manip_t)
{
    return {os};
}

inline constexpr detail::add_manip_t add;

#endif