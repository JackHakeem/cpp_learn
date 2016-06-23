//
//  FindPath8.h
//  HLQS
//
//  Created by edward liu on 12-2-23.
//  Copyright (c) 2012 4399. All rights reserved.
//

#ifndef HLQS_FindPath8_h
#define HLQS_FindPath8_h

#include "cocos2d.h"
#include "utils/findPath/Diagonal.h"

#define MAP_MAX_W 200
#define MAP_MAX_H 200

typedef struct _SMAP
{
    int _x;
    int _y;
    int _value;
    bool _block;
    bool _open;
    int _value_g;
    int _value_h;
    int _value_f;
    struct _SMAP* _nodeparent;
    void reset()
    {
        _x = 0;
        _y = 0;
        _value = 0;
        _block = 0;
        _open = 0;
        _value_g = 0;
        _value_h = 0;
        _value_f = 0;
        _nodeparent = NULL;
    }
    _SMAP()
    {
        reset();
    }
} _sMap;

class FindPath8
{
private:
    
    _sMap* _map[MAP_MAX_H][MAP_MAX_W];
    uint32 _w;
    uint32 _h;
    vector<_sMap*> _open;
    _sMap* _startPoint;
    _sMap* _endPoint;
    
    //char _path[MAP_MAX_W][MAP_MAX_H];

    std::vector<point> _path;
    
public:
    FindPath8(char** map, uint32 w, uint32 h);
	FindPath8(const FindPath8&);
	FindPath8();

    virtual ~FindPath8();

	FindPath8& operator = (const FindPath8&);

    vector<point> path();
    int find(point &star, point &end, vector<point> &path);
    int optimizePath(vector<point> &path);
	void init();
    
private:
    void initBlock();
    void count(_sMap* neighboringNode, _sMap* centerNode);
    void drawPath();
    void addToOpen(_sMap* newNode);
    void ghf(_sMap* node);
    uint32 getMin();
    void find_ex(point startPoint, point endPoint);
	int optimizeLinePoint(std::vector<point> &path);
	int optimizeSlashPoint(std::vector<point> &path);
	void optimizeLast4Point(std::vector<point> &path);
};

#endif
