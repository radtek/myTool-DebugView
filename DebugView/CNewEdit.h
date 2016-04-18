#pragma once


// CNewEdit

class CNewEdit : public CEdit
{
	DECLARE_DYNAMIC(CNewEdit)

public:
	CNewEdit();
	virtual ~CNewEdit();

    void showByte(CString data);

    CString showString(CString data);

protected:
    afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnPopCopyall();
    afx_msg void OnPopCopyhex();
    afx_msg void OnPopCarray();
	DECLARE_MESSAGE_MAP()
    
    void Pasteboard(CString data);

    CString m_data;

    CString m_default;  
};


