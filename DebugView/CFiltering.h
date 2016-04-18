#pragma once

#include <windows.h>

#include "FilterHead.h"

class CFilter
{
public:
    CFilter();
    ~CFilter();
     
    bool isFilter(BYTE* buffer, int buffLength, int status);

    void showFilterDlg();
      
private:
    filterTab m_filterTab; 
}; 