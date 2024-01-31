

//=== Cpp2 type declarations ====================================================


#include "cpp2util.h"

#line 1 "mixed-overview-of-is-inspections.cpp2"

#line 219 "mixed-overview-of-is-inspections.cpp2"
class A;
class B;
class C;
    

#line 225 "mixed-overview-of-is-inspections.cpp2"
template<int I> class VA;

class VC;
    

//=== Cpp2 type definitions and function declarations ===========================

#line 1 "mixed-overview-of-is-inspections.cpp2"
int* raw_null = nullptr;

auto expect_throws(auto l) -> bool {
    try {
        l();
    } catch (...) {
        return true;
    }
    return false;
}

struct ThrowingConstruction {
    constexpr ThrowingConstruction() = default;
    ThrowingConstruction(int) { throw 1; }
};

#line 18 "mixed-overview-of-is-inspections.cpp2"
auto main() -> int;

#line 219 "mixed-overview-of-is-inspections.cpp2"
class A {
      public: A() = default;
      public: A(A const&) = delete; /* No 'that' constructor, suppress copy */
      public: auto operator=(A const&) -> void = delete;
};
#line 220 "mixed-overview-of-is-inspections.cpp2"
class B {
      public: B() = default;
      public: B(B const&) = delete; /* No 'that' constructor, suppress copy */
      public: auto operator=(B const&) -> void = delete;
};
#line 221 "mixed-overview-of-is-inspections.cpp2"
class C: public A {
    public: C() = default;
    public: C(C const&) = delete; /* No 'that' constructor, suppress copy */
    public: auto operator=(C const&) -> void = delete;


#line 223 "mixed-overview-of-is-inspections.cpp2"
};

template<int I> class VA {
public: virtual ~VA() noexcept;

      public: VA() = default;
      public: VA(VA const&) = delete; /* No 'that' constructor, suppress copy */
      public: auto operator=(VA const&) -> void = delete;
};
#line 226 "mixed-overview-of-is-inspections.cpp2"

class VC: public VA<0>, public VA<1> {
    public: VC() = default;
    public: VC(VC const&) = delete; /* No 'that' constructor, suppress copy */
    public: auto operator=(VC const&) -> void = delete;


#line 230 "mixed-overview-of-is-inspections.cpp2"
};

#line 233 "mixed-overview-of-is-inspections.cpp2"
[[nodiscard]] auto pred_i(cpp2::in<int> x) -> bool;

#line 237 "mixed-overview-of-is-inspections.cpp2"
[[nodiscard]] auto pred_d(cpp2::in<double> x) -> bool;

#line 241 "mixed-overview-of-is-inspections.cpp2"
[[nodiscard]] auto pred_(auto const& x) -> bool;

#line 245 "mixed-overview-of-is-inspections.cpp2"
extern std::array<int,5> col;

auto print(auto const& what, auto const& value, auto const& expected, auto const& comment) -> void;

#line 258 "mixed-overview-of-is-inspections.cpp2"
auto print(auto const& what, auto const& value, auto const& expected) -> void;

#line 262 "mixed-overview-of-is-inspections.cpp2"
auto print(auto const& what, auto const& value, auto const& expected, auto const& result, auto const& comment) -> void;

#line 271 "mixed-overview-of-is-inspections.cpp2"
auto print_header() -> void;
#line 280 "mixed-overview-of-is-inspections.cpp2"

#include <iomanip>
#include <map>


//=== Cpp2 function definitions =================================================

#line 1 "mixed-overview-of-is-inspections.cpp2"

#line 18 "mixed-overview-of-is-inspections.cpp2"
auto main() -> int{

    print_header();
    // is template
    {
        std::vector v {1, 2, 3}; 
        print("v is vector",   cpp2::is<std::vector>(v), true);
        print("v is array",    cpp2::is<std::array>(v), false);
        print("v is optional", cpp2::is<std::optional>(std::move(v)), false);
        std::array<int,4> a {4, 3, 2, 1}; 
        print("a is array",    cpp2::is<std::array>(a), true);
        print("a is vector",   cpp2::is<std::vector>(a), false);
        print("a is optional", cpp2::is<std::optional>(std::move(a)), false);
        std::optional o {42}; 
        print("o is array",    cpp2::is<std::array>(o), false);
        print("o is vector",   cpp2::is<std::vector>(o), false);
        print("o is optional", cpp2::is<std::optional>(std::move(o)), true);

    }

    // is type
    {
        A a {}; 
        B b {}; 
        C c {}; 
        print("C is A", cpp2::is<C,A>(), true, "not expressed in cpp2");
        print("C is B", cpp2::is<C,B>(), false, "not expressed in cpp2");

        print("a is A", cpp2::is<A>(std::move(a)), true);
        print("b is A", cpp2::is<A>(std::move(b)), false);
        print("c is A", cpp2::is<A>(std::move(c)), true);
    }
    {
        VC vc {}; 
        VA<0>* ptr_va0 {&vc}; 
        VA<1>* ptr_va1 {&vc}; 
        VA<0> const* cptr_va0 {&vc}; 

        print("ptr_va0 is VC", cpp2::is<VC>(ptr_va0), true);
        print("ptr_va1 is VC", cpp2::is<VC>(ptr_va1), true);
        print("ptr_va0 is VA<1>", cpp2::is<VA<1>>(ptr_va0), true);
        print("ptr_va1 is VA<0>", cpp2::is<VA<0>>(ptr_va1), true);
        print("cptr_va0 is VC", cpp2::is<VC>(std::move(cptr_va0)), true);

        print("ptr_va0* is VC", cpp2::is<VC>(*cpp2::assert_not_null(ptr_va0)), true);
        print("ptr_va1* is VC", cpp2::is<VC>(*cpp2::assert_not_null(ptr_va1)), true);
        print("ptr_va0* is VA<1>", cpp2::is<VA<1>>(*cpp2::assert_not_null(std::move(ptr_va0))), true);
        print("ptr_va1* is VA<0>", cpp2::is<VA<0>>(*cpp2::assert_not_null(std::move(ptr_va1))), true);
    }

    // pointer-like empty check
    {
        print("raw_null is empty", cpp2::is<cpp2::empty>(raw_null), true);
        print("nullptr is empty", cpp2::is<cpp2::empty>(nullptr), true);
        print("shared_ptr() is empty", cpp2::is<cpp2::empty>(std::shared_ptr<int>()), true);
        print("unique_ptr() is empty", cpp2::is<cpp2::empty>(std::unique_ptr<int>()), true);

        auto i {42}; 
        print("i& is empty", cpp2::is<cpp2::empty>(&i), false);
        print("std::make_shared<int>(42) is empty", cpp2::is<cpp2::empty>(std::make_shared<int>(42)), false);
        print("std::make_unique<int>(44) is empty", cpp2::is<cpp2::empty>(std::make_unique<int>(44)), false);
    }

    // values check
    {
        auto i {42}; 
        print("i{42} is empty", cpp2::is<cpp2::empty>(i), false);
        print("i{42} is 24",    cpp2::is(i, 24), false);
        print("i{42} is 42",    cpp2::is(i, 42), true);
        print("i{42} is 42u",   cpp2::is(i, 42u), true);
        print("i{42} is 42L",   cpp2::is(i, 42L), true);
        print("i{42} is 42.0",  cpp2::is(i, 42.0), true);
        print("i{42} is 42.0f", cpp2::is(std::move(i), 42.0f), true);
        print("3.14f is 3.14",  cpp2::is(3.14f, 3.14), false);
        auto close_to {[](auto const& v) mutable -> auto { return [_0 = v](auto const& x) mutable -> bool{
            return cpp2::cmp_less(std::abs(_0 - x),std::max<std::common_type_t<std::decay_t<decltype(x)>,std::decay_t<decltype(_0)>>>(std::numeric_limits<std::decay_t<decltype(x)>>::epsilon(), std::numeric_limits<std::decay_t<decltype(_0)>>::epsilon())); 
        }; }}; 
        print("3.14f is (close_to(3.14 ))",  cpp2::is(3.14f, (close_to(3.14))), true);
        print("3.14  is (close_to(3.14f))",  cpp2::is(3.14, (std::move(close_to)(3.14f))), true);
    }
/*
    // type_trait
    {
        i  : int       = 42;
        ci : const int = 24;

        print("i{int} is std::is_const",                  i is std::is_const, false);
        print("ci{const int} is std::is_const",          ci is std::is_const, true);
        print("ci{const int} is std::is_integral",       ci is std::is_integral, true);
        print("ci{const int} is std::is_floating_point", ci is std::is_floating_point, false);
    }
*/
    // predicate
    {
        auto d {3.14}; 

        print("d{3.14} is (:(x) -> bool = x>0;)", cpp2::is(d, ([](auto const& x) mutable -> bool { return cpp2::cmp_greater(x,0); })), true);
        print("d{3.14} is (:(x:int) -> bool = x>0;)", cpp2::is(d, ([](cpp2::in<int> x) mutable -> bool { return cpp2::cmp_greater(x,0); })), false);
        print("d{3.14} is (:(x:std::string) -> bool = x.ssize()>5;)", cpp2::is(d, ([](cpp2::in<std::string> x) mutable -> bool { return cpp2::cmp_greater(CPP2_UFCS(ssize)(x),5); })), false);
        print("std::string(\"abcdefg\") is (:(x:std::string) -> bool = x.ssize()>5;)", cpp2::is(std::string("abcdefg"), ([](cpp2::in<std::string> x) mutable -> bool { return cpp2::cmp_greater(CPP2_UFCS(ssize)(x),5); })), true);

        print("d{3.14} is (pred_i)", cpp2::is(d, (pred_i)), false);
        print("d{3.14} is (pred_d)", cpp2::is(d, (pred_d)), true);
        print("d{3.14} is (pred_)", true, true);

        print("d{3.14} is (:<T:std::floating_point> () -> _ = true;)", cpp2::is(d, ([]<std::floating_point T>() mutable -> auto { return true; })), true);
        print("d{3.14} is (:<T:std::floating_point> () = {})", cpp2::is(d, ([]<std::floating_point T>() mutable -> void{})), true);
        print("d{3.14} is (:<T:std::integral> () = {})", cpp2::is(std::move(d), ([]<std::integral T>() mutable -> void{})), false);
    }

    // is variant value
    {
        std::variant<int,long,float,double,std::string,std::vector<int>> v {42}; 

        print("v{42} is 42",   cpp2::is(v, 42), true);
        print("v{42} is int",   cpp2::is<int>(v), true);
        print("v{42} is int",   cpp2::is<double>(v), false);
        print("v{42} is 42.0", cpp2::is(v, 42.0), true);
        print("v{42} is 24",   cpp2::is(v, 24), false);
        print("v{42} is (std::string(\"hello\"))",   cpp2::is(v, (std::string("hello"))), false);
        print("v{42} is std::integral",   cpp2::is(v, ([]<std::integral T>() mutable -> void{})), true);
        print("v{42} is std::floating_point",   cpp2::is(v, ([]<std::floating_point T>() mutable -> void{})), false);

        v = std::string("hello");
        print("v{hello} is (std::string(\"hello\"))",   cpp2::is(v, (std::string("hello"))), true);
        print("v{hello} is 42",    cpp2::is(v, 42), false);
        print("v{hello} is empty", cpp2::is<cpp2::empty>(v), false);
        print("v{hello} is int",   cpp2::is<int>(v), false);
        print("v{hello} is std::string",   cpp2::is<std::string>(v), true);

        v = std::vector{1, 2, 3, 4};
        print("v{std::vector{1,2,3,4}} is std::vector<int>", cpp2::is<std::vector<int>>(v), true);
        print("v{std::vector{1,2,3,4}} is std::vector",      cpp2::is<std::vector>(v), true);
        print("v{std::vector{1,2,3,4}} is std::map",         cpp2::is<std::map>(v), false);
        print("v{std::vector{1,2,3,4}} is std::variant",     cpp2::is<std::variant>(std::move(v)), true);
    }

    // is variant value
    {
        std::variant<int,ThrowingConstruction,std::monostate> v {}; 
        print("v{int} is empty", cpp2::is<cpp2::empty>(v), false);

        v = std::monostate();
        print("v{monostate} is empty", cpp2::is<cpp2::empty>(v), true);

        expect_throws([_0 = (&v)]() mutable -> void { CPP2_UFCS_TEMPLATE(emplace<1>)((*cpp2::assert_not_null(_0)), 42);  });
        print("v{valueless_by_exception} is empty", cpp2::is<cpp2::empty>(v), true, "is valueless: " + cpp2::to_string(CPP2_UFCS(valueless_by_exception)(std::move(v))));

    }

    // any is type
    {
        std::any a {42}; 

        print("a{42} is int", cpp2::is<int>(a), true);
        print("a{42} is double", cpp2::is<double>(a), false);
        print("a{42} is empty", cpp2::is<cpp2::empty>(std::move(a)), false);

        print("std::any() is empty", cpp2::is<cpp2::empty>(std::any()), true);
    }

    // any is value
    {
        std::any a {42}; 

        print("a{42} is 42",  cpp2::is(a, 42), true);
        print("a{42} is 24",  cpp2::is(a, 24), false);
        print("a{42} is 42L", cpp2::is(a, 42L), false);
        print("std::any(3.14) is 3", cpp2::is(std::any(3.14), 3), false);

        print("a{42} is :(v)->bool = v.has_value();", cpp2::is(a, [](auto const& v) mutable -> bool { return CPP2_UFCS(has_value)(v); }), true);
        print("a{42} is :(v:std::any)->bool = v.has_value();", cpp2::is(a, [](cpp2::in<std::any> v) mutable -> bool { return CPP2_UFCS(has_value)(v); }), true);
        print("a{42} is :(v:int)->bool = v>0;", cpp2::is(std::move(a), [](cpp2::in<int> v) mutable -> bool { return cpp2::cmp_greater(v,0); }), true);
    }

    // optional is type
    {
        std::optional o {42}; 

        print("o{42} is int",  cpp2::is<int>(o), true);
        print("o{42} is empty",  cpp2::is<cpp2::empty>(std::move(o)), false);
        print("std::optional<int>() is empty",  cpp2::is<cpp2::empty>(std::optional<int>()), true);
    }

    // optional is value
    {
        std::optional o {42}; 

        print("o{42} is 42",   cpp2::is(o, 42), true);
        print("o{42} is 24",   cpp2::is(o, 24), false);
        print("o{42} is 42.0", cpp2::is(o, 42.0), true);

        print("o{42} is :(v) -> bool = v > 0;",   cpp2::is(o, [](auto const& v) mutable -> bool { return cpp2::cmp_greater(v,0); }), true);
        print("o{42} is :(v:std::optional<int>) -> bool = v > 0;",   cpp2::is(o, [](cpp2::in<std::optional<int>> v) mutable -> bool { return cpp2::cmp_greater(v,0); }), true);
        print("o{42} is :(v:std::optional<long>) -> bool = v > 0;",   cpp2::is(std::move(o), [](cpp2::in<std::optional<long>> v) mutable -> bool { return cpp2::cmp_greater(v,0); }), true);
        print("std::optional(3.14) is :(v:std::optional<int>) -> bool = v == 3;", cpp2::is(std::optional(3.14), [](cpp2::in<std::optional<int>> v) mutable -> bool { return *cpp2::assert_not_null(v) == 3; }), false);

    }

}

template <int I> VA<I>::~VA() noexcept{}

#line 233 "mixed-overview-of-is-inspections.cpp2"
[[nodiscard]] auto pred_i(cpp2::in<int> x) -> bool{
    return cpp2::cmp_greater(x,0); 
}

[[nodiscard]] auto pred_d(cpp2::in<double> x) -> bool{
    return cpp2::cmp_greater(x,0); 
}

[[nodiscard]] auto pred_(auto const& x) -> bool{
    return cpp2::cmp_greater(x,0); 
}

std::array<int,5> col {70, 8, 8, 8, 30}; 

auto print(auto const& what, auto const& value, auto const& expected, auto const& comment) -> void{
    auto l {[](auto const& value) mutable -> std::string{
        if (value) {
            return "true"; 
        }else {
            return "false"; 
        }
    }}; 
    print(what, l(value), std::move(l)(expected), [&] () -> std::string { auto&& _expr = (value == expected); if (cpp2::is(_expr, (true))) { if constexpr( requires{"OK";} ) if constexpr( std::is_convertible_v<CPP2_TYPEOF(("OK")),std::string> ) return "OK"; else return std::string{}; else return std::string{}; }else return "FAILED!"; }(), comment);
}

auto print(auto const& what, auto const& value, auto const& expected) -> void{
    print(what, value, expected, std::string());
}

auto print(auto const& what, auto const& value, auto const& expected, auto const& result, auto const& comment) -> void{
    std::cout << "|" << std::setw(CPP2_ASSERT_IN_BOUNDS(col, 0)) << std::right << what;
    std::cout << "|" << std::setw(CPP2_ASSERT_IN_BOUNDS(col, 1)) << std::internal << value;
    std::cout << "|" << std::setw(CPP2_ASSERT_IN_BOUNDS(col, 2)) << std::internal << expected;
    std::cout << "|" << std::setw(CPP2_ASSERT_IN_BOUNDS(col, 3)) << std::internal << result;
    std::cout << "|" << std::setw(CPP2_ASSERT_IN_BOUNDS(col, 4)) << std::left << std::setprecision(20) << comment;
    std::cout << "|" << std::endl;
}

auto print_header() -> void{
    print("Test", "Actual", "Expected", "Result", "Comment");
    print(     std::string(CPP2_ASSERT_IN_BOUNDS(col, 0) - 1, '-') + ":", 
         ":" + std::string(CPP2_ASSERT_IN_BOUNDS(col, 1) - 2, '-') + ":", 
         ":" + std::string(CPP2_ASSERT_IN_BOUNDS(col, 2) - 2, '-') + ":", 
         ":" + std::string(CPP2_ASSERT_IN_BOUNDS(col, 3) - 2, '-') + ":", 
         ":" + std::string(CPP2_ASSERT_IN_BOUNDS(col, 4) - 1, '-')
    );
}

