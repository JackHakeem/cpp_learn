
#include "FindPath8.h"
#include "Diagonal.h"

//Copy constructor
FindPath8::FindPath8()
{
	init();
}

void FindPath8::init()
{
	for(int i = 0; i < MAP_MAX_H; ++i)
		for(int j = 0; j < MAP_MAX_W; ++j)
			_map[i][j] = NULL;

	_startPoint = NULL;
	_endPoint = NULL;
}

FindPath8::FindPath8(const FindPath8& RightSides)
{
	init();

	for(int i = 0; i < MAP_MAX_H; ++i)
	{
		for(int j = 0; j < MAP_MAX_W; ++j)
		{
			if(RightSides._map[i][j] == NULL)
			{
				_map[i][j] = NULL;
				continue;
			}
			_sMap *map = new _sMap;
			_sMap *map_right = RightSides._map[i][j];
			map->_x = map_right->_x;
            map->_y = map_right->_y;
            map->_value = map_right->_value;
			map->_block = map_right->_block;
			map->_open =  map_right->_open;
			map->_value_g = map_right->_value_g;
			map->_value_h = map_right->_value_h;
			map->_value_f = map_right->_value_f;
			if(map_right->_nodeparent)
				map->_nodeparent = map_right->_nodeparent;
			else
				map->_nodeparent = NULL;
			
			_map[i][j] = map;
		}
	}
	_startPoint = 0;
    _endPoint = 0;

	*this = RightSides;
}

FindPath8::FindPath8(char** map, uint32_t h, uint32_t w)
{
    _w = w;
    _h = h;
    int value;
    for (int y = 0; y< MAP_MAX_H; y++)
    {
        for (int x = 0; x < MAP_MAX_W; x++)
        {
            if(x >= _w || y >= _h)
            {
                _map[y][x] = NULL;
                continue;
            }
            

            int vl = *((char*)map + y * _w + x);
            
            if(vl == 0 || vl == 2)
            {
                value = 0;
            }
            else
            {
                value=1;
            }
            
            _sMap *map = new _sMap;
            map->_x = x;
            map->_y = y;
            map->_value = value;
            map->_block = false;
            map->_open = false;
            map->_value_g = 0;
            map->_value_h = 0;
            map->_value_f = 0;
            map->_nodeparent = NULL;
            _map[y][x] = map;
        }
    }

	_startPoint = 0;
    _endPoint = 0;
    
}

FindPath8& FindPath8::operator = (const FindPath8& RightSides)
{
	for(int i = 0; i < MAP_MAX_H; ++i)
	{
		for(int j = 0; j < MAP_MAX_W; ++j)
		{
			CC_SAFE_DELETE( _map[i][j] );//jae change
			if(RightSides._map[i][j] == NULL)
			{
				_map[i][j] = NULL;
				continue;
			}
			_sMap *map = new _sMap;
			_sMap *map_right = RightSides._map[i][j];
			map->_x = map_right->_x;
            map->_y = map_right->_y;
            map->_value = map_right->_value;
			map->_block = map_right->_block;
			map->_open =  map_right->_open;
			map->_value_g = map_right->_value_g;
			map->_value_h = map_right->_value_h;
			map->_value_f = map_right->_value_f;
			if(map_right->_nodeparent)
				map->_nodeparent = map_right->_nodeparent;
			else
				map->_nodeparent = NULL;
			
			_map[i][j] = map;
		}
	}

	_w = RightSides._w;
    _h = RightSides._h;
    //vector<_sMap*> _open;

	if(RightSides._startPoint)
	{
		//CC_SAFE_DELETE( _startPoint );//jae change
		_startPoint = _map[RightSides._startPoint->_x][RightSides._startPoint->_y];
		//_startPoint = new _sMap;

		//_startPoint->_x = RightSides._startPoint->_x;
		//_startPoint->_y = RightSides._startPoint->_y;
		//_startPoint->_value = RightSides._startPoint->_value;
		//_startPoint->_block = RightSides._startPoint->_block;
		//_startPoint->_open =  RightSides._startPoint->_open;
		//_startPoint->_value_g = RightSides._startPoint->_value_g;
		//_startPoint->_value_h = RightSides._startPoint->_value_h;
		//_startPoint->_value_f = RightSides._startPoint->_value_f;
		//if(RightSides._startPoint->_nodeparent)
		//	_startPoint->_nodeparent = RightSides._startPoint->_nodeparent;
		//else
		//	_startPoint->_nodeparent = NULL;

	}
	else
		_startPoint = NULL;

	if(RightSides._endPoint)
	{
		//CC_SAFE_DELETE( _endPoint );//jae change
		_endPoint = _map[RightSides._endPoint->_x][RightSides._endPoint->_y];
		//_endPoint = new _sMap;

		//_endPoint->_x = RightSides._endPoint->_x;
		//_endPoint->_y = RightSides._endPoint->_y;
		//_endPoint->_value = RightSides._endPoint->_value;
		//_endPoint->_block = RightSides._endPoint->_block;
		//_endPoint->_open =  RightSides._endPoint->_open;
		//_endPoint->_value_g = RightSides._endPoint->_value_g;
		//_endPoint->_value_h = RightSides._endPoint->_value_h;
		//_endPoint->_value_f = RightSides._endPoint->_value_f;
		//if(RightSides._endPoint->_nodeparent)
		//	_endPoint->_nodeparent = RightSides._endPoint->_nodeparent;
		//else
		//	_endPoint->_nodeparent = NULL;

	}
	else
		_endPoint = NULL;

	_path = RightSides._path;

	return *this;
}

FindPath8::~FindPath8()
{
	for(int i = 0; i < MAP_MAX_H; ++i)
	{
		for(int j = 0; j < MAP_MAX_W; ++j)
		{
			CC_SAFE_DELETE( _map[i][j] );
		}
	}
	_startPoint = 0;
	_endPoint = 0;
}

vector<point> FindPath8::path()
{
    return _path;
}

int FindPath8::find(point &start, point &end, vector<point> &path)
{
    if(start.x < 0.f || start.x >= MAP_MAX_W
		|| start.y < 0.f || start.y >= MAP_MAX_H
		|| end.x < 0.f || end.x >= MAP_MAX_W
		|| end.y < 0.f || end.y >= MAP_MAX_H)
		return -1;

    _path.clear();
    _startPoint = _map[start.y][start.x];
    _endPoint = _map[end.y][end.x];

    if(_startPoint == NULL|| _endPoint == NULL || _endPoint->_value == 1)
        return -1;
    
    if(_endPoint->_x==_startPoint->_x &&_endPoint->_y == _startPoint->_y)
        return -1;
    
    bool _getEnd = false;
    initBlock();
    
    _sMap* _thisNode = _startPoint;
    while (!_getEnd) {
        _thisNode->_block = true;

        vector<_sMap*> _checkList;

        if (_thisNode->_y>0) {
            _checkList.push_back(_map[(_thisNode->_y-1)][_thisNode->_x]);
        }
        if (_thisNode->_x>0) {
            _checkList.push_back(_map[_thisNode->_y][(_thisNode->_x-1)]);
        }
        if (_thisNode->_x<_w-1) {
            _checkList.push_back(_map[_thisNode->_y][(_thisNode->_x+1)]);
        }
        if (_thisNode->_y<_h-1) {
            _checkList.push_back(_map[(_thisNode->_y+1)][_thisNode->_x]);
        }
        
      

        if (_thisNode->_y>0 && _thisNode->_x>0) {
            _checkList.push_back(_map[(_thisNode->_y-1)][(_thisNode->_x-1)]);
        }
        if (_thisNode->_y<_h-1 && _thisNode->_x>0) {
            _checkList.push_back(_map[(_thisNode->_y+1)][(_thisNode->_x-1)]);
        }
        if (_thisNode->_y>0 && _thisNode->_x<_w-1) {
            _checkList.push_back(_map[(_thisNode->_y-1)][(_thisNode->_x+1)]);
        }
        if (_thisNode->_y<_h-1 && _thisNode->_x<_w-1) {
            _checkList.push_back(_map[(_thisNode->_y+1)][(_thisNode->_x+1)]);
        }
     

        for(int i = 0; i < _checkList.size(); ++i)
        {

            _sMap* _neighboringNode = _checkList[i];

            if (_neighboringNode == _endPoint
                && ((_neighboringNode->_x - _thisNode->_x) != 0)
                && abs((_neighboringNode->_y - _thisNode->_y) / (_neighboringNode->_x - _thisNode->_x))!= 1)
            {
                _neighboringNode->_nodeparent = _thisNode;
                _getEnd = true;
                break;
            }

            if (_neighboringNode->_value == 0) {
                count(_neighboringNode, _thisNode);

            }
        }
        if (!_getEnd) {

            if (_open.size()>0) {

                int _f = 100000;
                int cnt = 0;
                vector<_sMap*>::iterator iter;
                vector<_sMap*>::iterator del;
                for(iter = _open.begin();
                    iter != _open.end(); ++iter)
                {
                    if(_f > (*iter)->_value_f)
                    {
                        _f = (*iter)->_value_f;
                        _thisNode = (*iter);
                        del = iter;
                        cnt ++;
                    }
                }
                
                if(cnt > 0)
                    _open.erase(del);
            }
            else
            {

                return -1;
            }
        }
    }
    drawPath();
    path.clear();
    path = _path;
    return 0;
}

int FindPath8::optimizePath(vector<point> &path)
{
	optimizeLast4Point(_path);

    int _len = _path.size();	

    if(_len == 0)
        return -1;

	if (optimizeLinePoint(path) == 0)
	{
		return 0;
	}

	if (optimizeSlashPoint(path) == 0)
	{
		return 0;
	}

    vector<point> diagonal;
    
    int _dLen = 0;
    bool _cross = true;
    point _currentNode = _path[0];
    path.push_back(_path[0]);
    int n = 0;
    for (int i = 1; i < _len; ++i)
    {
        n++;
        Diagonal::each(_currentNode, _path[i], diagonal);
        _dLen = diagonal.size();
        _cross = true;
        for (int j = 0; j < _dLen; j++) 
        {
            if (_map[diagonal[j].y][diagonal[j].x]
                && _map[diagonal[j].y][diagonal[j].x]->_value == 1) {
                _cross = false;
                break;
            }
        }
        if(n>1)
        {
            _cross = false;
        }
        if (!_cross) {
            if (i>1) {
                _currentNode = _path[(i-1)];
                path.push_back(_path[(i-1)]);
                n=0;
            }
        }
    }
    path.push_back(_path[(_len-1)]);
    return 0;
}

void FindPath8::initBlock()
{
    for (int y = 0; y < _h; y++) 
    {
        for (int x = 0; x < _w; x++) 
        {
            _map[y][x]->_open = false;
            _map[y][x]->_block = false;
            _map[y][x]->_value_g = 0;
            _map[y][x]->_value_h = 0;
            _map[y][x]->_value_f = 0;
            _map[y][x]->_nodeparent = NULL;
        }
    }
    _open.clear();
}

void FindPath8::count(_sMap* neighboringNode, _sMap* centerNode)
{
    if(neighboringNode == NULL && centerNode == NULL)
        return;

    if (!neighboringNode->_block) {

        float _g = centerNode->_value_g+10;
        if(abs(neighboringNode->_x - centerNode->_x)==1 && abs(neighboringNode->_y-centerNode->_y)==1)
        {
            _g=centerNode->_value_g+14;
        }
        else
        {
            _g = centerNode->_value_g+10 ;
        }

        if(neighboringNode->_x > centerNode->_x && neighboringNode->_y < centerNode->_y)
        {
            //trace("("+neighboringNode.x+","+neighboringNode.y+")"+"	"+"("+centerNode.x+","+centerNode.y+")");

            if(_map[neighboringNode->_y][neighboringNode->_x - 1]->_value == 1 && _map[neighboringNode->_y + 1][neighboringNode->_x]->_value == 1)
            {
                _g += 10000;
            }
        }
        else if(neighboringNode->_x > centerNode->_x && neighboringNode->_y > centerNode->_y)
        {
            //trace("("+neighboringNode.x+","+neighboringNode.y+")"+"	"+"("+centerNode.x+","+centerNode.y+")");

            if(_map[neighboringNode->_y][neighboringNode->_x - 1]->_value == 1 && _map[neighboringNode->_y - 1][neighboringNode->_x]->_value == 1)
            {
                _g += 10000;
            }
        }
        else if(neighboringNode->_x < centerNode->_x && neighboringNode->_y > centerNode->_y)
        {
            //trace("("+neighboringNode.x+","+neighboringNode.y+")"+"	"+"("+centerNode.x+","+centerNode.y+")");

            if(_map[neighboringNode->_y][neighboringNode->_x + 1]->_value == 1 && _map[neighboringNode->_y - 1][neighboringNode->_x]->_value == 1)
            {
                _g += 10000;
            }
        }
        else if(neighboringNode->_x < centerNode->_x && neighboringNode->_y < centerNode->_y)
        {
            //trace("("+neighboringNode.x+","+neighboringNode.y+")"+"	"+"("+centerNode.x+","+centerNode.y+")");

            if(_map[neighboringNode->_y + 1][neighboringNode->_x]->_value == 1 && _map[neighboringNode->_y][neighboringNode->_x + 1]->_value == 1)
            {
                _g += 10000;
            }
        }
        //added by lyy end
        if (neighboringNode->_open) {

            if (neighboringNode->_value_g>=_g) {

                neighboringNode->_value_g = _g;
                ghf(neighboringNode);
                neighboringNode->_nodeparent = centerNode;
            }
        } else 
        {

            addToOpen(neighboringNode);

            neighboringNode->_value_g = _g;
            ghf(neighboringNode);
            neighboringNode->_nodeparent = centerNode;
        }
    }
}

void FindPath8::drawPath()
{
    _sMap* _pathNode = _endPoint;

    vector<point>::iterator iter;
    while (_pathNode != _startPoint)
    {
        point p;
        p.x = _pathNode->_x;
        p.y = _pathNode->_y;
        iter = _path.begin();
        _path.insert(iter, p);
        _pathNode = _pathNode->_nodeparent;
    }
    point p;
    p.x = _pathNode->_x;
    p.y = _pathNode->_y;
    iter = _path.begin();
    _path.insert(iter, p);
}

void FindPath8::addToOpen(_sMap* newNode)
{
    newNode->_open = true;
    _open.push_back(newNode);
}

void FindPath8::ghf(_sMap* node)
{
    float _dx = abs(node->_x-_endPoint->_x);
    float _dy = abs(node->_y-_endPoint->_y);
    node->_value_h = 10 * (_dx + _dy);
    node->_value_f = node->_value_g+node->_value_h;
}

int FindPath8::optimizeLinePoint(std::vector<point> &path)
{
	// add by L.H. 20120704
	int _len = _path.size();
	if (_path[0].x == _path[_len-1].x)
	{
		int ix = _path[0].x;
		int iy = _path[0].y;
		if(_path[0].x == _path[_len-1].x)
		{
			while(iy != _path[_len-1].y)
			{
				if(_map[iy][ix]->_value == 1)
				{
					path.clear();
					break;
				}
				point _point;
				_point.x = ix;
				_point.y = iy;
				path.push_back(_point);
				if(_path[0].y < _path[_len-1].y)
					iy++;
				else
					iy--;
			}
			if (iy == _path[_len-1].y)
			{
				point _point;
				_point.x = _path[_len-1].x;
				_point.y = iy;
				path.push_back(_point);
				return 0;
			}	
		}
	}
	return -1;
}

int FindPath8::optimizeSlashPoint(std::vector<point> &path)
{
	// add by L.H. 20120704
	int _len = _path.size();
	if (((_path[0].x - _path[_len-1].x) == (_path[0].y - _path[_len-1].y)) 
		|| ((_path[0].x - _path[_len-1].x) == ((-1)*(_path[0].y - _path[_len-1].y))))
	{
		int ix = _path[0].x;
		int iy = _path[0].y;
		if(((_path[0].x - _path[_len-1].x) == (_path[0].y - _path[_len-1].y)) 
			|| ((_path[0].x - _path[_len-1].x) == ((-1)*(_path[0].y - _path[_len-1].y))))
		{
			while(iy != _path[_len-1].y)
			{
				if(_map[iy][ix]->_value == 1)
				{
					path.clear();
					break;
				}
				point _point;
				_point.x = ix;
				_point.y = iy;
				path.push_back(_point);
				if(_path[0].x < _path[_len-1].x)
					ix++;
				else
					ix--;
				if(_path[0].y < _path[_len-1].y)
					iy++;
				else
					iy--;
			}
			if (iy == _path[_len-1].y)
			{
				point _point;
				_point.x = _path[_len-1].x;
				_point.y = iy;
				path.push_back(_point);
				return 0;
			}			
		}
	}
	return -1;
}

void FindPath8::optimizeLast4Point(std::vector<point> &path)
{
	if (path.size() < 4)
	{
		return;
	}
	point point4	= path.back();
	path.pop_back();
	point point3  = path.back();
	path.pop_back();
	point point2  = path.back();
	path.pop_back();
	point point1  = path.back();
	
	if (((point4.x-point1.x) == (point4.y-point1.y)) 
		|| ((point4.x-point1.x) == ((-1)*(point4.y-point1.y))))
	{
		path.push_back(point4);
	}
	else
	{
		path.push_back(point2);
		if (((point4.x-point2.x) == (point4.y-point2.y)) 
			|| ((point4.x-point2.x) == ((-1)*(point4.y-point2.y))))
		{
			path.push_back(point4);
		}
		else
		{
			path.push_back(point3);
			path.push_back(point4);
		}
	}	
}