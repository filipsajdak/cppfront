

//=== Cpp2 type declarations ====================================================


#include "cpp2util.h"

#line 1 "mixed-as-for-variant-20-types.cpp2"


//=== Cpp2 type definitions and function declarations ===========================

#line 1 "mixed-as-for-variant-20-types.cpp2"
template<int I>
struct X { operator int() const { return I; } };

template <std::size_t... Is>
auto make_variant(std::index_sequence<Is...>){
    return std::variant<X<Is>...>{};
}

template <typename F, template<typename...> class C, typename... Ts>
constexpr auto for_each_type(C<Ts...>, F&& fun)
{
    [&]<std::size_t... Is>(std::index_sequence<Is...>){
        if constexpr ( requires { (fun(cpp2::type_it<Is, Ts>{}), ...); } ) {
            (fun(cpp2::type_it<Is, Ts>{}), ...);
        }
    }(std::index_sequence_for<Ts...>());
}

#line 19 "mixed-as-for-variant-20-types.cpp2"
[[nodiscard]] auto main() -> int;
#line 36 "mixed-as-for-variant-20-types.cpp2"

#include <iomanip>


//=== Cpp2 function definitions =================================================

#line 1 "mixed-as-for-variant-20-types.cpp2"

#line 19 "mixed-as-for-variant-20-types.cpp2"
[[nodiscard]] auto main() -> int{

    auto v {make_variant(std::make_index_sequence<30>())}; 

    for_each_type(v, [_0 = (&v)]<typename T>(T const& x) mutable -> void{
        *cpp2::assert_not_null(_0) = X<T::index>(); std::cout << "v as X<" << std::setw(2) << T::index << "> = " << std::setw(1) << cpp2::as_<int>(cpp2::as_<X<T::index>>(*cpp2::assert_not_null(_0))) << std::endl;
    });

    for_each_type(v, [_0 = (&v)]<typename T>(T const& x) mutable -> void{
        *cpp2::assert_not_null(_0) = X<T::index>(); std::cout << "as_const(v) as X<" << std::setw(2) << T::index << "> = " << std::setw(1) << cpp2::as_<int>(cpp2::as_<X<T::index>>(std::as_const(*cpp2::assert_not_null(_0)))) << std::endl;
    });

    for_each_type(v, [_0 = (&v)]<typename T>(T const& x) mutable -> void{
        *cpp2::assert_not_null(_0) = X<T::index>(); std::cout << "move(v) as X<" << std::setw(2) << T::index << "> = " << std::setw(1) << cpp2::as_<int>(cpp2::as_<X<T::index>>((std::move(*cpp2::assert_not_null(_0))))) << std::endl;
    });

}

