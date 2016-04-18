// CMyStatic.cpp : 实现文件
//

#include "stdafx.h" 
#include "CMyStatic.h"

#define WM_USER_MY WM_USER + 1
#define WM_USER_MY2 WM_USER + 2

// CMyStatic

IMPLEMENT_DYNAMIC(CMyStatic, CStatic)

CMyStatic::CMyStatic()
{
    m_bTracking = false;
}

CMyStatic::~CMyStatic()
{
}


BEGIN_MESSAGE_MAP(CMyStatic, CStatic)
    ON_WM_MOUSEMOVE()
    ON_WM_MOUSELEAVE()
    ON_WM_MOUSELEAVE()
END_MESSAGE_MAP()



// CMyStatic 消息处理程序


void CMyStatic::OnMouseMove(UINT nFlags, CPoint point)
{
    GetParent()->SendMessage(WM_USER_MY, 0, 0);

    if (!m_bTracking)
    {
        TRACKMOUSEEVENT tme;
        tme.cbSize = sizeof(TRACKMOUSEEVENT);
        tme.dwFlags = TME_LEAVE;//要触发的消息
        tme.hwndTrack = this->m_hWnd;
        tme.dwHoverTime = 10;// 若不设此参数，则无法触发mouseHover

        if (::_TrackMouseEvent(&tme)) //MOUSELEAVE|MOUSEHOVER消息由此函数触发
        {
            m_bTracking = true;
        }
    }

    CStatic::OnMouseMove(nFlags, point);
}


void CMyStatic::OnMouseLeave()
{
    GetParent()->SendMessage(WM_USER_MY2, 0, 0);
    
    m_bTracking = false; 
     
    CStatic::OnMouseLeave();
}
