//
//  main.cpp
//  CppTestArena
//
//  Created by Brandon Stansbury on 6/21/15.
//  Copyright (c) 2015 Brandon Stansbury. All rights reserved.
//

#include <iostream>
#include "LibThing.h"

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

//struct func_or_struct {
//    int t;
//};
//
//void func_or_struct()
//{
//    std::cout << "i'm a function" << std::endl;
//}

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
    
    //fors s;
    struct fors s;
    s.s = 8;
    fors();
    
    func_or_struct fs;
    fs.s = 8;
    
    // rvalue ctor result
    func_or_struct();
}

void libthing()
{
    cpptestarena::LibThing thing{5};
    thing.printStuff();
}

int main(int argc, const char *argv[])
{
    // insert code here...
    std::cout << "Hello, World!\n";
    
    structDeclarations();
    libthing();
    
    return 0;
}
