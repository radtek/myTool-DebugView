// CInjectionDLG.cpp : 实现文件
//

#include "stdafx.h"
#include "DebugView.h"
#include "CInjectionDLG.h"
#include "afxdialogex.h"
#include "CInjection.h"

 
// CInjectionDLG 对话框

IMPLEMENT_DYNAMIC(CInjectionDLG, CDialogEx)

CInjectionDLG::CInjectionDLG(CWnd* pParent /*=NULL*/)
	: CDialogEx(CInjectionDLG::IDD, pParent)
{
    m_injectionID = -1;
}

CInjectionDLG::~CInjectionDLG()
{
}

void CInjectionDLG::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_list1);
    DDX_Control(pDX, IDC_LIST2, m_list2);
}


BEGIN_MESSAGE_MAP(CInjectionDLG, CDialogEx)
    ON_BN_CLICKED(IDOK, &CInjectionDLG::OnBnClickedOk)
    ON_BN_CLICKED(IDC_BUTTON1, &CInjectionDLG::OnBnClickedButton1)
    ON_NOTIFY(NM_CLICK, IDC_LIST1, &CInjectionDLG::OnNMClickList1)
    ON_NOTIFY(NM_CLICK, IDC_LIST2, &CInjectionDLG::OnNMClickList2)
    ON_BN_CLICKED(IDC_BUTTON2, &CInjectionDLG::OnBnClickedButton2)
END_MESSAGE_MAP()


// CInjectionDLG 消息处理程序


BOOL CInjectionDLG::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    initList();

    OnBnClickedButton1();
     
    return TRUE;   
}

void CInjectionDLG::initList()
{
    m_list1.SetExtendedStyle(
        m_list1.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
     
    int i = 0;
    m_list1.InsertColumn(i++, L"进程ID", LVCFMT_LEFT, 80);
    m_list1.InsertColumn(i++, L"进程名称", LVCFMT_LEFT, 80);
    m_list1.InsertColumn(i++, L"窗口名称", LVCFMT_LEFT, 80);
    m_list1.InsertColumn(i++, L"路径", LVCFMT_LEFT, 80);
     

    m_list2.SetExtendedStyle(
        m_list2.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

    i = 0;
    m_list2.InsertColumn(i++, L"模块路径ID", LVCFMT_LEFT, 300);
    m_list2.InsertColumn(i++, L"模块基址", LVCFMT_LEFT, 80);
    m_list2.InsertColumn(i++, L"模块大小", LVCFMT_LEFT, 80);
}

void CInjectionDLG::OnBnClickedOk()
{
    if (m_injectionID == -1)
    {
        MessageBox(L"请选择需要注入的进程");
        return;
    }

    static TCHAR BASED_CODE szFilter[] = _T("DLL Files (*.dll)|*.dll|") 
        _T("*.dll; *.dll|All Files (*.*)|*.*||");
     
    CFileDialog FileDlg(TRUE, L"", L"", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_ALLOWMULTISELECT, szFilter); 
    if (FileDlg.DoModal() == IDOK)
    {
        m_dll = FileDlg.GetPathName();
        
        CInjection inject;
        inject.injectionDLL(m_injectionID, (LPSTR)(LPCSTR)m_dll); 
    }

    m_injectionID = -1;
    CDialogEx::OnOK();
} 
 

void CInjectionDLG::showProcess()
{
    int i = 0;
    processInfo::const_iterator it = m_process->cbegin();
    for (it; it != m_process->cend(); it++, i++)
    {
        CString str;
        str.Format(L"%08X(%d)", (*it).second->m_pid, (*it).second->m_pid);
        m_list1.InsertItem(i, str);

        m_list1.SetItemText(i, 1, (*it).second->m_Name);

        m_list1.SetItemText(i, 2, (*it).second->m_WindowName);

        m_list1.SetItemText(i, 3, (*it).second->m_path);
    }

    int nCount = m_list1.GetHeaderCtrl()->GetItemCount();
    for (int i = 0; i < nCount; i++)
    {
        m_list1.SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER);
    }
}

void CInjectionDLG::OnBnClickedButton1()
{
    m_list1.DeleteAllItems();

    m_process = m_pi.getProcessInfo();
    if (m_process != nullptr)
    {
        showProcess();
    }
}


void CInjectionDLG::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

    int mark = m_list1.GetSelectionMark();
    if (mark == -1)
    {
        return;
    }

    processInfo::const_iterator it = m_process->find(mark);
    if (it == m_process->cend())
    {
        return;
    }

    m_injectionID = (*it).second->m_pid;
     
    showMoudle(); 

    m_list1.SetSelectionMark(-1);

    *pResult = 0;
}


void CInjectionDLG::showMoudle()
{ 
    m_moudle = m_pi.getModuleInfo(m_injectionID);
    if (m_moudle == nullptr)
    {
        return;
    }

    m_list2.DeleteAllItems();

    int i = 0;
    moduleInfo::const_iterator it = m_moudle->cbegin();
    for (it; it != m_moudle->cend(); it++, i++)
    { 
        m_list2.InsertItem(i, (*it).second->m_path);

        CString str;
        str.Format(L"%08X", (*it).second->m_base);
        m_list2.SetItemText(i, 1, str);

        str.Format(L"%08X(%d)", (*it).second->m_size, (*it).second->m_size);
        m_list2.SetItemText(i, 2, str);    
    } 

    int nCount = m_list2.GetHeaderCtrl()->GetItemCount();
    for (int i = 1; i < nCount; i++)
    {
        m_list2.SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER);
    }
}

void CInjectionDLG::OnNMClickList2(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
     
    int mark = m_list2.GetSelectionMark();
    if (mark == -1)
    {
        return;
    }

    CString base = m_list2.GetItemText(mark, 1);
    
    m_removeBase = wcstol((LPTSTR)(LPCTSTR)base, nullptr, 16);

    *pResult = 0;
}


void CInjectionDLG::OnBnClickedButton2()
{
    if (m_removeBase < 0)
    {
        return;
    }

    CInjection inject;
    inject.removeDLL(m_injectionID, m_removeBase);
}
