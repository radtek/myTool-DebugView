#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "resource.h"

#include "FilterHead.h"

// CFilterDLG 对话框
  

class CFilterDLG : public CDialogEx
{
	DECLARE_DYNAMIC(CFilterDLG)

public:
	CFilterDLG(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CFilterDLG();

// 对话框数据
    enum { IDD = IDD_DLG };
    CListCtrl m_list;
    CEdit m_edit;

    void setFilter(filterTab* tab);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
     
    virtual BOOL OnInitDialog();
     
    //加新的过滤器
    afx_msg void OnBnClickedButton1();

    afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
     
    afx_msg void OnEnKillfocusEdit1();
     
    //退出
    afx_msg void OnBnClickedOk();

    //删除过滤器
    afx_msg void OnBnClickedButton2();

    //清空过滤器 
    afx_msg void OnBnClickedButton3();
	
    //导出设置
    afx_msg void OnBnClickedButton4();
    DECLARE_MESSAGE_MAP() 

    void initList(); 

    void initFilter();

    int getFilterCount();

    void setTabRow(int count);

    void setFilterField();

    void fillingField(int row, filterCol* data);

    void upFilter(int row, filterCol* data);

    bool isFilterData(filterCol* data, int col, BYTE ch);

    bool newFilterData(filterCol* data, int col, BYTE ch);

    //删除过滤器
    int clearListRow();

    void clearTabRow(int row);

    //导出过滤设置
    void exportFilter(CString path);
    
    void writeHead(CFile& file);

    void writeData(CFile& file);

    void writeSubData(CFile& file, int row, filterCol* data);

private:
    int m_Row;
    int m_Col;

    filterTab *m_Tab;   
};
