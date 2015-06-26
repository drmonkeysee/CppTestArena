//
//  LibThing.cpp
//  CppTestArenaLib
//
//  Created by Brandon Stansbury on 6/21/15.
//  Copyright (c) 2015 Brandon Stansbury. All rights reserved.
//

#include <iostream>
#include "LibThing.hpp"

void cpptestarena::LibThing::printStuff() const
{
    std::cout << "LibThing contains " << this->v << std::endl;
}
