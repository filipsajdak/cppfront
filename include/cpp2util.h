
//  Copyright (c) Herb Sutter
//  SPDX-License-Identifier: CC-BY-NC-ND-4.0

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.


//===========================================================================
//  Cpp2 utilities:
//      Language support implementations
//      #include'd by generated Cpp1 code
//===========================================================================

#ifndef CPP2_UTIL_H
#define CPP2_UTIL_H

//  If this implementation doesn't support source_location yet, disable it
#include <version>
#if !defined(_MSC_VER) && !defined(__cpp_lib_source_location)
    #undef CPP2_USE_SOURCE_LOCATION
#endif

//  If the user requested making the entire C++ standard library available
//  via module import (incl. via -pure-cpp2) or header include, do that
#if defined(CPP2_IMPORT_STD) || defined(CPP2_INCLUDE_STD)

    //  If C++23 'import std;' was requested but isn't available, fall back
    //  to the 'include std' path
    #if defined(CPP2_IMPORT_STD) && defined(__cpp_lib_modules)
        import std.compat;
    //  If 'include std' was requested, include all standard headers.
    //  This list tracks the current draft standard, so as of this
    //  writing includes draft C++26 headers like <debugging>.
    //  Use a feature test #ifdef for each header that isn't supported
    //  by all of { VS 2022, g++-10, clang++-12 }
    #else
        #ifdef _MSC_VER
            #include "intrin.h"
        #endif
        #include <algorithm>
        #include <any>
        #include <array>
        #include <atomic>
        #ifdef __cpp_lib_barrier
            #include <barrier>
        #endif
        #include <bit>
        #include <bitset>
        #include <cassert>
        #include <cctype>
        #include <cerrno>
        #include <cfenv>
        #include <cfloat>
        #include <charconv>
        #include <chrono>
        #include <cinttypes>
        #include <climits>
        #include <clocale>
        #include <cmath>
        #include <codecvt>
        #include <compare>
        #include <complex>
        #include <concepts>
        #include <condition_variable>
        #ifdef __cpp_lib_coroutine
            #include <coroutine>
        #endif
        #include <csetjmp>
        #include <csignal>
        #include <cstdarg>
        #include <cstddef>
        #include <cstdint>
        #include <cstdio>
        #include <cstdlib>
        #include <cstring>
        #include <ctime>
        #if __has_include(<cuchar>)
            #include <cuchar>
        #endif
        #include <cwchar>
        #include <cwctype>
        #ifdef __cpp_lib_debugging
            #include <debugging>
        #endif
        #include <deque>
        #ifndef CPP2_NO_EXCEPTIONS
            #include <exception>
        #endif
        // libstdc++ currently has a dependency on linking TBB if <execution> is
        // included, and TBB seems to be not automatically installed and linkable
        // on some GCC installations, so let's not pull in that little-used header
        // in our -pure-cpp2 "import std;" simulation mode... if you need this,
        // use mixed mode (not -pure-cpp2) and #include all the headers you need
        // including this one
        //
        // #include <execution>
        #ifdef __cpp_lib_expected
            #include <expected>
        #endif
        #include <filesystem>
        #if defined(__cpp_lib_format) || (defined(_MSC_VER) && _MSC_VER >= 1929)
            #include <format>
        #endif
        #ifdef __cpp_lib_flat_map
            #include <flat_map>
        #endif
        #ifdef __cpp_lib_flat_set
            #include <flat_set>
        #endif
        #include <forward_list>
        #include <fstream>
        #include <functional>
        #include <future>
        #ifdef __cpp_lib_generator
            #include <generator>
        #endif
        #ifdef __cpp_lib_hazard_pointer
            #include <hazard_pointer>
        #endif
        #include <initializer_list>
        #include <iomanip>
        #include <ios>
        #include <iosfwd>
        #include <iostream>
        #include <iso646.h>
        #include <istream>
        #include <iterator>
        #ifdef __cpp_lib_latch
            #include <latch>
        #endif
        #include <limits>
        #ifdef __cpp_lib_linalg
            #include <linalg>
        #endif
        #include <list>
        #include <locale>
        #include <map>
        #ifdef __cpp_lib_mdspan
            #include <mdspan>
        #endif
        #include <memory>
        #ifdef __cpp_lib_memory_resource
            #include <memory_resource>
        #endif
        #include <mutex>
        #include <new>
        #include <numbers>
        #include <numeric>
        #include <optional>
        #include <ostream>
        #ifdef __cpp_lib_print
            #include <print>
        #endif
        #include <queue>
        #include <random>
        #include <ranges>
        #include <ratio>
        #ifdef __cpp_lib_rcu
            #include <rcu>
        #endif
        #include <regex>
        #include <scoped_allocator>
        #ifdef __cpp_lib_semaphore
            #include <semaphore>
        #endif
        #include <set>
        #include <shared_mutex>
        #ifdef __cpp_lib_source_location
            #include <source_location>
        #endif
        #include <span>
        #ifdef __cpp_lib_spanstream
            #include <spanstream>
        #endif
        #include <sstream>
        #include <stack>
        #ifdef __cpp_lib_stacktrace
            #include <stacktrace>
        #endif
        #ifdef __cpp_lib_stdatomic_h
            #include <stdatomic.h>
        #endif
        #include <stdexcept>
        #if __has_include(<stdfloat>)
            #if !defined(_MSC_VER) || _HAS_CXX23
                #include <stdfloat>
            #endif
        #endif
        #ifdef __cpp_lib_jthread
            #include <stop_token>
        #endif
        #include <streambuf>
        #include <string>
        #include <string_view>
        #ifdef __cpp_lib_syncstream
            #include <syncstream>
        #endif
        #include <system_error>
        #ifdef __cpp_lib_text_encoding
            #include <text_encoding>
        #endif
        #include <thread>
        #include <tuple>
        #include <type_traits>
        #include <typeindex>
        #ifndef CPP2_NO_RTTI
            #include <typeinfo>
        #endif
        #include <unordered_map>
        #include <unordered_set>
        #include <utility>
        #include <valarray>
        #include <variant>
        #include <vector>
    #endif

//  Otherwise, just #include the facilities used in this header
#else
    #ifdef _MSC_VER
        #include "intrin.h"
    #endif
    #include <algorithm>
    #include <any>
    #include <compare>
    #include <concepts>
    #include <cstddef>
    #include <cstdint>
    #include <cstdio>
    #ifndef CPP2_NO_EXCEPTIONS
        #include <exception>
    #endif
    #ifdef __cpp_lib_expected
        #include <expected>
    #endif
    #if defined(__cpp_lib_format) || (defined(_MSC_VER) && _MSC_VER >= 1929)
        #include <format>
    #endif
    #include <functional>
    #include <iostream>
    #include <iterator>
    #include <limits>
    #include <memory>
    #include <new>
    #include <random>
    #include <optional>
    #if defined(CPP2_USE_SOURCE_LOCATION)
        #include <source_location>
    #endif
    #include <span>
    #include <string>
    #include <string_view>
    #include <system_error>
    #include <tuple>
    #include <type_traits>
    #ifndef CPP2_NO_RTTI
        #include <typeinfo>
    #endif
    #include <utility>
    #include <variant>
    #include <vector>
#endif


#define CPP2_TYPEOF(x)              std::remove_cvref_t<decltype(x)>
#define CPP2_FORWARD(x)             std::forward<decltype(x)>(x)
#define CPP2_PACK_EMPTY(x)          (sizeof...(x) == 0)
#define CPP2_CONTINUE_BREAK(NAME)   goto CONTINUE_##NAME; CONTINUE_##NAME: continue; goto BREAK_##NAME; BREAK_##NAME: break;
                                    // these redundant goto's to avoid 'unused label' warnings


#if defined(_MSC_VER)
   // MSVC can't handle 'inline constexpr' yet in all cases
    #define CPP2_CONSTEXPR const
#else
    #define CPP2_CONSTEXPR constexpr
#endif


namespace cpp2 {


//-----------------------------------------------------------------------
//
//  Convenience names for fundamental types
//
//  Note: De jure, some of these are optional per the C and C++ standards
//        De facto, all of these are supported in all implementations I know of
//
//-----------------------------------------------------------------------
//

//  Encouraged by default: Fixed-precision names
using i8        = std::int8_t        ;
using i16       = std::int16_t       ;
using i32       = std::int32_t       ;
using i64       = std::int64_t       ;
using u8        = std::uint8_t       ;
using u16       = std::uint16_t      ;
using u32       = std::uint32_t      ;
using u64       = std::uint64_t      ;

//  Discouraged: Variable precision names
//                 short
using ushort     = unsigned short;
//                 int
using uint       = unsigned int;
//                 long
using ulong      = unsigned long;
using longlong   = long long;
using ulonglong  = unsigned long long;
using longdouble = long double;

//  Strongly discouraged, for compatibility/interop only
using _schar     = signed char;      // normally use i8 instead
using _uchar     = unsigned char;    // normally use u8 instead

//-----------------------------------------------------------------------
//
//  Helper for concepts
//
//-----------------------------------------------------------------------
//

template<typename Ret, typename Arg>
auto argument_of_helper(Ret(*) (Arg)) -> Arg;

template<typename Ret, typename F, typename Arg>
auto argument_of_helper(Ret(F::*) (Arg)) -> Arg;

template<typename Ret, typename F, typename Arg>
auto argument_of_helper(Ret(F::*) (Arg) const) -> Arg;

template <typename F>
auto argument_of_helper(F) -> CPP2_TYPEOF(argument_of_helper(&F::operator()));

template <typename T>
using argument_of_t = CPP2_TYPEOF(argument_of_helper(std::declval<T>()));

template <typename T>
using pointee_t = std::iter_value_t<T>;

template <typename T>
using value_type_of_t = typename std::remove_cvref_t<T>::value_type;

template <template <typename...> class C, typename... Ts>
constexpr auto specialization_of_template_helper(C< Ts...> const& ) -> std::true_type {
    return {};
}

template <template <typename, auto...> class C, typename T, auto... Ns>
    requires (sizeof...(Ns) > 0)
constexpr auto specialization_of_template_helper(C< T, Ns... > const& ) -> std::true_type {
    return {};
}

//-----------------------------------------------------------------------
//
//  Concepts
//
//-----------------------------------------------------------------------
//

template <typename X, template<typename...> class C>
concept specialization_of_template = requires (X x) {
    { specialization_of_template_helper<C>(std::forward<X>(x)) } -> std::same_as<std::true_type>;
};

template <typename X, template<typename,auto...> class C>
concept specialization_of_template_type_and_nttp = requires (X x) {
    { specialization_of_template_helper<C>(std::forward<X>(x)) } -> std::same_as<std::true_type>;
};

template <template <typename...> class C>
concept type_trait = std::derived_from<C<int>, std::true_type> || std::derived_from<C<int>, std::false_type>;

template<typename X>
concept boolean_testable = std::convertible_to<X, bool> && requires(X&& x) {
  { !std::forward<X>(x) } -> std::convertible_to<bool>;
};

template <typename X>
concept polymorphic = std::is_polymorphic_v<std::remove_cvref_t<X>>;

template <typename X>
concept pointer = std::is_pointer_v<std::remove_cvref_t<X>>;

template <typename X>
concept reference = std::is_reference_v<X&&>;

template <typename X>
concept polymorphic_pointer = pointer<X> 
                        && polymorphic<std::remove_pointer_t<std::remove_cvref_t<X>>>;

template <typename X>
concept non_polymorphic_pointer = pointer<X> 
                        && !polymorphic<std::remove_pointer_t<std::remove_cvref_t<X>>>;

template <typename X>
concept dereferencable = requires (X x) { *x; };

template <typename X>
concept default_constructible = std::is_default_constructible_v<std::remove_cvref_t<X>>;

template <typename X>
concept bounded_array = std::is_bounded_array_v<std::remove_cvref_t<X>>;

template <typename X>
concept pointer_like = dereferencable<X> && default_constructible<X> && std::equality_comparable<X>
                       && !bounded_array<X>;

template <typename X>
concept not_pointer_like = !pointer_like<X>;

template< typename From, typename To >
concept brace_initializable_to = requires (From x) { To{x}; };

template< typename From, typename To >
concept no_brace_initializable_to = !brace_initializable_to<From, To>;

template <typename C, typename X>
concept different_sign_types = std::is_signed_v<std::remove_cvref_t<C>> != std::is_signed_v<std::remove_cvref_t<X>>;

template< typename X, typename C >
concept type_bigger_than = sizeof(X) > sizeof(C);

template <typename X, typename C>
concept not_bigger_than = std::integral<std::remove_cvref_t<X>> && !type_bigger_than<X, C>; //sizeof(X) <= sizeof(C);

template <typename T>
concept arithmetic = std::is_arithmetic_v<std::remove_cvref_t<T>>;

template< typename X, typename C >
concept same_type_as = std::same_as<std::remove_cvref_t<X>, C>;

template <typename X, typename C>
concept not_same_as = !same_type_as<X, C>;

template <typename X, typename... Ts>
concept not_one_of = (not_same_as<X,Ts> && ...) ;

template <typename X>
concept const_type = std::is_const_v<X> || std::is_const_v<std::remove_reference_t<X>>;

template <typename X>
concept has_defined_argument = requires { 
	std::declval<argument_of_t<X>>(); 
};

template <typename X, typename F>
concept covertible_to_argument_of = same_type_as<X,argument_of_t<F>>
                                 || (pointer_like<argument_of_t<F>> && brace_initializable_to<X, pointee_t<argument_of_t<F>>>)
                                 || (!pointer_like<argument_of_t<F>> && brace_initializable_to<X, argument_of_t<F>>)
                                 ;

template <typename F, typename X>
concept valid_predicate = (std::predicate<F, X> && !has_defined_argument<F>)
                          || (std::predicate<F, X> && has_defined_argument<F> && covertible_to_argument_of<X, F>);

template <typename V, typename X>
concept callable_with_explicit_type = requires (V value) {
    {value.template operator()<X>()};
};

template <typename V, typename X>
concept has_custom_operator_is = requires (V value, X x){ 
	value.op_is(x); 
};

template< typename T >
concept enum_type = std::is_enum_v<std::remove_cvref_t<T>>;

template <typename X, typename C>
concept can_bound_to__impl__ = same_type_as<X, C> 
                       || (
                            std::derived_from<std::remove_cvref_t<X>, std::remove_cvref_t<C>> 
                        )
                       || (
                            !(polymorphic<X> && polymorphic<C>)
                            && requires (X x){ static_cast<C&>(x); }
                        );

template <typename X, typename C>
concept can_bound_to = can_bound_to__impl__<X, C> 
                       || can_bound_to__impl__<pointee_t<X>, pointee_t<C>>;

template <typename X, typename C>
concept cannot_bound_to = !can_bound_to<X,C> && !can_bound_to<pointee_t<X>, C>;

//-----------------------------------------------------------------------
//
//  General helpers
//
//-----------------------------------------------------------------------
//

inline constexpr auto max(auto... values) {
    return std::max( { values... } );
}

template <class T, class... Ts>
inline constexpr auto is_any = std::disjunction_v<std::is_same<T, Ts>...>;

template <std::size_t Len, std::size_t Align>
struct aligned_storage {
    alignas(Align) unsigned char data[Len];
};

//-----------------------------------------------------------------------
//
//  A type_find_if for iterating over types in parameter packs
//
//  Note: the current implementation is a workaround for clang-12 internal error.
//  Original implementation does not need type_it and is implemented
//  using lambda with explicit parameter type list in the following way:
//
//    template <typename... Ts, typename F>
//    constexpr auto type_find_if(F&& fun)
//    {
//        std::size_t found = std::variant_npos;
//        [&]<std::size_t... Is>(std::index_sequence<Is...>){
//            if constexpr ((requires { {CPP2_FORWARD(fun).template operator()<Is, Ts>()} -> std::convertible_to<bool>;} && ...)) {
//                (((CPP2_FORWARD(fun).template operator()<Is, Ts>()) && (found = Is, true)) || ...);
//            }
//        }(std::index_sequence_for<Ts...>());
//        return found;
//    }
//
//  The workaround is not needed in gcc-12.1+, clang-13+, msvc 19.29+
//
//  Note2: the internal if constexpr could have else with static_assert.
//  Unfortunatelly I cannot make it work on MSVC.
//
//-----------------------------------------------------------------------
//
template <std::size_t Index, typename T>
struct type_it {
    using type = T;
    inline static const std::size_t index = Index;
};

template <typename... Ts, typename F>
constexpr auto type_find_if(F&& fun)
{
    std::size_t found = std::variant_npos;
    [&]<std::size_t... Is>(std::index_sequence<Is...>){
        if constexpr ((requires { {CPP2_FORWARD(fun)(type_it<Is, Ts>{})} -> boolean_testable;} && ...)) {
            ((CPP2_FORWARD(fun)(type_it<Is, Ts>{}) && (found = Is, true)) || ...);
        } 
    }(std::index_sequence_for<Ts...>());
    return found;
}

template <typename F, template<typename...> class C, typename... Ts>
constexpr auto type_find_if(C<Ts...>, F&& fun)
{
    return type_find_if<Ts...>(CPP2_FORWARD(fun));
}

template <typename T, typename... Ts>
constexpr auto variant_contains_type(std::variant<Ts...>)
{
    if constexpr (is_any<T, Ts...>) {
        return std::true_type{};
    } else {
        return std::false_type{};
    }
}

//-----------------------------------------------------------------------
//
//  String: A helper workaround for passing a string literal as a
//  template argument
//
//-----------------------------------------------------------------------
//
template<std::size_t N>
struct String
{
    constexpr String(const char (&str)[N])
    {
        std::copy_n(str, N, value);
    }

    auto operator<=>(String const&) const = default;

    char value[N] = {};
};


//-----------------------------------------------------------------------
//
//  contract_group
//
//-----------------------------------------------------------------------
//

#ifdef CPP2_USE_SOURCE_LOCATION
    #define CPP2_SOURCE_LOCATION_PARAM              , std::source_location where
    #define CPP2_SOURCE_LOCATION_PARAM_WITH_DEFAULT , std::source_location where = std::source_location::current()
    #define CPP2_SOURCE_LOCATION_PARAM_SOLO         std::source_location where
    #define CPP2_SOURCE_LOCATION_ARG                , where
#else
    #define CPP2_SOURCE_LOCATION_PARAM
    #define CPP2_SOURCE_LOCATION_PARAM_WITH_DEFAULT
    #define CPP2_SOURCE_LOCATION_PARAM_SOLO
    #define CPP2_SOURCE_LOCATION_ARG
#endif

//  For C++23: make this std::string_view and drop the macro
//      Before C++23 std::string_view was not guaranteed to be trivially copyable,
//      and so in<T> will pass it by const& and really it should be by value
#define CPP2_MESSAGE_PARAM  char const*
#define CPP2_CONTRACT_MSG   cpp2::message_to_cstr_adapter

inline auto message_to_cstr_adapter( CPP2_MESSAGE_PARAM msg ) -> CPP2_MESSAGE_PARAM { return msg ? msg : ""; }
inline auto message_to_cstr_adapter( std::string const& msg ) -> CPP2_MESSAGE_PARAM { return msg.c_str(); }

class contract_group {
public:
    using handler = void (*)(CPP2_MESSAGE_PARAM msg CPP2_SOURCE_LOCATION_PARAM);

    constexpr contract_group  (handler h = {}) : reporter{h} { }
    constexpr auto set_handler(handler h = {}) { reporter = h; }
    constexpr auto get_handler() const -> handler { return reporter; }
    constexpr auto has_handler() const -> bool    { return reporter != handler{}; }

    constexpr auto enforce(bool b, CPP2_MESSAGE_PARAM msg = "" CPP2_SOURCE_LOCATION_PARAM_WITH_DEFAULT)
                                          -> void { if (!b) report_violation(msg CPP2_SOURCE_LOCATION_ARG); }
    constexpr auto report_violation(CPP2_MESSAGE_PARAM msg = "" CPP2_SOURCE_LOCATION_PARAM_WITH_DEFAULT)
                                          -> void { if (reporter) reporter(msg CPP2_SOURCE_LOCATION_ARG); }
private:
    handler reporter;
};

[[noreturn]] inline auto report_and_terminate(std::string_view group, CPP2_MESSAGE_PARAM msg = "" CPP2_SOURCE_LOCATION_PARAM_WITH_DEFAULT) noexcept -> void {
    std::cerr
#ifdef CPP2_USE_SOURCE_LOCATION
        << where.file_name() << "("
        << where.line() << ") "
        << where.function_name() << ": "
#endif
        << group << " violation";
    if (msg && msg[0] != '\0') {
        std::cerr << ": " << msg;
    }
    std::cerr << "\n";
    std::terminate();
}

auto inline Default = contract_group(
    [](CPP2_MESSAGE_PARAM msg CPP2_SOURCE_LOCATION_PARAM)noexcept {
        report_and_terminate("Contract",      msg CPP2_SOURCE_LOCATION_ARG);
    }
);
auto inline Bounds  = contract_group(
    [](CPP2_MESSAGE_PARAM msg CPP2_SOURCE_LOCATION_PARAM)noexcept {
        report_and_terminate("Bounds safety", msg CPP2_SOURCE_LOCATION_ARG);
    }
);
auto inline Null    = contract_group(
    [](CPP2_MESSAGE_PARAM msg CPP2_SOURCE_LOCATION_PARAM)noexcept {
        report_and_terminate("Null safety",   msg CPP2_SOURCE_LOCATION_ARG);
    }
);
auto inline Type    = contract_group(
    [](CPP2_MESSAGE_PARAM msg CPP2_SOURCE_LOCATION_PARAM)noexcept {
        report_and_terminate("Type safety",   msg CPP2_SOURCE_LOCATION_ARG);
    }
);
auto inline Testing = contract_group(
    [](CPP2_MESSAGE_PARAM msg CPP2_SOURCE_LOCATION_PARAM)noexcept {
        report_and_terminate("Testing",       msg CPP2_SOURCE_LOCATION_ARG);
    }
);


//  Check for invalid dereference or indirection which would result in undefined behavior.
// 
//     - Null pointer
//     - std::unique_ptr that owns nothing
//     - std::shared_ptr with no managed object
//     - std::optional with no value
//     - std::expected containing an unexpected value
// 
//  Note: For naming simplicity we consider all the above cases to be "null" states so that
//        we can write: `*assert_not_null(object)`.
//
template<typename T>
concept UniquePtr = std::is_same_v<T, std::unique_ptr<typename T::element_type, typename T::deleter_type>>;

template<typename T>
concept SharedPtr = std::is_same_v<T, std::shared_ptr<typename T::element_type>>;

template<typename T>
concept Optional = std::is_same_v<T, std::optional<typename T::value_type>>;

#ifdef __cpp_lib_expected

template<typename T>
concept Expected = std::is_same_v<T, std::expected<typename T::value_type, typename T::error_type>>;

#endif

auto assert_not_null(auto&& arg CPP2_SOURCE_LOCATION_PARAM_WITH_DEFAULT) -> decltype(auto)
{
    //  NOTE: This "!= T{}" test may or may not work for STL iterators. The standard
    //        doesn't guarantee that using == and != will reliably report whether an
    //        STL iterator has the default-constructed value. So use it only for raw *...
    if constexpr (std::is_pointer_v<CPP2_TYPEOF(arg)>) {
        if (arg == CPP2_TYPEOF(arg){}) {
            Null.report_violation("dynamic null dereference attempt detected" CPP2_SOURCE_LOCATION_ARG);
        };
    }
    else if constexpr (UniquePtr<CPP2_TYPEOF(arg)>) {
        if (!arg) {
            Null.report_violation("std::unique_ptr is empty" CPP2_SOURCE_LOCATION_ARG);
        }
    }
    else if constexpr (SharedPtr<CPP2_TYPEOF(arg)>) {
        if (!arg) {
            Null.report_violation("std::shared_ptr is empty" CPP2_SOURCE_LOCATION_ARG);
        }
    }
    else if constexpr (Optional<CPP2_TYPEOF(arg)>) {
        if (!arg.has_value()) {
            Null.report_violation("std::optional does not contain a value" CPP2_SOURCE_LOCATION_ARG);
        }
    }
#ifdef __cpp_lib_expected
    else if constexpr (Expected<CPP2_TYPEOF(arg)>) {
        if (!arg.has_value()) {
            Null.report_violation("std::expected has an unexpected value" CPP2_SOURCE_LOCATION_ARG);
        }
    }
#endif

    return CPP2_FORWARD(arg);
}

//  Subscript bounds checking
//
#define CPP2_ASSERT_IN_BOUNDS_IMPL \
    requires (std::is_integral_v<CPP2_TYPEOF(arg)> && \
             requires { std::size(x); std::ssize(x); x[arg]; std::begin(x) + 2; }) \
{ \
    auto max = [&]() -> auto { \
        if constexpr (std::is_signed_v<CPP2_TYPEOF(arg)>) { return std::ssize(x); } \
        else { return std::size(x); } \
    }; \
    auto msg = "out of bounds access attempt detected - attempted access at index " + std::to_string(arg) + ", "; \
    if (max() > 0 ) { \
        msg += "[min,max] range is [0," + std::to_string(max()-1) + "]"; \
    } \
    else { \
        msg += "but container is empty"; \
    } \
    if (!(0 <= arg && arg < max())) { \
        Bounds.report_violation(msg.c_str()  CPP2_SOURCE_LOCATION_ARG); \
    } \
    return CPP2_FORWARD(x) [ arg ]; \
}

template<auto arg>
auto assert_in_bounds(auto&& x CPP2_SOURCE_LOCATION_PARAM_WITH_DEFAULT) -> decltype(auto)
    CPP2_ASSERT_IN_BOUNDS_IMPL

auto assert_in_bounds(auto&& x, auto&& arg CPP2_SOURCE_LOCATION_PARAM_WITH_DEFAULT) -> decltype(auto)
    CPP2_ASSERT_IN_BOUNDS_IMPL

template<auto arg>
auto assert_in_bounds(auto&& x CPP2_SOURCE_LOCATION_PARAM_WITH_DEFAULT) -> decltype(auto)
{
    return CPP2_FORWARD(x) [ arg ];
}

auto assert_in_bounds(auto&& x, auto&& arg CPP2_SOURCE_LOCATION_PARAM_WITH_DEFAULT) -> decltype(auto)
{
    return CPP2_FORWARD(x) [ CPP2_FORWARD(arg) ];
}

#define CPP2_ASSERT_IN_BOUNDS(x,arg)         (cpp2::assert_in_bounds((x),(arg)))
#define CPP2_ASSERT_IN_BOUNDS_LITERAL(x,arg) (cpp2::assert_in_bounds<(arg)>(x))


//-----------------------------------------------------------------------
//
//  Support wrappers that unblock using this file in environments that
//  disable EH or RTTI
//
//  Note: This is not endorsing disabling those features, it's just
//        recognizing that disabling them is popular (e.g., games, WASM)
//        and so we should remove a potential adoption blocker... only a
//        few features in this file depend on EH or RTTI anyway, and
//        wouldn't be exercised in such an environment anyway so there
//        is no real net loss here
//
//-----------------------------------------------------------------------
//

[[noreturn]] auto Throw(auto&& x, [[maybe_unused]] char const* msg) -> void {
#ifdef CPP2_NO_EXCEPTIONS
    auto err = std::string{"exceptions are disabled with -fno-exceptions - attempted to throw exception with type \"" + typeid(decltype(x)).name() + "\""};
    if (msg) {
        err += " and the message \"" + msg + "\"";
    }
    Type.report_violation( err );
    std::terminate();
#else
    throw CPP2_FORWARD(x);
#endif
}

inline auto Uncaught_exceptions() -> int {
#ifdef CPP2_NO_EXCEPTIONS
    return 0;
#else
    return std::uncaught_exceptions();
#endif
}

template<typename T>
auto Dynamic_cast( [[maybe_unused]] auto&& x ) -> decltype(auto) {
#ifdef CPP2_NO_RTTI
    Type.report_violation( "'as' dynamic casting is disabled with -fno-rtti" );
    return nullptr;
#else
    return dynamic_cast<T>(CPP2_FORWARD(x));
#endif
}

template<typename T>
auto Typeid() -> decltype(auto) {
#ifdef CPP2_NO_RTTI
    Type.report_violation( "'any' dynamic casting is disabled with -fno-rtti" );
#else
    return typeid(T);
#endif
}

auto Typeid( [[maybe_unused]] auto&& x ) -> decltype(auto) {
#ifdef CPP2_NO_RTTI
    Type.report_violation( "'typeid' is disabled with -fno-rtti" );
#else
    return typeid(CPP2_FORWARD(x));
#endif
}


//-----------------------------------------------------------------------
//
//  Arena objects for std::allocators
//
//  Note: cppfront translates "new" to "cpp2_new", so in Cpp2 code
//        these are invoked by simply "unique.new<T>" etc.
//
//-----------------------------------------------------------------------
//
struct {
    template<typename T>
    [[nodiscard]] auto cpp2_new(auto&& ...args) const -> std::unique_ptr<T> {
        //  Prefer { } to ( ) so that initializing a vector<int> with
        //  (10), (10, 20), and (10, 20, 30) is consistent
        if constexpr (requires { T{CPP2_FORWARD(args)...}; }) {
            //  This is because apparently make_unique can't deal with list
            //  initialization of aggregates, even after P0960
            return std::unique_ptr<T>( new T{CPP2_FORWARD(args)...} );
        }
        else {
            return std::make_unique<T>(CPP2_FORWARD(args)...);
        }
    }
} inline unique;

[[maybe_unused]] struct {
    template<typename T>
    [[nodiscard]] auto cpp2_new(auto&& ...args) const -> std::shared_ptr<T> {
        //  Prefer { } to ( ) as noted for unique.new
        //
        //  Note this does mean we don't get the make_shared optimization a lot
        //  of the time -- we can restore that as soon as make_shared improves to
        //  allow list initialization. But the make_shared optimization isn't a
        //  huge deal anyway: it saves one allocation, but most of the cost of
        //  shared_ptrs is copying them and the allocation cost saving is probably
        //  outweighed by just a couple of shared_ptr copies; also, the make_shared
        //  optimization has the potential downside of keeping the raw storage
        //  alive longer when there are weak_ptrs. So, yes, we can and should
        //  restore the make_shared optimization as soon as make_shared supports
        //  list init, but I don't think it's all that important AFAIK
        if constexpr (requires { T{CPP2_FORWARD(args)...}; }) {
            //  Why this calls 'unique.new': The workaround to use { } initialization
            //  requires calling naked 'new' to allocate the object separately anyway,
            //  so reuse the unique.new path that already does that (less code
            //  duplication, plus encapsulate the naked 'new' in one place)
            return unique.cpp2_new<T>(CPP2_FORWARD(args)...);
        }
        else {
            return std::make_shared<T>(CPP2_FORWARD(args)...);
        }
    }
} inline shared;

template<typename T>
[[nodiscard]] auto cpp2_new(auto&& ...args) -> std::unique_ptr<T> {
    return unique.cpp2_new<T>(CPP2_FORWARD(args)...);
}


//-----------------------------------------------------------------------
//
//  in<T>       For "in" parameter
//
//-----------------------------------------------------------------------
//
template<typename T>
constexpr bool prefer_pass_by_value =
    sizeof(T) <= 2*sizeof(void*)
    && std::is_trivially_copy_constructible_v<T>;

template<typename T>
    requires std::is_class_v<T> || std::is_union_v<T> || std::is_array_v<T> || std::is_function_v<T>
constexpr bool prefer_pass_by_value<T> = false;

template<typename T>
    requires (!std::is_void_v<T>)
using in =
    std::conditional_t <
        prefer_pass_by_value<T>,
        T const,
        T const&
    >;

template <typename C, typename X>
using constness_like_t = 
  std::conditional_t<
    std::is_const_v<
      std::remove_pointer_t<
        std::remove_reference_t<X>
      >
    >,
    std::add_const_t<C>,
    std::remove_const_t<C>
  >;

template <typename C, typename X>
using forward_like_t =
  std::conditional_t<
    std::is_rvalue_reference_v<X>,
    std::add_rvalue_reference_t<constness_like_t<C,X>>,
    std::conditional_t<
        std::is_lvalue_reference_v<X>,
        std::add_lvalue_reference_t<constness_like_t<C,X>>,
        constness_like_t<C,X>
    >
  >;

template<class T, class U>
[[nodiscard]] constexpr auto&& forward_like(U&& x) noexcept
{
    constexpr bool is_adding_const = std::is_const_v<std::remove_reference_t<T>>;
    if constexpr (std::is_lvalue_reference_v<T&&>)
    {
        if constexpr (is_adding_const)
            return std::as_const(x);
        else
            return static_cast<U&>(x);
    }
    else
    {
        if constexpr (is_adding_const)
            return std::move(std::as_const(x));
        else
            return std::move(x);
    }
}

//-----------------------------------------------------------------------
//
//  Initialization: These are closely related...
//
//  deferred_init<T>    For deferred-initialized local object
//
//  out<T>              For out parameter
//
//-----------------------------------------------------------------------
//
template<typename T>
class deferred_init {
    alignas(T) std::byte data[sizeof(T)];
    bool init = false;

    auto t() -> T& { return *std::launder(reinterpret_cast<T*>(&data)); }

    template<typename U>
    friend class out;

    auto destroy() -> void         { if (init) { t().~T(); }  init = false; }

public:
    deferred_init() noexcept       { }
   ~deferred_init() noexcept       { destroy(); }
    auto value()    noexcept -> T& { Default.enforce(init);  return t(); }

    auto construct(auto&& ...args) -> void { Default.enforce(!init);  new (&data) T{CPP2_FORWARD(args)...};  init = true; }
};


template<typename T>
class out {
    //  Not going to bother with std::variant here
    union {
        T* t;
        deferred_init<T>* dt;
    };
    out<T>* ot = {};
    bool has_t;

    //  Each out in a chain contains its own uncaught_count ...
    int  uncaught_count   = Uncaught_exceptions();
    //  ... but all in a chain share the topmost called_construct_
    bool called_construct_ = false;

public:
    out(T*                 t_) noexcept :  t{ t_}, has_t{true}       { Default.enforce( t); }
    out(deferred_init<T>* dt_) noexcept : dt{dt_}, has_t{false}      { Default.enforce(dt); }
    out(out<T>*           ot_) noexcept : ot{ot_}, has_t{ot_->has_t} { Default.enforce(ot);
        if (has_t) {  t = ot->t;  }
        else       { dt = ot->dt; }
    }

    auto called_construct() -> bool& {
        if (ot) { return ot->called_construct(); }
        else    { return called_construct_; }
    }

    //  In the case of an exception, if the parameter was uninitialized
    //  then leave it in the same state on exit (strong guarantee)
    ~out() {
        if (called_construct() && uncaught_count != Uncaught_exceptions()) {
            Default.enforce(!has_t);
            dt->destroy();
            called_construct() = false;
        }
    }

    auto construct(auto&& ...args) -> void {
        if (has_t || called_construct()) {
            if constexpr (requires { *t = T(CPP2_FORWARD(args)...); }) {
                Default.enforce( t );
                *t = T(CPP2_FORWARD(args)...);
            }
            else {
                Default.report_violation("attempted to copy assign, but copy assignment is not available");
            }
        }
        else {
            Default.enforce( dt );
            if (dt->init) {
                if constexpr (requires { *t = T(CPP2_FORWARD(args)...); }) {
                    dt->value() = T(CPP2_FORWARD(args)...);
                }
                else {
                    Default.report_violation("attempted to copy assign, but copy assignment is not available");
                }
            }
            else {
                dt->construct(CPP2_FORWARD(args)...);
                called_construct() = true;
            }
        }
    }

    auto value() noexcept -> T& {
        if (has_t) {
            Default.enforce( t );
            return *t;
        }
        else {
            Default.enforce( dt );
            return dt->value();
        }
    }
};


//-----------------------------------------------------------------------
//
//  CPP2_UFCS: Variadic macro generating a variadic lamba, oh my...
//
//-----------------------------------------------------------------------
//
// Workaround <https://github.com/llvm/llvm-project/issues/70556>.
#define CPP2_FORCE_INLINE_LAMBDA_CLANG /* empty */

#if defined(_MSC_VER) && !defined(__clang_major__)
    #define CPP2_FORCE_INLINE              __forceinline
    #define CPP2_FORCE_INLINE_LAMBDA       [[msvc::forceinline]]
    #define CPP2_LAMBDA_NO_DISCARD
#else
    #define CPP2_FORCE_INLINE              __attribute__((always_inline))
    #if defined(__clang__)
        #define CPP2_FORCE_INLINE_LAMBDA       /* empty */
        #undef CPP2_FORCE_INLINE_LAMBDA_CLANG
        #define CPP2_FORCE_INLINE_LAMBDA_CLANG __attribute__((always_inline))
    #else
        #define CPP2_FORCE_INLINE_LAMBDA       __attribute__((always_inline))
    #endif

    #if defined(__clang_major__)
        //  Also check __cplusplus, only to satisfy Clang -pedantic-errors
        #if __cplusplus >= 202302L && (__clang_major__ > 13 || (__clang_major__ == 13 && __clang_minor__ >= 2))
            #define CPP2_LAMBDA_NO_DISCARD   [[nodiscard]]
        #else
            #define CPP2_LAMBDA_NO_DISCARD
        #endif
    #elif defined(__GNUC__)
        #if __GNUC__ >= 9
            #define CPP2_LAMBDA_NO_DISCARD   [[nodiscard]]
        #else
            #define CPP2_LAMBDA_NO_DISCARD
        #endif
        #if ((__GNUC__ * 100) + __GNUC_MINOR__) < 1003
            //  GCC 10.2 doesn't support this feature (10.3 is fine)
            #undef  CPP2_FORCE_INLINE_LAMBDA
            #define CPP2_FORCE_INLINE_LAMBDA
        #endif
    #else
        #define CPP2_LAMBDA_NO_DISCARD
    #endif
#endif

#define CPP2_UFCS_REMPARENS(...) __VA_ARGS__

// Ideally, the expression `CPP2_UFCS_IS_NOTHROW` expands to
// is in the _noexcept-specifier_ of the UFCS lambda, but without 'std::declval'.
// To workaround [GCC bug 101043](https://gcc.gnu.org/bugzilla/show_bug.cgi?id=101043),
// we instead make it a template parameter of the UFCS lambda.
// But using a template parameter, Clang also ICEs on an application.
// So we use these `NOTHROW` macros to fall back to the ideal for when not using GCC.
#define CPP2_UFCS_IS_NOTHROW(QUALID,TEMPKW,...) \
   requires { requires  requires { std::declval<Obj>().CPP2_UFCS_REMPARENS QUALID TEMPKW __VA_ARGS__(std::declval<Params>()...); }; \
              requires    noexcept(std::declval<Obj>().CPP2_UFCS_REMPARENS QUALID TEMPKW __VA_ARGS__(std::declval<Params>()...)); } \
|| requires { requires !requires { std::declval<Obj>().CPP2_UFCS_REMPARENS QUALID TEMPKW __VA_ARGS__(std::declval<Params>()...); }; \
              requires noexcept(CPP2_UFCS_REMPARENS QUALID __VA_ARGS__(std::declval<Obj>(), std::declval<Params>()...)); }
#define CPP2_UFCS_IS_NOTHROW_PARAM(...)               /*empty*/
#define CPP2_UFCS_IS_NOTHROW_ARG(QUALID,TEMPKW,...)   CPP2_UFCS_IS_NOTHROW(QUALID,TEMPKW,__VA_ARGS__)
#if defined(__GNUC__) && !defined(__clang__)
    #undef  CPP2_UFCS_IS_NOTHROW_PARAM
    #undef  CPP2_UFCS_IS_NOTHROW_ARG
    #define CPP2_UFCS_IS_NOTHROW_PARAM(QUALID,TEMPKW,...) , bool IsNothrow = CPP2_UFCS_IS_NOTHROW(QUALID,TEMPKW,__VA_ARGS__)
    #define CPP2_UFCS_IS_NOTHROW_ARG(...)                 IsNothrow
    #if __GNUC__ < 11
        #undef  CPP2_UFCS_IS_NOTHROW_PARAM
        #undef  CPP2_UFCS_IS_NOTHROW_ARG
        #define CPP2_UFCS_IS_NOTHROW_PARAM(...)    /*empty*/
        #define CPP2_UFCS_IS_NOTHROW_ARG(...)      false // GCC 10 UFCS is always potentially-throwing.
    #endif
#endif

// Ideally, the expression `CPP2_UFCS_CONSTRAINT_ARG` expands to
// is in the _requires-clause_ of the UFCS lambda.
// To workaround an MSVC bug within a member function 'F' where UFCS is also for 'F'
// (<https://github.com/hsutter/cppfront/pull/506#issuecomment-1826086952>),
// we instead make it a template parameter of the UFCS lambda.
// But using a template parameter, Clang also ICEs and GCC rejects a local 'F'.
// Also, Clang rejects the SFINAE test case when using 'std::declval'.
// So we use these `CONSTRAINT` macros to fall back to the ideal for when not using MSVC.
#define CPP2_UFCS_CONSTRAINT_PARAM(...)               /*empty*/
#define CPP2_UFCS_CONSTRAINT_ARG(QUALID,TEMPKW,...) \
   requires { CPP2_FORWARD(obj).CPP2_UFCS_REMPARENS QUALID TEMPKW __VA_ARGS__(CPP2_FORWARD(params)...); } \
|| requires { CPP2_UFCS_REMPARENS QUALID __VA_ARGS__(CPP2_FORWARD(obj), CPP2_FORWARD(params)...); }
#if defined(_MSC_VER)
    #undef  CPP2_UFCS_CONSTRAINT_PARAM
    #undef  CPP2_UFCS_CONSTRAINT_ARG
    #define CPP2_UFCS_CONSTRAINT_PARAM(QUALID,TEMPKW,...) , bool IsViable = \
   requires { std::declval<Obj>().CPP2_UFCS_REMPARENS QUALID TEMPKW __VA_ARGS__(std::declval<Params>()...); } \
|| requires { CPP2_UFCS_REMPARENS QUALID __VA_ARGS__(std::declval<Obj>(), std::declval<Params>()...); }
    #define CPP2_UFCS_CONSTRAINT_ARG(...)                 IsViable
#endif

#define CPP2_UFCS_(LAMBDADEFCAPT,QUALID,TEMPKW,...) \
[LAMBDADEFCAPT]< \
    typename Obj, typename... Params \
    CPP2_UFCS_IS_NOTHROW_PARAM(QUALID,TEMPKW,__VA_ARGS__) \
    CPP2_UFCS_CONSTRAINT_PARAM(QUALID,TEMPKW,__VA_ARGS__) \
  > \
  CPP2_LAMBDA_NO_DISCARD (Obj&& obj, Params&& ...params) CPP2_FORCE_INLINE_LAMBDA_CLANG \
  noexcept(CPP2_UFCS_IS_NOTHROW_ARG(QUALID,TEMPKW,__VA_ARGS__)) CPP2_FORCE_INLINE_LAMBDA -> decltype(auto) \
    requires CPP2_UFCS_CONSTRAINT_ARG(QUALID,TEMPKW,__VA_ARGS__) { \
    if constexpr (requires{ CPP2_FORWARD(obj).CPP2_UFCS_REMPARENS QUALID TEMPKW __VA_ARGS__(CPP2_FORWARD(params)...); }) { \
        return CPP2_FORWARD(obj).CPP2_UFCS_REMPARENS QUALID TEMPKW __VA_ARGS__(CPP2_FORWARD(params)...); \
    } else { \
        return CPP2_UFCS_REMPARENS QUALID __VA_ARGS__(CPP2_FORWARD(obj), CPP2_FORWARD(params)...); \
    } \
}

#define CPP2_UFCS(...)                                    CPP2_UFCS_(&,(),,__VA_ARGS__)
#define CPP2_UFCS_TEMPLATE(...)                           CPP2_UFCS_(&,(),template,__VA_ARGS__)
#define CPP2_UFCS_QUALIFIED_TEMPLATE(QUALID,...)          CPP2_UFCS_(&,QUALID,template,__VA_ARGS__)
#define CPP2_UFCS_NONLOCAL(...)                           CPP2_UFCS_(,(),,__VA_ARGS__)
#define CPP2_UFCS_TEMPLATE_NONLOCAL(...)                  CPP2_UFCS_(,(),template,__VA_ARGS__)
#define CPP2_UFCS_QUALIFIED_TEMPLATE_NONLOCAL(QUALID,...) CPP2_UFCS_(,QUALID,template,__VA_ARGS__)


//-----------------------------------------------------------------------
//
//  to_string for string interpolation
//
//-----------------------------------------------------------------------
//
//  For use when returning "no such thing", such as
//  when customizing "as" for std::variant

inline auto to_string(...) -> std::string
{
    return "(customize me - no cpp2::to_string overload exists for this type)";
}

inline auto to_string(std::same_as<std::any> auto const&) -> std::string
{
    return "std::any";
}

inline auto to_string(std::same_as<bool> auto b) -> std::string
{
    return b ? "true" : "false";
}

template <typename X>
concept has_std_to_string_overload = requires (std::remove_cvref_t<X> x) {
    std::to_string(x);
};

template <has_std_to_string_overload X>
    requires not_one_of<X, bool, char>
auto to_string( X const x ) -> std::string { 
    return std::to_string(x); 
}

template <brace_initializable_to<std::string> T>
    requires not_one_of<T, bool, std::true_type, std::false_type>
inline auto to_string(T const& s) -> std::string
{
    return std::string(s);
}

template <typename... Ts>
inline auto to_string(std::variant<Ts...> const& v) -> std::string;

template < typename T, typename U>
inline auto to_string(std::pair<T,U> const& p) -> std::string;

template < typename... Ts>
inline auto to_string(std::tuple<Ts...> const& t) -> std::string;

template<typename T>
inline auto to_string(std::optional<T> const& o) -> std::string {
    if (o.has_value()) {
        return cpp2::to_string(o.value());
    }
    return "(empty)";
}

inline auto to_string(std::same_as<std::monostate> auto const&) -> std::string {
    return "(empty)";
}

template <typename T>
concept has_to_string_overload = requires{ static_cast<std::string (*)(std::remove_cvref_t<T> const&)>(&to_string); }
                                 || requires{ static_cast<std::string (*)(std::remove_cvref_t<T>)>(&to_string); };

template <typename T>
concept no_to_string_overload = !has_to_string_overload<T>;

template <typename... Ts>
inline auto to_string(std::variant<Ts...> const& v) -> std::string
{
    if (v.valueless_by_exception()) return "(empty)";

    return std::visit([]<typename T>(T const& arg) -> std::string {
        if constexpr (has_to_string_overload<T> || std::is_copy_constructible_v<T>) {
            return cpp2::to_string(arg);
        } else {
            return cpp2::to_string(std::ref(arg)); // cpp2::to_string(...) requires copy constructible type
        }
    }, v);
}

template < typename T, typename U>
inline auto to_string(std::pair<T,U> const& p) -> std::string
{
    return "(" + cpp2::to_string(p.first) + ", " + cpp2::to_string(p.second) + ")";
}

template < typename... Ts>
inline auto to_string(std::tuple<Ts...> const& t) -> std::string
{
    if constexpr (sizeof...(Ts) == 0) {
        return "()";
    } else {
        std::string out = "(" + cpp2::to_string(std::get<0>(t));
        std::apply([&out](auto&&, auto&&... args) {
            ((out += ", " + cpp2::to_string(args)), ...);
        }, t);
        out += ")";
        return out;
    }
}

//  MSVC supports it but doesn't define __cpp_lib_format until the ABI stablizes, but here
//  don't care about that, so consider it as supported since VS 2019 16.10 (_MSC_VER 1929)
#if defined(__cpp_lib_format) || (defined(_MSC_VER) && _MSC_VER >= 1929)
inline auto to_string(auto&& value, std::string_view fmt) -> std::string
{
    return std::vformat(fmt, std::make_format_args(CPP2_FORWARD(value)));
}
#else
inline auto to_string(auto&& value, std::string_view) -> std::string
{
    //  This Cpp1 implementation does not support <format>-ted string interpolation
    //  so the best we can do is ignore the formatting request (degraded operation
    //  seems better than a dynamic error message string or a hard error)
    return to_string(CPP2_FORWARD(value));
}
#endif

enum class casting_errors {
    unknown, narrowing_cast, no_to_string_cast, no_to_string_cast_for_aggregate_types
};

//  For use when returning "no such thing", such as
//  when customizing "as" for std::variant
template <casting_errors error = casting_errors::unknown>
struct nonesuch_ {
    auto operator==(auto const&) -> bool { return false; }
};
constexpr inline nonesuch_<> nonesuch;

template <typename X>
concept nonesuch_specialization = requires (X x) {
    { is<nonesuch_>(x) } -> std::same_as<std::true_type>;
};

//-----------------------------------------------------------------------
//
//  and "as std::string" for the same cases
//
template <template<typename...> class C, typename... Ts>
constexpr auto has_recursive_to_string_overload(C<Ts...> const&)
{
    if constexpr ((has_to_string_overload<Ts> && ...)) {
        return std::true_type{};
    } else {
        return std::false_type{};
    }
}


template <std::same_as<std::string> C, has_to_string_overload X>
    requires not_same_as<X, std::string> && (same_type_as<X, bool> || no_brace_initializable_to<X, C>)
auto as( X&& x ) {
    if constexpr (same_type_as<X, std::any>) {
        return nonesuch_<cpp2::casting_errors::no_to_string_cast>{};
    } else if constexpr (specialization_of_template<X, std::variant> 
        && requires {
            { has_recursive_to_string_overload(x) } -> std::same_as<std::false_type>;
        }
    ) {
        return nonesuch_<cpp2::casting_errors::no_to_string_cast_for_aggregate_types>{};
    } else {
        return to_string(x); 
    }
}

//-----------------------------------------------------------------------
//
//  is and as
//
//-----------------------------------------------------------------------
//

//-------------------------------------------------------------------------------------------------------------
//  Built-in is
//

//  For designating "holds no value" -- used only with is, not as
//  TODO: Does this really warrant a new synonym? Perhaps "is void" is enough
using empty = void;

//  Type is Type
//

template <typename X, typename C>
constexpr auto is() -> std::false_type { return {}; }

template <typename X, typename C>
    requires std::same_as<X, C> || std::derived_from<X,C>
constexpr auto is() -> std::true_type { return {}; }

//  Type is Template
//

template <typename X, template <typename, typename...> class C>
constexpr auto is() -> std::false_type { return {}; }

template <typename X, template <typename, typename...> class C>
    requires specialization_of_template<X, C>
constexpr auto is() -> std::true_type { return {}; }

template <typename X, template <typename, auto, auto...> class C>
constexpr auto is() -> std::false_type { return {}; }

template <typename X, template <typename, auto, auto...> class C>
    requires specialization_of_template_type_and_nttp<X, C>
constexpr auto is() -> std::true_type { return {}; }

//  Type is Type Traits
//

template <typename  X, template <typename, typename...> class C>
    requires type_trait<C>
constexpr auto is() -> C<X> { return {}; }

//  Type is Concept
//

template <typename X, auto C>
constexpr auto is() {
    if constexpr (callable_with_explicit_type<CPP2_TYPEOF(C), X>) {
        return std::true_type{};
    } else {
        return std::false_type{};
    }
}

//  Variable is Template
//

template <template <typename...> class C, specialization_of_template<C> X>
    // requires (!specialization_of_template<X, std::variant>)
constexpr auto is( X&& ) -> std::true_type {
    return {};
}
template <template <typename...> class C, typename T>
constexpr auto is( T&& ) -> std::false_type {
    return {};
}

template <template <typename, auto, auto...> class C, typename T, auto... Vs>
constexpr auto is( C<T, Vs...> const& ) -> std::true_type {
    return {};
}

// additional auto required not to collide with is type_trait
template <template <typename, auto, auto...> class C, typename T>
constexpr auto is( T const& ) -> std::false_type {
    return {};
}

template <template <auto, auto...> class C, auto... Vs>
constexpr auto is( C<Vs...> const& ) -> std::true_type {
    return {};
}

template <template <auto, auto...> class C, typename T>
constexpr auto is( T const& ) -> std::false_type {
    return {};
}

// Variable is Type_traits
//
template <template <typename...> class C, typename X>
    requires type_trait<C>
constexpr auto is( X&& ) -> decltype(auto) {
    if constexpr (
        C<X&&>::value
        || C<std::remove_reference_t<X>>::value
        || C<std::remove_cv_t<X>>::value
        || C<std::remove_cvref_t<X>>::value
    ) {
        return std::true_type{};
    } else {
        return std::false_type{};
    }
}

//  Variable is Type
//
template< typename C, typename X >
constexpr auto is( X && ) -> std::false_type {
    return {};
}

template< typename C, can_bound_to<C> X >
constexpr auto is( X && ) -> std::true_type {
    return {};
}

template< polymorphic C, polymorphic X >
    requires std::derived_from<X, C>
constexpr auto is( X && ) -> std::true_type { return {}; }

template< polymorphic C, polymorphic X >
constexpr auto is( X&& x ) {
    if constexpr ( const_type<std::remove_reference_t<X>> && !const_type<C>) {
        return std::false_type{};
    } else {
        return Dynamic_cast<std::add_pointer_t<C>>(&x) != nullptr;
    }
}

template< polymorphic_pointer C, polymorphic_pointer X >
    requires std::derived_from<pointee_t<X>, pointee_t<C>>
constexpr auto is( X && ) -> std::true_type { return {}; }

template< polymorphic_pointer C, polymorphic_pointer X >
constexpr auto is( X&& x ) {
    if constexpr ( const_type<std::remove_pointer_t<std::remove_reference_t<X>>> && !const_type<std::remove_pointer_t<C>>) {
        return std::false_type{};
    } else {
        return Dynamic_cast<std::add_pointer_t<std::add_const_t<std::remove_pointer_t<C>>>>(x) != nullptr;
    }
}

template< std::same_as<empty> C, pointer_like X >
constexpr auto is( X && x ) -> bool {
    return x == std::remove_cvref_t<X>();
}

template< std::same_as<empty> C, typename X >
    requires same_type_as<X, std::nullptr_t> || same_type_as<X, std::monostate>
constexpr auto is( X && ) -> std::true_type {
    return {};
}

//  Variable is Value
//
template <typename X, typename V>
constexpr auto is( X const&, V && ) -> std::false_type {
    return {};
}

template <typename X, has_custom_operator_is<X> V>
constexpr bool is( X const& x, V && value ) {
    return value.op_is(x);
}

template <not_pointer_like X, valid_predicate<X> V>
constexpr bool is( X const& x, V && value ) {
    return value(x);
}

template <not_pointer_like X, std::equality_comparable_with<X> V>
constexpr bool is( X const& x, V && value ) {
    return x == value;
}

template <not_pointer_like X, std::equality_comparable_with<X> V>
    requires std::ranges::range<X> && std::ranges::range<V> && std::equality_comparable_with<std::ranges::range_value_t<X>, std::ranges::range_value_t<V>> 
constexpr bool is( X const& x, V && value ) {
    if constexpr (std::convertible_to<X, std::string_view> && std::convertible_to<V, std::string_view>) {
        return std::string_view(x) == std::string_view(value);
    } else {
        return std::equal(std::cbegin(x), std::cend(x),
                        std::cbegin(value), std::cend(value));
    }
}

template <std::ranges::range X, std::ranges::range V>
    requires std::equality_comparable_with<std::ranges::range_value_t<X>, std::ranges::range_value_t<V>> 
constexpr bool is( X const& x, V && value ) {
    return std::equal(std::cbegin(x), std::cend(x),
                      std::cbegin(value), std::cend(value));
}

template <typename X, callable_with_explicit_type<X> V>
constexpr auto is( X const&, V &&) -> std::true_type {
    return {};
}

//-----------------------------------------------------------------------
//
//  and "is predicate" for generic function used as predicate
//

template <typename X>
inline constexpr auto is( X const& x, bool (*value)(X const&) ) -> bool {
    return value(x);
}

//-------------------------------------------------------------------------------------------------------------
//  Built-in as
//

template <std::same_as<std::string> C, not_same_as<std::string> X>
    requires no_brace_initializable_to<X, C> && no_to_string_overload<X>
auto as( X&& ) -> nonesuch_<casting_errors::no_to_string_cast> { return {}; }

template< typename From, typename To > // https://eel.is/c++draft/dcl.init.list#7
concept narrowing_to = arithmetic<From> && arithmetic<To> && !brace_initializable_to<From, To>;

template <typename... Ts>
inline constexpr auto program_violates_type_safety_guarantee = sizeof...(Ts) < 0;

template< typename C, auto x >
concept castable = requires{ C{x}; };

//  As
//

template <typename C,        typename X > auto as( X&& ) -> nonesuch_<> { return {}; }
template< typename C, narrowing_to<C> X > auto as( X&& ) -> nonesuch_<casting_errors::narrowing_cast> { return {}; }

template< not_same_as<std::string> C, brace_initializable_to<C> X >
    requires not_same_as<X, C>
auto as( X&& x ) -> decltype(auto) {
    return C{std::forward<X>(x)};
}

template< typename C, pointer_like X >
    requires brace_initializable_to<pointee_t<X>, C> && not_one_of<pointee_t<X>, C>
auto as( X&& x ) -> decltype(auto) {
    if (x) {
        return C{*std::forward<X>(x)};
    }
    Throw( std::bad_cast(), "'as' cast failed for 'pointer_like'");
}

template< typename C, arithmetic auto x >
    requires castable<C, x> || castable<value_type_of_t<C>, x>
inline constexpr auto as() -> auto {
    return static_cast<C>(x);
}

template< typename C, same_type_as<C> X >
auto as( X&& x ) -> decltype(auto) {
    return std::forward<X>(x);
}

template< pointer C, pointer X >
    requires can_bound_to<X, C>
auto as( X&& x ) -> decltype(auto) {
    return static_cast<forward_like_t<C, X>>(x);
}

template< pointer C, same_type_as<pointee_t<C>> X >
    requires (!std::is_rvalue_reference_v<X&&>)
auto as( X&& x ) -> decltype(auto) {
    return &std::forward<forward_like_t<std::remove_pointer_t<C>,X&&>>(x);
}

template< typename C, not_same_as<C> X >
    requires std::derived_from<std::remove_cvref_t<X>, C>
auto as( X&& x ) -> decltype(auto) {
    return std::forward<forward_like_t<C,X&&>>(x);
}

template< polymorphic C, polymorphic X >
    requires reference<X> && (!std::derived_from<std::remove_cvref_t<X>, C>)
auto as( X&& x ) -> decltype(auto) {
    return Dynamic_cast<forward_like_t<C,X&&>>(std::forward<X>(x));
}

template< polymorphic C, polymorphic_pointer X >
auto as( X&& x ) -> forward_like_t<C,X&&> {
    return Dynamic_cast<forward_like_t<C,X&&>>(*x);
}

template< polymorphic_pointer C, polymorphic_pointer X >
    requires (!can_bound_to<X, C>)
auto as( X&& x ) -> decltype(auto) {
    return Dynamic_cast<forward_like_t<pointee_t<C>,std::remove_pointer_t<std::remove_cvref_t<X>>>*>(x);
}

template< polymorphic_pointer C, polymorphic X >
    requires not_same_as<pointee_t<C>, X>
auto as( X&& x ) -> decltype(auto) {
    return Dynamic_cast<std::remove_reference_t<forward_like_t<std::remove_pointer_t<C>,X>>*>(&x);
}


//-------------------------------------------------------------------------------------------------------------
//  std::any is and as
//

//  std::any variable is Type
//
template<typename T>
constexpr auto is( same_type_as<std::any> auto && x ) -> bool
    { return x.type() == Typeid<T>(); }

template<std::same_as<empty> T>
constexpr auto is( same_type_as<std::any> auto && x ) -> bool
    { return !x.has_value(); }


//  std::any variable is Value
//

template <std::same_as<std::any> X, has_defined_argument V>
    requires not_same_as<std::any, argument_of_t<V>>
constexpr bool is( X const& x, V && value ) {
    auto* ptr = std::any_cast<argument_of_t<V>>(&x);
    return ptr && value(*ptr);
}

template <std::same_as<std::any> X, std::equality_comparable V>
    requires (!has_defined_argument<V>)
constexpr bool is( X const& x, V && value ) {
    if constexpr (pointer_like<V>) {
        auto* ptr = std::any_cast<pointee_t<V>>(&x);
        return ptr && !is<empty>(value) && is(*ptr, *value);
    } else {
        auto* ptr = std::any_cast<std::remove_cvref_t<V>>(&x);
        return ptr && is(*ptr, std::forward<V>(value));
    }
}

//  as
//
template<typename T, same_type_as<std::any> X>
auto as( X && x ) -> decltype(auto) {
    auto* ptr = std::any_cast<T>(&x);
    if (!ptr) { Throw( std::bad_any_cast(), "'as' cast failed for 'any'"); } 
    return forward_like<X>(*ptr);
}

//-------------------------------------------------------------------------------------------------------------
//  std::optional is and as
//

//  std::optional variable is Type
//
template<not_same_as<empty> T, specialization_of_template<std::optional> U>
constexpr auto is( U&& x ) {
    if constexpr (same_type_as<T, pointee_t<U>>) {
        return std::true_type{};
    } else {
        return std::false_type{};
    }
}

//-------------------------------------------------------------------------------------------------------------
//  forward declarations needed for recursive calls
//

template<specialization_of_template<std::variant> T, typename C>
constexpr auto is( T&& x, C&& value );

//-------------------------------------------------------------------------------------------------------------
//  pointer_like variable is value
//

template <pointer_like X, typename V>
constexpr auto is( X const& x, V && value) -> decltype(auto) {
    if constexpr (pointer<X> && pointer<V>) {
        return x == value;
    } else {
        return !is<empty>(x) && is(*x, value);
    }
}

//-------------------------------------------------------------------------------------------------------------
//  std::variant is and as
//

//  std::variant variable is Template
//

template<template <typename...> class C, specialization_of_template<std::variant> T>
    requires (!specialization_of_template<T, C>)
constexpr auto is( T&& x ) {
    return type_find_if(x, [&]<typename It>(It const&) -> bool {
        if (x.index() == It::index) { return is<C>(forward_like<T>(std::get<It::index>(x)));}
        return false;
    }) != std::variant_npos;
}

template <template <typename...> class C, typename... Ts>
    requires std::same_as<C<Ts...>, std::variant<Ts...>>
constexpr auto is( std::variant<Ts...> const& ) -> std::true_type {
    return {};
}

template<template <typename, auto...> class C, specialization_of_template<std::variant> T>
constexpr auto is( T&& x ) {
    return type_find_if(x, [&]<typename It>(It const&) -> bool {
        if (x.index() == It::index) { return is<C>(forward_like<T>(std::get<It::index>(x)));}
        return false;
    }) != std::variant_npos || specialization_of_template_type_and_nttp<T, C>;
}

//  std::variant variable is Value
//

template<specialization_of_template<std::variant> T, typename C>
constexpr auto is( T&& x, C&& value ) {
    if constexpr (std::same_as<T,C>) {
        return x == value;
    } else {
        return type_find_if(x, [&]<typename It>(It const&) -> bool {
            if (x.index() == It::index) { return is(forward_like<T>(std::get<It::index>(x)), std::forward<C>(value));}
            return false;
        }) != std::variant_npos;
    }
}

//  std::variant variable is Type
//
template<specialization_of_template<std::variant> T, specialization_of_template<std::variant> C>
constexpr auto is( C&& ) {
    if constexpr (std::same_as<std::remove_cvref_t<T>, std::remove_cvref_t<C>>) {
        return std::true_type{};
    } else {
        return std::false_type{};
    }
}

template<typename C, specialization_of_template<std::variant> T>
auto is( T&& x ) {
    return type_find_if(x, [&]<typename It>(It const&) -> bool {
        if (x.index() == It::index) { return is<C>(std::get<It::index>(x));}
        return false;
    }) != std::variant_npos;
}

template<std::same_as<empty> C, specialization_of_template<std::variant> T>
auto is( T&& x ) {
    if (x.valueless_by_exception())
        return true;
    if constexpr (requires { {variant_contains_type<std::monostate>(std::declval<T>())} -> std::same_as<std::true_type>; }) 
        return std::get_if<std::monostate>(&x) != nullptr;
    return false;
}

template<not_same_as<std::string> T, specialization_of_template<std::variant> X>
auto as( X && x ) -> decltype(auto) {
    constness_like_t<T, X>* ptr = nullptr;
    type_find_if(std::forward<X>(x), [&]<typename It>(It const&) -> bool {
        if constexpr (std::is_same_v< typename It::type, T >) { if (std::forward<X>(x).index() ==  It::index) { ptr = &std::get<It::index>(x); return true; } }; return false;
    });
    if (!ptr) { Throw( std::bad_variant_access(), "'as' cast failed for 'variant'"); } 
    return forward_like<X>(*ptr);
}

template< typename C, pointer_like X >
    requires can_bound_to<pointee_t<X>, C>
auto as( X&& x ) -> decltype(auto) {
    if (x) {
        return forward_like<X>(*x);
    }
    Throw( std::bad_cast(), "'as' cast failed for 'pointer_like'");
}

//-----------------------------------------------------------------------
//
//  A variation of GSL's final_action_success / finally
//
//  finally ensures something is run at the end of a scope always
//
//  finally_success ensures something is run at the end of a scope
//      if no exception is thrown
//
//  finally_presuccess ensures a group of add'd operations are run
//      immediately before (not after) the return if no exception is
//      thrown - right now this is used only for postconditions, so
//      they can inspect named return values before they're moved from
//
//-----------------------------------------------------------------------
//

template <class F>
class finally_success
{
public:
    explicit finally_success(const F& ff) noexcept : f{ff} { }
    explicit finally_success(F&& ff) noexcept : f{std::move(ff)} { }

    ~finally_success() noexcept
    {
        if (invoke && ecount == std::uncaught_exceptions()) {
            f();
        }
    }

    finally_success(finally_success&& that) noexcept
        : f(std::move(that.f)), invoke(std::exchange(that.invoke, false))
    { }

    finally_success(finally_success const&) = delete;
    void operator= (finally_success const&) = delete;
    void operator= (finally_success&&)      = delete;

private:
    F f;
    int  ecount = std::uncaught_exceptions();
    bool invoke = true;
};


template <class F>
class finally
{
public:
    explicit finally(const F& ff) noexcept : f{ff} { }
    explicit finally(F&& ff) noexcept : f{std::move(ff)} { }

    ~finally() noexcept { f(); }

    finally(finally&& that) noexcept
        : f(std::move(that.f)), invoke(std::exchange(that.invoke, false))
    { }

    finally       (finally const&) = delete;
    void operator=(finally const&) = delete;
    void operator=(finally&&)      = delete;

private:
    F f;
    bool invoke = true;
};


class finally_presuccess
{
public:
    finally_presuccess() = default;

    auto add(const auto& f) { fs.push_back(f); }

    //  In compiled Cpp2 code, this function will be called
    //  immediately before 'return' (both explicit and implicit)
    auto run() {
        if (invoke && ecount == std::uncaught_exceptions()) {
            for (auto const& f : fs) {
                f();
            }
        }
        invoke = false;
    }

    ~finally_presuccess() noexcept {
        run();
    }

    finally_presuccess(finally_presuccess const&) = delete;
    void operator=    (finally_presuccess const&) = delete;
    void operator=    (finally_presuccess &&)     = delete;

private:
    std::vector<std::function<void()>> fs;
    int  ecount = std::uncaught_exceptions();
    bool invoke = true;
};


//-----------------------------------------------------------------------
//
//  args: see main() arguments as vector<string_view>
//
//-----------------------------------------------------------------------
//
struct args_t : std::vector<std::string_view>
{
    args_t(int c, char** v) : vector{static_cast<std::size_t>(c)}, argc{c}, argv{v} {}

    mutable int        argc = 0;        //  mutable for compatibility with frameworks that take 'int& argc'
    char**             argv = nullptr;
};

inline auto make_args(int argc, char** argv) -> args_t
{
    auto ret  = args_t{argc, argv};
    auto args = std::span(argv, static_cast<std::size_t>(argc));
    std::copy( args.begin(), args.end(), ret.data());
    return ret;
}


//-----------------------------------------------------------------------
//
//  alien_memory: memory typed as T but that is outside C++ and that the
//                compiler may not assume it knows anything at all about
//
//-----------------------------------------------------------------------
//
template<typename T>
using alien_memory = T volatile;


//-----------------------------------------------------------------------
//
//  An implementation of GSL's narrow_cast with a clearly 'unsafe' name
//
//-----------------------------------------------------------------------
//
template <typename C, typename X>
constexpr auto unsafe_narrow( X&& x ) noexcept -> decltype(auto)
{
    return static_cast<C>(CPP2_FORWARD(x));
}


//-----------------------------------------------------------------------
//
//  has_flags:  query whether a flag_enum value has all flags in 'flags' set
//
//  flags       set of flags to check
//
//  Returns a function object that takes a 'value' of the same type as
//  'flags', and evaluates to true if and only if 'value' has set all of
//  the bits set in 'flags'
//
//-----------------------------------------------------------------------
//
template <typename T>
auto has_flags(T flags)
{
    return [=](T value) { return (value & flags) == flags; };
}


//-----------------------------------------------------------------------
//
//  Speculative: RAII wrapping for the C standard library
//
//  As part of embracing compatibility while also reducing what we have to
//  teach and learn about C++ (which includes the C standard library), I
//  was curious to see if we can improve use of the C standard library
//  from Cpp2 code... UFCS is a part of that, and then RAII destructors is
//  another that goes hand in hand with that, hence this section...
//  but see caveat note at the end.
//
//-----------------------------------------------------------------------
//
template<typename T, typename D>
class c_raii {
    T t;
    D dtor;
public:
    c_raii( T t_, D d )
        : t{ t_ }
        , dtor{ d }
    { }

    ~c_raii() { dtor(t); }

    operator T&() { return t; }

    c_raii(c_raii const&)         = delete;
    auto operator=(c_raii const&) = delete;
};

inline auto fopen( const char* filename, const char* mode ) {

    //  Suppress annoying deprecation warning about fopen
    #ifdef _MSC_VER
        #pragma warning( push )
        #pragma warning( disable : 4996 )
    #endif

    auto x = std::fopen(filename, mode);

    #ifdef _MSC_VER
        #pragma warning( pop )
    #endif

    if (!x) {
        Throw( std::make_error_condition(std::errc::no_such_file_or_directory), "'fopen' attempt failed");
    }
    return c_raii( x, &std::fclose );
}

//  Caveat: There's little else in the C stdlib that allocates a resource...
//
//      malloc          is already wrapped like this via std::unique_ptr, which
//                        typically uses malloc or gets memory from the same pool
//      thrd_create     std::jthread is better
//
//  ... is that it? I don't think it's useful to provide a c_raii just for fopen,
//  but perhaps c_raii may be useful for bringing forward third-party C code too,
//  with cpp2::fopen as a starting example.


//-----------------------------------------------------------------------
//
//  Signed/unsigned comparison checks
//
//-----------------------------------------------------------------------
//
template<typename T, typename U>
CPP2_FORCE_INLINE constexpr auto cmp_mixed_signedness_check() -> void
{
    if constexpr (
        std::is_same_v<T, bool> ||
        std::is_same_v<U, bool>
        )
    {
        static_assert(
            program_violates_type_safety_guarantee<T, U>,
            "comparing bool values using < <= >= > is unsafe and not allowed - are you missing parentheses?");
    }
    else if constexpr (
        std::is_integral_v<T> &&
        std::is_integral_v<U> &&
        std::is_signed_v<T> != std::is_signed_v<U>
        )
    {
        //  Note: It's tempting here to "just call std::cmp_*() instead"
        //  which does signed/unsigned relational comparison correctly
        //  for negative values, and so silently "fix that for you." But
        //  doing that has security pitfalls for the reasons described at
        //  https://github.com/hsutter/cppfront/issues/220, so this
        //  static_assert to reject the comparison is the right way to go.
        static_assert(
            program_violates_type_safety_guarantee<T, U>,
            "mixed signed/unsigned comparison is unsafe - prefer using .ssize() instead of .size(), consider using std::cmp_less instead, or consider explicitly casting one of the values to change signedness by using 'as' or 'cpp2::unsafe_narrow'"
            );
    }
}


CPP2_FORCE_INLINE constexpr auto cmp_less(auto&& t, auto&& u) -> decltype(auto)
    requires requires {CPP2_FORWARD(t) < CPP2_FORWARD(u);}
{
    cmp_mixed_signedness_check<CPP2_TYPEOF(t), CPP2_TYPEOF(u)>();
    return CPP2_FORWARD(t) < CPP2_FORWARD(u);
}

CPP2_FORCE_INLINE constexpr auto cmp_less(auto&& t, auto&& u) -> decltype(auto)
{
    static_assert(
        program_violates_type_safety_guarantee<decltype(t), decltype(u)>,
        "attempted to compare '<' for incompatible types"
        );
    return nonesuch;
}


CPP2_FORCE_INLINE constexpr auto cmp_less_eq(auto&& t, auto&& u) -> decltype(auto)
    requires requires {CPP2_FORWARD(t) <= CPP2_FORWARD(u);}
{
    cmp_mixed_signedness_check<CPP2_TYPEOF(t), CPP2_TYPEOF(u)>();
    return CPP2_FORWARD(t) <= CPP2_FORWARD(u);
}

CPP2_FORCE_INLINE constexpr auto cmp_less_eq(auto&& t, auto&& u) -> decltype(auto)
{
    static_assert(
        program_violates_type_safety_guarantee<decltype(t), decltype(u)>,
        "attempted to compare '<=' for incompatible types"
        );
    return nonesuch;
}


CPP2_FORCE_INLINE constexpr auto cmp_greater(auto&& t, auto&& u) -> decltype(auto)
    requires requires {CPP2_FORWARD(t) > CPP2_FORWARD(u);}
{
    cmp_mixed_signedness_check<CPP2_TYPEOF(t), CPP2_TYPEOF(u)>();
    return CPP2_FORWARD(t) > CPP2_FORWARD(u);
}

CPP2_FORCE_INLINE constexpr auto cmp_greater(auto&& t, auto&& u) -> decltype(auto)
{
    static_assert(
        program_violates_type_safety_guarantee<decltype(t), decltype(u)>,
        "attempted to compare '>' for incompatible types"
        );
    return nonesuch;
}


CPP2_FORCE_INLINE constexpr auto cmp_greater_eq(auto&& t, auto&& u) -> decltype(auto)
    requires requires {CPP2_FORWARD(t) >= CPP2_FORWARD(u);}
{
    cmp_mixed_signedness_check<CPP2_TYPEOF(t), CPP2_TYPEOF(u)>();
    return CPP2_FORWARD(t) >= CPP2_FORWARD(u);
}

CPP2_FORCE_INLINE constexpr auto cmp_greater_eq(auto&& t, auto&& u) -> decltype(auto)
{
    static_assert(
        program_violates_type_safety_guarantee<decltype(t), decltype(u)>,
        "attempted to compare '>=' for incompatible types"
        );
    return nonesuch;
}



//-----------------------------------------------------------------------
//
//  A static-asserting "as" for better diagnostics than raw 'nonesuch'
//
//  Note for the future: This needs go after all 'as', which is fine for
//  the ones in this file but will have problems with further user-
//  defined 'as' customizations. One solution would be to make the main
//  'as' be a class template, and have all customizations be actual
//  specializations... that way name lookup should find the primary
//  template first and then see later specializations. Or we could just
//  remove this and live with the 'nonesuch' error messages. Either way,
//  we don't need anything more right now, this solution is fine to
//  unblock general progress
//
//-----------------------------------------------------------------------
//
template <typename C, typename X > 
auto as_( X&& x ) -> decltype(auto) 
{ 
    if constexpr ( requires { {as<C>(std::forward<X>(x))} -> std::same_as<nonesuch_<casting_errors::narrowing_cast>>; } ) {
        static_assert(
            program_violates_type_safety_guarantee<C, X>,
            "'as' does not allow unsafe narrowing conversions - if you're sure you want this, use `unsafe_narrow<T>()` to force the conversion");
    } else if constexpr ( requires { {as<C>(std::forward<X>(x))} -> std::same_as<nonesuch_<casting_errors::no_to_string_cast>>; } ) {
        static_assert(
            program_violates_type_safety_guarantee<C, X>,
            "No cpp2::to_string overload exists for this type!");
    } else if constexpr ( 
        requires { {as<C>(std::forward<X>(x))} -> nonesuch_specialization; } 
    ) {
        static_assert(
            program_violates_type_safety_guarantee<C, X>,
            "No safe 'as' cast available - please check your cast");
    } 
    return as<C>(std::forward<X>(x));
}

template< typename C, auto x >
inline constexpr auto as_() -> decltype(auto)
{
    if constexpr ( !requires { as<C, x>(); }) {
        static_assert(
            program_violates_type_safety_guarantee<C, decltype(x)>,
            "No safe 'as' cast available - please check your cast"
        );
    }
    if constexpr( requires { {as<C, x>()} -> nonesuch_specialization; } ) {
        static_assert(
            program_violates_type_safety_guarantee<C, decltype(x)>,
            "Literal cannot be narrowed using 'as' -  if you're sure you want this, use 'unsafe_narrow<T>()' to force the conversion"
        );
    }
    return as<C,x>();
}

} // namespace cpp2


using cpp2::cpp2_new;


//  Stabilize line numbers for "compatibility" static assertions that we know
//  will fire for some compilers, to keep regression test outputs cleaner
#line 9999

//  GCC 10 doesn't support 'requires' in forward declarations in some cases
//  Workaround: Disable the requires clause where that gets reasonable behavior
//  Diagnostic: static_assert the other cases that can't be worked around
#if !defined(__clang__) && defined(__GNUC__) && __GNUC__ == 10
    #define CPP2_REQUIRES(...) /* empty */
    #define CPP2_REQUIRES_(...) static_assert(false, "GCC 11 or higher is required to support variables and type-scope functions that have a 'requires' clause. This includes a type-scope 'forward' parameter of non-wildcard type, such as 'func: (this, forward s: std::string)', which relies on being able to add a 'requires' clause - in that case, use 'forward s: _' instead if you need the result to compile with GCC 10.")
#else
    #define CPP2_REQUIRES(...) requires (__VA_ARGS__)
    #define CPP2_REQUIRES_(...) requires (__VA_ARGS__)
#endif

#endif
