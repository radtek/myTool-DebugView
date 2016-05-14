
// DebugViewDlg.h : 头文件
//

#pragma once
#include "afxcmn.h" 
#include "afxwin.h"
#include "Data.h" 
#include "CNewEdit.h"
#include "CFiltering.h"

#define SEND_SERVER 1
#define RECV_SERVER 2
#define SEND_HARDWARE 3 
#define RECV_HARDWARE 4 

// CDebugViewDlg 对话框
class CDebugViewDlg : public CDialogEx
{
// 构造
public:
	CDebugViewDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
    enum { IDD = IDD_DEBUGVIEW_DIALOG };
    CListCtrl m_listShow;
    CTabCtrl m_tabCtrl;
    CNewEdit m_Edit;

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
    afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnBnClickedRadio1();
    afx_msg void OnBnClickedRadio2();
    afx_msg void OnBnClickedRadio3();
    afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
    
    //是否收包
    afx_msg void OnBnClickedCheck1();
    
    //清空列表
    afx_msg void OnBnClickedButton2();

    //刷新显示
    afx_msg void OnBnClickedButton4();

    //清除所有数据
    afx_msg void OnBnClickedButton6();
     
    //打开过滤器
    afx_msg void OnBnClickedButton3();
    
    //有关消息
    afx_msg void About();
	
    //注入DLL
    afx_msg void OnBnClickedButton1();
    DECLARE_MESSAGE_MAP()

    void initList();
     
    void initTabCtrl();

    void showData(tagBuffer* buff);

    bool filteringPack(COPYDATASTRUCT* pCopyDataStruct); 
      
    void showByte(tagBuffer* pBuff);
      
    void showByte(std::map<int, tagBuffer*>* pItem);

    void showEditByte(CString str);

    void clearList();

private:
    bool m_pack;

    int m_showComm;

    int m_filteringState; 

    CData m_data;   

    CFilter m_filter; 
};
