// CNewEdit.cpp : 实现文件
//

#include "stdafx.h"
#include "DebugView.h"
#include "CNewEdit.h"


// CNewEdit

IMPLEMENT_DYNAMIC(CNewEdit, CEdit)

CNewEdit::CNewEdit()
{

}

CNewEdit::~CNewEdit()
{
}


BEGIN_MESSAGE_MAP(CNewEdit, CEdit)
    ON_WM_RBUTTONDOWN()
    ON_COMMAND(ID_POP_copyAll, &CNewEdit::OnPopCopyall)
    ON_COMMAND(ID_POP_copyHex, &CNewEdit::OnPopCopyhex)
    ON_COMMAND(ID_POP_CArray, &CNewEdit::OnPopCarray)
END_MESSAGE_MAP()



// CNewEdit 消息处理程序

void CNewEdit::OnRButtonDown(UINT nFlags, CPoint point)
{ 
    CMenu  menu;
    menu.LoadMenu(IDR_MENU2);
    CMenu *pMenu = menu.GetSubMenu(0);
    ClientToScreen(&point);
    CPoint cpoint;
    GetCursorPos(&cpoint);
    pMenu->TrackPopupMenu(TPM_LEFTALIGN, cpoint.x, cpoint.y, this); 
}
 
void CNewEdit::showByte(CString data)
{
    m_data = data;
    CString tmp;
    bool enter;

    int i = 0; 

    m_default.Format(L"  Offset: 00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F\r\n"
        L"-------------------------------------------------------------\r\n"
        L"%08X: ", i);

    int count = data.GetLength();
    for (int inedx = 0, rn = 0; inedx < count; inedx++, rn++)
    { 
        enter = true;
        m_default += data[inedx];
        if (tmp.IsEmpty() == false)
        {
            tmp += data[inedx];
        }
        else
        {
            tmp = data[inedx];
        }

        if (rn == 47)
        {
            rn = -1;
            i += 0x10;
              
            enter = false;
            tmp = showString(tmp);
             
            m_default += CString("      ") + tmp;
            
            tmp.Format(L"%08X: ", i); 
            m_default += CString(L"\r\n") + tmp; 
            tmp.Empty();
        }
    }

    if (enter == true)
    {
        if (tmp.GetLength() == 47)
        {
            tmp = showString(tmp);

            m_default += CString("       ") + tmp;
        } 
        else
        {
            CString str(L"  ");
            int n = 47 - tmp.GetLength();
            for (int i = 1; i < n; i++)
            { 
                str += L" ";
            }

            tmp = showString(tmp);
            m_default += str + CString("      ") + tmp;
        }

         
    }

    SetWindowText(m_default);
}

CString CNewEdit::showString(CString data)
{
    CString ret; 

    for (int i = 0; i < 47; i+=3)
    {
        int tmp = wcstol((LPTSTR)(LPCTSTR)data + i, nullptr, 16);
         
        WCHAR ch;
        switch (tmp)
        {
        case 0x0:
        case 0x1:
        case 0x2:
        case 0x3:
        case 0x4:
        case 0x5:
        case 0x6:
        case 0x7:
        case 0x8:
        case 0x9:
        case 0xA:
        case 0xB:
        case 0xC:
        case 0xD: 
            ch = L'.';
            break;
        default:
            ch = tmp;
            break;
        }
        
        if (i != 0)
        {
            ret += ch;
        }
        else
        {
            ret = ch;
        }
    }

    return ret;
}

void CNewEdit::Pasteboard(CString data)
{
    if (OpenClipboard())//打开剪切板  
    {
        EmptyClipboard();//清空剪切板,让当前窗口进程拥有剪切板  

        HANDLE hClip = GlobalAlloc(GMEM_MOVEABLE, data.GetLength() + 1);//分配内存对象返回地址(该函数是系统从全局堆中分配内存)  

        char *pBuf = (char*)GlobalLock(hClip);//锁定全局内存中指定的内存块，并返回一个地址值，令其指向内存块的起始处  

        CStringA str;
        str = data;

        strcpy_s(pBuf, strlen(str) + 1, str);//将Str对象中的数据Copy到内存空间中  

        GlobalUnlock(hClip);//解锁全局内存块  

        SetClipboardData(CF_TEXT, hClip);//设置剪贴板数据  

        CloseClipboard();//关闭  
    }
}

void CNewEdit::OnPopCopyall()
{
    Pasteboard(m_default);
}


void CNewEdit::OnPopCopyhex()
{ 
    CString data;
    int count = m_data.GetLength();
    for (int inedx = 0, rn = 0; inedx < count; inedx++, rn++)
    {
        data += m_data[inedx];

        if (rn == 47)
        {
            rn = -1; 
             
            data += CString(L"\r\n");
        }
    }

    Pasteboard(data);
}


void CNewEdit::OnPopCarray()
{
    CString data;

    data.Format(L"BYTE buffer[] = {");

    int count = m_data.GetLength();
    int up = 0;
    for (int inedx = 0, rn = 0; inedx < count; inedx += 3, rn += 3)
    {
        if (inedx != 0)
        {
            data += CString(L", 0x") + m_data[inedx] + m_data[inedx + 1];
        } 
        else
        { 
            data += CString(L"0x") + m_data[inedx] + m_data[inedx + 1];
        }
         
        if (rn >= 44)
        {
            rn = -1;

            data += CString(L"\r\n    ");
        }
    }

    data += L"};";

    Pasteboard(data);
}
