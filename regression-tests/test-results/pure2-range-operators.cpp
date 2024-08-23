
#define CPP2_IMPORT_STD          Yes

//=== Cpp2 type declarations ====================================================


#include "cpp2util.h"

#line 1 "pure2-range-operators.cpp2"


//=== Cpp2 type definitions and function declarations ===========================

#line 1 "pure2-range-operators.cpp2"

#line 2 "pure2-range-operators.cpp2"
auto main() -> int;

//=== Cpp2 function definitions =================================================

#line 1 "pure2-range-operators.cpp2"

#line 2 "pure2-range-operators.cpp2"
auto main() -> int{
    std::vector v {
        "Aardvark", "Baboon", "Cat", "Dolphin", "Elephant", "Flicker", "Grue", "Wumpus"}; 

    std::cout << "We have some alpabetical animals:\n";
    for ( auto const& e : cpp2::range(CPP2_UFCS(begin)(v),CPP2_UFCS(end)(v)) ) {
        std::cout << "  " + cpp2::to_string(*cpp2::impl::assert_not_null(e)) + "\n";
    }

    std::cout << "\nAnd from indexes 1..=5 they are:\n";
    for ( auto const& e : cpp2::range(1,5,true) ) {
        std::cout << "  " + cpp2::to_string(e) + "  " + cpp2::to_string(CPP2_ASSERT_IN_BOUNDS(v, e)) + "\n";
    }

    std::list all_about {
        "Hokey", "Pokey"}; 

    std::cout << "\nMake sure non-random-access iterators work:\n";
    for ( auto const& e : cpp2::range(CPP2_UFCS(begin)(all_about),CPP2_UFCS(end)(cpp2::move(all_about))) ) {
        std::cout << "  " + cpp2::to_string(*cpp2::impl::assert_not_null(e)) + "\n";
    }

    std::cout << "\nMake sure .sum works:\n";
    std::cout << "" + cpp2::to_string(CPP2_UFCS(sum)((cpp2::range(1,20,true)))) + "\n";// prints 210
    std::cout << "" + cpp2::to_string(CPP2_UFCS(sum)((cpp2::range(1,20)))) + "\n";// prints 190

    std::cout << "\nMake sure .contains works:\n";
    std::cout << "" + cpp2::to_string(CPP2_UFCS(contains)((cpp2::range(1,20,true)), 0)) + "\n";// prints false
    std::cout << "" + cpp2::to_string(CPP2_UFCS(contains)((cpp2::range(1,20,true)), 1)) + "\n";// prints true
    std::cout << "" + cpp2::to_string(CPP2_UFCS(contains)((cpp2::range(1,20,true)), 19)) + "\n";// prints true
    std::cout << "" + cpp2::to_string(CPP2_UFCS(contains)((cpp2::range(1,20,true)), 20)) + "\n";// prints true
    std::cout << "" + cpp2::to_string(CPP2_UFCS(contains)((cpp2::range(1,20,true)), 21)) + "\n";// prints false
    std::cout << "" + cpp2::to_string(CPP2_UFCS(contains)((cpp2::range(1,20)), 0)) + "\n";// prints false
    std::cout << "" + cpp2::to_string(CPP2_UFCS(contains)((cpp2::range(1,20)), 1)) + "\n";// prints true
    std::cout << "" + cpp2::to_string(CPP2_UFCS(contains)((cpp2::range(1,20)), 19)) + "\n";// prints true
    std::cout << "" + cpp2::to_string(CPP2_UFCS(contains)((cpp2::range(1,20)), 20)) + "\n";// prints false
    std::cout << "" + cpp2::to_string(CPP2_UFCS(contains)((cpp2::range(1,20)), 21)) + "\n";// prints false

    //  Only run these parts on implementations that support views::take
    // : <V: bool = (CPP2_GCC_VER > 1400 || CPP2_CLANG_VER > 1600 || CPP2_MSVC_VER > 1920)> () = {
    //     if constexpr V
    //     {
    //         using std::views::_ ;

    //         std::cout << "\nMake sure views::take works:\n";
    //         for (1 ..= 100).take(5) do (e) {
    //             std::cout << e << " ";
    //         }   // prints: 1 2 3 4 5

    //         for (2 ..< 5).take(5) do (e) {
    //             std::cout << e << " ";
    //         }   // prints: 2 3 4
    //     }
    // } ();
}

