

//=== Cpp2 type declarations ====================================================


#include "cpp2util.h"

#line 1 "mixed-as-cast-no-to_string-overload.cpp2"

#line 5 "mixed-as-cast-no-to_string-overload.cpp2"
class A;


//=== Cpp2 type definitions and function declarations ===========================

#line 1 "mixed-as-cast-no-to_string-overload.cpp2"
auto main() -> int;

#line 5 "mixed-as-cast-no-to_string-overload.cpp2"
class A {
      public: A() = default;
      public: A(A const&) = delete; /* No 'that' constructor, suppress copy */
      public: auto operator=(A const&) -> void = delete;
};
#line 6 "mixed-as-cast-no-to_string-overload.cpp2"


//=== Cpp2 function definitions =================================================

#line 1 "mixed-as-cast-no-to_string-overload.cpp2"
auto main() -> int{
#line 2 "mixed-as-cast-no-to_string-overload.cpp2"
    cpp2::as_<std::string>(A());
}

