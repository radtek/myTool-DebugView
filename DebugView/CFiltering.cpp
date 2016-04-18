#include "stdafx.h"
#include "CFiltering.h"
#include "CFilterDLG.h"


CFilter::CFilter()
{

}


CFilter::~CFilter()
{

}
  
bool CFilter::isFilter(BYTE* buffer, int buffLength, int status)
{ 
    filterTab::iterator tit = m_filterTab.begin();
    for (tit; tit != m_filterTab.end(); tit++)
    {  
        filterCol* data = tit->second;

        filterCol::iterator it = data->begin();
        for (it; it != data->end(); it++)
        {
            if ((*it)->m_col <= buffLength)
            {
                // 等于1 符合则过滤
                if (status == 1)
                {
                    if (buffer[(*it)->m_col] == (*it)->m_data)
                    {
                        return false;
                    }
                }
                else
                {
                    //等于0不符合则过滤
                    if (buffer[(*it)->m_col] == (*it)->m_data)
                    {
                        return true;
                    }
                } 
            } 
            else
            {
                return false;
            }
        } 
    }

    return true;
}

void CFilter::showFilterDlg()
{
    CFilterDLG dlg;
    dlg.setFilter(&m_filterTab);
    dlg.DoModal();
}