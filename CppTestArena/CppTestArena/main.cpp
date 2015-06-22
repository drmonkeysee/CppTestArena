//
//  main.cpp
//  CppTestArena
//
//  Created by Brandon Stansbury on 6/21/15.
//  Copyright (c) 2015 Brandon Stansbury. All rights reserved.
//

#include <iostream>
#include "LibThing.h"

int main(int argc, const char *argv[])
{
    // insert code here...
    std::cout << "Hello, World!\n";
    
    cpptestarena::LibThing thing{5};
    
    thing.printStuff();
    
    return 0;
}
