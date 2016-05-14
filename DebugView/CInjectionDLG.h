#pragma once
#include "afxcmn.h"
#include "CProcessInfo.h"


// CInjectionDLG 对话框

class CInjectionDLG : public CDialogEx
{
	DECLARE_DYNAMIC(CInjectionDLG)

public:
	CInjectionDLG(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CInjectionDLG();

// 对话框数据
    enum { IDD = IDD_DIALOG1 };
    CListCtrl m_list1;
    CListCtrl m_list2;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

    virtual BOOL OnInitDialog();
     
    //注入
    afx_msg void OnBnClickedOk();
	 
    afx_msg void OnBnClickedButton1();

    afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
     
    afx_msg void OnNMClickList2(NMHDR *pNMHDR, LRESULT *pResult);

    //卸载
    afx_msg void OnBnClickedButton2();
    DECLARE_MESSAGE_MAP()

    void initList(); 
    
    void showProcess(); 

    void showMoudle();

private: 
    CProcessInfo m_pi;

    const processInfo* m_process;
    
    const moduleInfo* m_moudle;

    DWORD m_injectionID;

    CStringA m_dll;  

    DWORD m_removeBase;
};
