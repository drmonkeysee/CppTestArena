//
//  main.cpp
//  CppTestArena
//
//  Created by Brandon Stansbury on 6/21/15.
//  Copyright (c) 2015 Brandon Stansbury. All rights reserved.
//

#include <iostream>
#include <utility>
#include <initializer_list>
#include <type_traits>
#include "LibThing.hpp"
#include "ownership.hpp"

template<typename T>
struct type_diagnostic;
#define check_type(x) type_diagnostic<decltype(x)> x ## Type;


// const vs constexpr

const char *cs = "foobar";
constexpr char *ces = "barfoo";
constexpr const char *cces = "baz";


// Name testing with typedefs and identifiers

struct foo {
    int v;
};

struct bar {
    bar(int v) : v{v} {}
    
    int v;
};

typedef struct blarg {
    int b;
} alt_blarg;

typedef struct fors {
    int s;
} func_or_struct;

void fors()
{
    std::cout << "i am also a function" << std::endl;
}

// conflicts with typedef of fors
//struct func_or_struct {
//    int t;
//};
//
// also conflicts with typedef of fors
//void func_or_struct()
//{
//    std::cout << "i'm a function" << std::endl;
//}

class bort {
public:
    int r;
};

void bort()
{
    std::cout << "i'm a bort function" << std::endl;
}

void structDeclarations()
{
    foo f;
    f.v = 8;
    struct foo f2;
    f2.v = 8;
    
    struct {
        int f;
    } bar;
    bar.f = 8;
    
    alt_blarg b;
    b.b = 8;
    blarg b2;
    b2.b = 8;
    struct blarg b3;
    b3.b = 8;
    
    //fors s; // fors is a function
    struct fors s;
    s.s = 8;
    fors();
    
    func_or_struct fs;
    fs.s = 8;
    
    // rvalue ctor result
    func_or_struct();
    
    //bort b; // bort is a function
    class bort brt;
    brt.r = 10;
    bort();
}


// Referencing external library and usings as typedefs

using Foo = int;
using Bar = int;

void libthing()
{
    cpptestarena::LibThing thing{5};
    thing.printStuff();
    
    Bar b = 10;
    Foo f = b;
    std::cout << f;
}


// Ownership and initialization testing

void ownership()
{
    FooBar me{2};
    FooBar us = {2};
    FooBar you{4};
    InitializationTest b{7, 8, 9};
    // copy initialization can't use explicit ctors
    //InitializationTest b2 = {4, 5, 6};
    InitializationTest b3 = b;
    own_rvalue(std::move(me));
    own_sp(std::make_unique<FooBar>(you));
    own_rvalue({7});
    
    foo a = {};
    foo d{};
    foo c = {10};
}

        
// Virtual method dispatch

struct ClassParent {
    virtual int foo() const { return 10; }
};

class StructChild : public ClassParent {
public:
    int foo() const override { return 5; }
};

void inheritance()
{
    ClassParent p;
    StructChild c;
    std::cout << "foo is " << p.foo() << " or " << c.foo() << std::endl;
}


// Constructor tests

struct ctor_test {
    int a;
    int b;
    float c;
    
    ctor_test(int a, int b, float c) : a{a}, b{b}, c{c}
    {
        std::cout << "ctor called " << a << std::endl;
    }
    
    ctor_test(const ctor_test& that) : a{that.a}, b{that.b}, c{that.c}
    {
        std::cout << "cctor called " << a << std::endl;
    }
    
    ctor_test(ctor_test&& that) : a{that.a}, b{that.b}, c{that.c}
    {
        std::cout << "mctor called " << a << std::endl;
    }
    
    ~ctor_test()
    {
        std::cout << "dtor called " << a << std::endl;
    }
};

void ctors(ctor_test arg)
{
    std::cout << "arg is " << arg.a << std::endl;
}

ctor_test make_ctor()
{
    return ctor_test{6, 7, 8.0f};
}

void ctors()
{
    ctor_test a{1, 2, 3.0f};
    ctor_test b = {2, 3, 4.0f};
    ctors(a);
    ctors(b);
    ctors({3, 4, 5.0f});
    ctors(ctor_test{4, 5, 6.0f});
    ctors(make_ctor());
    ctors(std::move(make_ctor()));
}


// Static Function Wrapping

#define stringify(e) #e
#define type_assert_failure(e) stringify(e)

template<auto fn>
using static_func = std::integral_constant<decltype(fn), fn>;

template<auto fn, typename Func = decltype(fn)>
struct better_static_func {
    using func_type = Func;
    constexpr static func_type func = fn;
    
    static_assert(std::is_function_v<std::remove_pointer_t<func_type>>,
                  "template parameter fn must be a function or pointer to function");
    
    constexpr operator func_type() const noexcept { return func; }
};

void one_param(int i)
{
    std::cout << "One param: " << i << std::endl;
}

void no_param()
{
    std::cout << "No param" << std::endl;
}

void static_func_wrapping()
{
    static_func<one_param> op;
    static_func<no_param> np;
    op(10);
    // this call is static_func<no_param>::operator() which just returns value
    // interferes with implicit conversion to function pointer
    np();
    np()();
    
    auto opf = op.value;
    auto npf = np.value;
    opf(12);
    npf();
    
    better_static_func<one_param> bop;
    better_static_func<no_param> bnp;
    bop(20);
    bnp();
    
    auto bopf = bop.func;
    auto bnpf = bnp.func;
    bopf(22);
    bnpf();
    
    better_static_func<&one_param> bopp;
    bopp(30);
    
    // fails static assert
    //better_static_func<5> badFunc;
}


// Incomplete type parameter

struct Bodyless;

template<typename T>
void with_type(int i)
{
    std::cout << "Bodyless called" << i << std::endl;
}


int main(int argc, const char* argv[])
{
    // insert code here...
    std::cout << "Hello, World!\n";
    
    int v{};
    std::cout << "v is " << v << std::endl;
    foo f;
    std::cout << "f is " << f.v << std::endl;
    bar b{2};
    std::cout << "b is " << b.v << std::endl;
    
    constexpr static int num = 10;
    static_assert(0x2 == 2, "foobar");
    //static_assert(0x2 == 0x20, "barfoo");
    
    structDeclarations();
    libthing();
    inheritance();
    with_type<Bodyless>(5);
    ctors();
    ownership();
    static_func_wrapping();
    
    return 0;
}
