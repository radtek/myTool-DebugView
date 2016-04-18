#pragma once


// CMyStatic

class CMyStatic : public CStatic
{
	DECLARE_DYNAMIC(CMyStatic)

public:
	CMyStatic();
	virtual ~CMyStatic();

protected:
	DECLARE_MESSAGE_MAP() 
public:
    afx_msg void OnMouseMove(UINT nFlags, CPoint point); 
    afx_msg void OnMouseLeave();

    bool m_bTracking;
};


