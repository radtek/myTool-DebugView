#include "stdafx.h"
#include "CProcessInfo.h"
#include <windows.h>
#include <TLHELP32.H>
#include <Psapi.h>

CProcessInfo::CProcessInfo()
{
}


CProcessInfo::~CProcessInfo()
{
    clearProcessInfo();

    clearModuleInfo();
}


void CProcessInfo::clearProcessInfo()
{
    processInfo::iterator it = m_processInfo.begin();
    for (it; it != m_processInfo.end(); it++)
    {
        delete (*it).second;
    }

    m_processInfo.clear();
}

void CProcessInfo::clearModuleInfo()
{
    moduleInfo::iterator it = m_moduleInfo.begin();
    for (it; it != m_moduleInfo.end(); it++)
    {
        delete (*it).second;
    }

    m_moduleInfo.clear();
}


const processInfo* CProcessInfo::getProcessInfo()
{
    clearProcessInfo();

    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof(pe32);
     
    WCHAR path[MAX_PATH + 1] = { 0 };

    HANDLE hProcessSnap = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hProcessSnap == INVALID_HANDLE_VALUE)
    { 
        return nullptr;
    }

    int i = 0;
    BOOL bMore = ::Process32First(hProcessSnap, &pe32);
    while (bMore)
    { 
        tagPrcoessInfo* data = new tagPrcoessInfo;
        if (data == nullptr)
        { 
            break;
        }

        data->m_pid = pe32.th32ProcessID;
        data->m_Name = pe32.szExeFile;

        HANDLE handle = ::OpenProcess(PROCESS_ALL_ACCESS, false, pe32.th32ProcessID);
        if (handle != nullptr)
        { 
            ::GetModuleFileNameEx(handle, nullptr, path, MAX_PATH);
        } 

        ::EnumWindows(EnumWindowsName, (LPARAM)data);
        
        data->m_path = path;
        
        m_processInfo.insert(std::pair<int, tagPrcoessInfo*>(i++, data));

        bMore = ::Process32Next(hProcessSnap, &pe32);
    }

    ::CloseHandle(hProcessSnap);

    return &m_processInfo;
}

BOOL CProcessInfo::EnumWindowsName(HWND hwnd, LPARAM lParam)
{
    tagPrcoessInfo* data = (tagPrcoessInfo*)lParam;

    DWORD dwProcessId;
    ::GetWindowThreadProcessId(hwnd, &dwProcessId);
    if (data->m_pid == dwProcessId)
    { 
        while (::GetParent(hwnd) != NULL)
        {
            hwnd = ::GetParent(hwnd);
        }

        WCHAR txt[MAX_PATH + 1] = { 0 };
        ::GetWindowText(hwnd, txt, MAX_PATH);
        data->m_WindowName = txt;
        return FALSE;
    }

    return TRUE;
} 


const moduleInfo* CProcessInfo::getModuleInfo(DWORD pid)
{
    clearModuleInfo();

    MODULEENTRY32 m32;
    m32.dwSize = sizeof(m32);

    WCHAR path[MAX_PATH + 1] = { 0 };

    HANDLE hProcessSnap = ::CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid);
    if (hProcessSnap == INVALID_HANDLE_VALUE)
    { 
        return nullptr;
    }

    int i = 0;
    BOOL bMore = ::Module32First(hProcessSnap, &m32);
    while (bMore)
    {
        if (m32.th32ProcessID != pid) continue;

        tagModuleInfo* data = new tagModuleInfo;
        if (data == nullptr)
        { 
            break;
        }
         
        data->m_path = m32.szExePath;
        data->m_base = (DWORD)m32.modBaseAddr;
        data->m_size = m32.dwSize;

        m_moduleInfo.insert(std::pair<int, tagModuleInfo*>(i++, data));

        bMore = ::Module32Next(hProcessSnap, &m32);
    }

    ::CloseHandle(hProcessSnap);

    return &m_moduleInfo;
}