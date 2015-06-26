//
//  LibThing.h
//  CppTestArenaLib
//
//  Created by Brandon Stansbury on 6/21/15.
//  Copyright (c) 2015 Brandon Stansbury. All rights reserved.
//

#ifndef CppTestArenaLib_LibThing_hpp
#define CppTestArenaLib_LibThing_hpp

namespace cpptestarena {
    
    class LibThing {
    public:
        explicit LibThing(int value)
        :v{value}
        {}
        
        void printStuff() const;
        
    private:
        int v;
    };
}

#endif
