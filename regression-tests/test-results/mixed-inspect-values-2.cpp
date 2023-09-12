

//=== Cpp2 type declarations ====================================================


#include "cpp2util.h"



//=== Cpp2 type definitions and function declarations ===========================


#include <iostream>
#include <vector>

constexpr auto less_than = [](int value) {
    return [=](auto x) { return x < value;};
};

constexpr auto in = [](auto min, auto max) {
    return [=](auto x) {
        return min <= x && x <= max;
    };
};

constexpr auto empty = [](auto&& x){
    return std::empty(x);
};

auto negative(auto v) {
    return v < 0;
}

#line 23 "mixed-inspect-values-2.cpp2"
[[nodiscard]] auto main() -> int;
    

//=== Cpp2 function definitions =================================================


#line 23 "mixed-inspect-values-2.cpp2"
[[nodiscard]] auto main() -> int{
    auto i {15}; 

    std::cout << [&] () -> std::string { auto&& __expr = i;
        if (cpp2::is(__expr, (less_than(10)))) { if constexpr( requires{"i less than 10";} ) if constexpr( std::is_convertible_v<CPP2_TYPEOF(("i less than 10")),std::string> ) return "i less than 10"; else return std::string{}; else return std::string{}; }
        else if (cpp2::is(__expr, in(11, 20))) { if constexpr( requires{"i is between 11 and 20";} ) if constexpr( std::is_convertible_v<CPP2_TYPEOF(("i is between 11 and 20")),std::string> ) return "i is between 11 and 20"; else return std::string{}; else return std::string{}; }
        else return "i is out of our interest"; }
    () << std::endl;

    if (cpp2::is(i, (less_than(20)))) {
        std::cout << "less than 20" << std::endl;
    }

    if (cpp2::is(i, (in(10, 30)))) {
        std::cout << "i is between 10 and 30" << std::endl;
    }

    if (cpp2::is(std::move(i), (negative))) {
        std::cout << "i is negative" << std::endl;
    }else {
        std::cout << "i is not negative" << std::endl;
    }

    std::vector<int> v {}; 

    if (empty(v)) {
        std::cout << "v is empty" << std::endl;
    }

    if (cpp2::is(std::move(v), (empty))) {
        std::cout << "v is empty" << std::endl;
    }
}

