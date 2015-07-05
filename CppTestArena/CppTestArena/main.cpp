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

void libthing()
{
    cpptestarena::LibThing thing{5};
    thing.printStuff();
}

void ownership()
{
    FooBar me{2};
    FooBar you{4};
    own_rvalue(std::move(me));
    own_sp(std::make_unique<FooBar>(you));
    own_rvalue({7});
    own_sp(std::make_unique<FooBar>({10}));
}

int main(int argc, const char* argv[])
{
    // insert code here...
    std::cout << "Hello, World!\n";
    
    structDeclarations();
    libthing();
    
    return 0;
}
