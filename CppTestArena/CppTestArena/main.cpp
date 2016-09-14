//
//  main.cpp
//  CppTestArena
//
//  Created by Brandon Stansbury on 6/21/15.
//  Copyright (c) 2015 Brandon Stansbury. All rights reserved.
//

#include <iostream>
#include <utility>
#include "LibThing.hpp"
#include "ownership.hpp"

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

void ownership()
{
    FooBar me{2};
    FooBar you{4};
    own_rvalue(std::move(me));
    own_sp(std::make_unique<FooBar>(you));
    own_rvalue({7});
}

struct Bodyless;

template<typename T>
void with_type(int i)
{
    std::cout << i << std::endl;
}

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

struct ctor_test {
    int a;
    int b;
    float c;
    
    ctor_test(int a, int b, float c) : a{a}, b{b}, c{c}
    {
        std::cout << "ctor called " << a << std::endl;
    }
    
    ctor_test(const ctor_test& that)
    {
        a = that.a;
        b = that.b;
        c = that.c;
        std::cout << "cctor called " << a << std::endl;
    }
    
    ctor_test(ctor_test&& that)
    {
        a = that.a;
        b = that.b;
        c = that.c;
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
    
    foo a = {};
    foo d{};
    foo c = {10};
    
    constexpr static int num = 10;
    static_assert(0x2 == 2, "foobar");
    //static_assert(0x2 == 0x20, "barfoo");
    
    structDeclarations();
    libthing();
    inheritance();
    with_type<Bodyless>(5);
    ctors();
    
    return 0;
}
