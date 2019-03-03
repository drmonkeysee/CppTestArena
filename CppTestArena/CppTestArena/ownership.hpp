//
//  ownership.hpp
//  CppTestArena
//
//  Created by Brandon Stansbury on 7/5/15.
//  Copyright (c) 2015 Brandon Stansbury. All rights reserved.
//

#ifndef CppTestArena_ownership_hpp
#define CppTestArena_ownership_hpp

#include <memory>
#include <iostream>

struct FooBar {
    int value;
};

class InitializationTest {
public:
    explicit InitializationTest(int a, int b, int c)
    : a(a), b(b), c(c) { std::cout << "Baz ctor called" << std::endl; }
    
    /*InitializationTest(std::initializer_list<int> list)
     {
     std::initializer_list<int>::size_type size = list.size();
     std::cout << "Baz list ctor called with size: " << size << std::endl;
     this->a = 1;
     this->b = 2;
     this->c = 3;
     }*/
    
    /*InitializationTest(const Baz& other)
     {
     this->a = other.a;
     this->b = other.b;
     this->c = other.c;
     std::cout << "Baz copy ctor called" << std::endl;
     }*/
private:
    int a, b, c;
};

void own_rvalue(FooBar&& f);

void own_sp(std::unique_ptr<FooBar> fp);

#endif
