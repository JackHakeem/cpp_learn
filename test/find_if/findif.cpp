#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
struct Point
{
    int x;
    int y;
};
struct PointFindByCoord : public std::binary_function<Point, Point, bool>
{
    bool operator () (const Point &obj1, const Point &obj2) const
    {
        return obj1.x == obj2.x && obj1.y == obj2.y;
    }
};



struct Dummy{
    std::string _id;
    long long  mid;
    long long  fid;
    long long  time;
};



struct DummyFindByFid : public std::binary_function<Dummy, Dummy, bool>
{
    bool operator () (const Dummy &obj1, const Dummy &obj2) const
    {
        return obj1.fid == obj2.fid;
    }
};


int main()
{
    std::vector<Point> v;
    for (int i = 0; i < 5; ++i)
    {
        for (int j = 0; j < 5; ++j)
        {
            Point pt;
            pt.x = i;
            pt.y = j;
            v.push_back(pt);
        }
    }
    Point needFind;
    needFind.x = 4;
    needFind.y = 3;
    std::vector<Point>::iterator iter=std::find_if(v.begin(),v.end(),std::bind2nd(PointFindByCoord(), needFind));
    if (iter == v.end())
    {
        // 未找到  
    }
    else
        std::cout << "the index of value Point(" << (*iter).x << ", " << (*iter).y
            << ") is " << std::distance(v.begin(), iter) << std::endl;
    
    std::vector<Dummy> vv;
    for (int i = 0; i < 10; ++i)
    {
        Dummy d;
        d._id = "1"; d.mid=i; d.fid=6; d.time=0;
        vv.push_back(d);
    }
    
    Dummy needDummy; needDummy._id=""; needDummy.mid=0; needDummy.fid=6;needDummy.time=0;

    std::vector<Dummy>::iterator it=std::find_if(vv.begin(), vv.end(), std::bind2nd(DummyFindByFid(), needDummy));


    if (it == vv.end()) {
        std::cout << "find no " << std::endl;
    }
    else {
        std::cout << "find index is " << std::distance(vv.begin(), it) << std::endl;
    }





    return 0;
}
