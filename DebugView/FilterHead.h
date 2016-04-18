#ifndef HEAD
#define HEAD

#include <map>
#include <list>

//列，过滤字符
typedef struct tagFilterData
{
    int m_col;
    BYTE m_data;
} filterData, *pfilterData;

//过滤列
typedef std::list<filterData*> filterCol;

typedef std::map<int, filterCol*> filterTab;

#endif