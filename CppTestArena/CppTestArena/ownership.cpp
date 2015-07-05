//
//  ownership.cpp
//  CppTestArena
//
//  Created by Brandon Stansbury on 7/5/15.
//  Copyright (c) 2015 Brandon Stansbury. All rights reserved.
//

#include "ownership.hpp"

std::unique_ptr<FooBar> fromRValue;
std::unique_ptr<FooBar> fromPointer;

void own_rvalue(FooBar&& f)
{
    fromRValue = std::make_unique<FooBar>(f);
}

void own_sp(std::unique_ptr<FooBar> fp)
{
    fromPointer.swap(fp);
}