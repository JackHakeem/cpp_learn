//
//  Diagonal.h
//  HLQS
//
//  Created by edward liu on 12-2-24.
//  Copyright (c) 2012 4399. All rights reserved.
//

#ifndef HLQS_Diagonal_h
#define HLQS_Diagonal_h

#include <vector>
#include "BaseType.h"

typedef struct spoint
{
    uint32 x;
    uint32 y;
} point;

class Diagonal
{
public:
    Diagonal();
    static int each(point start_point, point end_point, vector<point> &_value);
    
private:
};

#endif