/* Variant classes.
 * @file
 * @date 2018-08-12
 * @author Anonymous
 */

#ifndef __VARIANT_HPP__
#define __VARIANT_HPP__

#include <map>
#include <memory>
#include <variant>
#include <vector>
#include <string>
#include <type_traits>

#include <boost/variant.hpp>

//{ number
using number = std::variant<int, float>;
//}

//{ array
using array = std::vector<number>;
//}
constexpr
//{ recursive_array
struct recursive_array : public std::vector<std::variant<number, std::shared_ptr<recursive_array>>>
{
    using std::vector<std::variant<number, std::shared_ptr<recursive_array>>>::vector;
};
//}

//{ recursive_array2
struct recursive_array2 : public std::vector<std::variant<number, boost::recursive_wrapper<recursive_array2>>>
{
    using std::vector<std::variant<number, boost::recursive_wrapper<recursive_array2>>>::vector;
};
//}

//{ variant_decorator
template<class... Types>
struct variant_decorator : std::variant<Types...>
{
    using std::variant<Types...>::variant;

    template<class T>
    constexpr const auto& as() const
    {
        if constexpr (std::disjunction_v<std::is_same<boost::recursive_wrapper<T>, Types>...>)
        {
            return std::get<boost::recursive_wrapper<T>>(*this).get();
        }
        else
        {
            return std::get<T>(*this);
        }
    }

    template<class T>
    constexpr auto& as()
    {
        using return_type = std::remove_const_t<std::remove_reference_t<decltype(std::declval<const variant_decorator&>().template as<T>())>>;
        return const_cast<return_type&>(static_cast<const variant_decorator&>(*this).as<T>());
    }
};
//}

//{ recursive_map
struct recursive_map : public std::map<std::string, variant_decorator<int, float, std::string, bool, boost::recursive_wrapper<recursive_map>>>
{
    using std::map<std::string, variant_decorator<int, float, std::string, bool, boost::recursive_wrapper<recursive_map>>>::map;
};
//}

#endif // __VARIANT_HPP__
