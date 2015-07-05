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

struct FooBar {
    int value;
};

void own_rvalue(FooBar&& f);

void own_sp(std::unique_ptr<FooBar> fp);

#endif
