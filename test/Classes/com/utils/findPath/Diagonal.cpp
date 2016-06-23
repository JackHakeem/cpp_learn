//
//  Diagonal.cpp
//  HLQS
//
//  Created by edward liu on 12-2-24.
//  Copyright (c) 2012 4399. All rights reserved.
//


#include "Diagonal.h"
Diagonal::Diagonal()
{
}

int Diagonal::each(point start_point, point end_point, vector<point> &_value)
{
    int w = 0;
    int h = 0;
    
    int _ox = 0;
    int _oy = 0;
    //var __value:Array = [];
    float _r = 0.0f;
    float _n1 = 0.0f;
    float _n2 = 0.0f;
    bool _b1 = false;
    bool _b2 = false;
    int _m = 0;
    int _n = 0;
    bool _d = false;
    if((start_point.x < end_point.x && start_point.y < end_point.y)
       || (start_point.x > end_point.x && start_point.y > end_point.y))
        _d = true;
    
    //var __d:Boolean = (start_point.x<end_point.x)==(start_point.y<end_point.y);

    if (start_point.x<end_point.x)
    {
        _ox = start_point.x;
        _oy = start_point.y;
        w = end_point.x - _ox;
        h = end_point.y - _oy;
        if(h < 0 )
            h = h * (-1);
    } 
    else
    {
        _ox = end_point.x;
        _oy = end_point.y;
        w = start_point.x - _ox;
        h = start_point.y - _oy;
        if(h < 0)
            h = h * (-1);
    }
    
    if (w==h)
    {
        for (_m=0; _m<=w; _m++)
        {
            point p;
            if(_d)
            {
                p.x = _ox + _m;
                p.y = _oy + _m;
            }
            else
            {
                p.x = _ox + _m;
                p.y = _oy - _m;
            }
            _value.push_back(p);
            
            if(_m>0)
            {
                p.x = _ox + _m - 1;
                p.y = _oy + _m;
            }
            else
            {
                p.x = _ox + _m - 1;
                p.y = _oy - _m;
            }
            
            _value.push_back(p);
            
            if(_m<w)
            {
                p.x = _ox + _m + 1;
                p.y = _oy + _m;
            }
            else
            {
                p.x = _ox + _m + 1;
                p.y = _oy - _m;
            }
            
            _value.push_back(p);
            
            
            //__d ? __value.push(new Point(__ox+__m, __oy+__m)):__value.push(new Point(__ox+__m, __oy-__m));
            //if (__m>0) {
            //    __d ? __value.push(new Point(__ox+__m-1, __oy+__m)):__value.push(new Point(__ox+__m-1, __oy-__m));
            //}
            //if (__m<w) {
            //    __d ? __value.push(new Point(__ox+__m+1, __oy+__m)):__value.push(new Point(__ox+__m+1, __oy-__m));
            //}

        }
    }
    else if (w>h)
    {
        if(w != 0)
            _r=h/w;
        else
            _r = 0;
        
        point p;
        p.x = _ox;
        p.y = _oy;
        _value.push_back(p);
        
        for (_m=1; _m<=w; _m++) {
            _n1 = (int)(((float)_m - 0.5f) * (float)_r);
            _n2 = (int)(((float)_m + 0.5f) * (float)_r);
            _b1 = ((float)_n1 > (float)_n - 0.5f && (float)_n1 < (float)_n + 0.5f);
            _b2 = ((float)_n2 > (float)_n - 0.5f && (float)_n2 < (float)_n + 0.5f);
            if (_b1 || _b2)
            {
                if(_d)
                {
                    p.x = _ox + _m;
                    p.y = _oy + _n;
                }
                else
                {
                    p.x = _ox + _m;
                    p.y = _oy - _n;
                }
                
                _value.push_back(p);
                
                
                //__d ? __value.push(new Point(__ox+__m, __oy+__n)):__value.push(new Point(__ox+__m, __oy-__n));

                if (!_b2) 
                {
                    _n++;
                    if(_d)
                    {
                        p.x = _ox + _m;
                        p.y = _oy + _n;
                    }
                    else
                    {
                        p.x = _ox + _m;
                        p.y = _oy - _n;
                    }
                    
                    _value.push_back(p);
                    //__d ? __value.push(new Point(__ox+__m, __oy+__n)):__value.push(new Point(__ox+__m, __oy-__n));

                }
            }
        }
    } 
    else if (w<h) 
    {
        if(h != 0)
            _r = w/h;
        else
            _r = 0;
        
        point p;
        p.x = _ox;
        p.y = _oy;
        
        _value.push_back(p);
        //__value.push(new Point(__ox, __oy));

        for (_m=1; _m<=h; _m++) 
        {
            _n1 = (int)(((float)_m- 0.5f) * (float)_r);
            _n2 = (int)(((float)_m+ 0.5f) * (float)_r);
            _b1 = (float)_n1 > (float)_n - 0.5f && (float)_n1 < (float)_n+ 0.5f;
            _b2 = (float)_n2 > (float)_n - 0.5f && (float)_n2 < (float)_n+ 0.5f;
            if (_b1 || _b2)
            {
                if(_d)
                {
                    p.x = _ox + _n;
                    p.y = _oy + _m;
                }
                else
                {
                    p.x = _ox + _n;
                    p.y = _oy - _m;
                }
                _value.push_back(p);
                
                //__d ? __value.push(new Point(__ox+__n, __oy+__m)):__value.push(new Point(__ox+__n, __oy-__m));

                if (!_b2)
                {
                    _n++;
                    if(_d)
                    {
                        p.x = _ox+_n;
                        p.y = _oy+_m;
                    }
                    else
                    {
                        p.x = _ox+_n;
                        p.y = _oy-_m;
                    }
                    //__d ? __value.push(new Point(__ox+__n, __oy+__m)):__value.push(new Point(__ox+__n, __oy-__m));

                }
            }
        }
    }
    
    return 0;
}