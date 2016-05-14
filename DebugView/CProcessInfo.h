#pragma once

struct tagPrcoessInfo
{
    DWORD m_pid;
    CString m_Name;
    CString m_WindowName;
    CString m_path;
};

struct tagModuleInfo
{
    CString m_path;
    DWORD m_base;
    DWORD m_size;
};

#include <map>

typedef std::map<int, tagPrcoessInfo*> processInfo;
typedef std::map<int, tagModuleInfo*> moduleInfo;

class CProcessInfo
{
public:
    CProcessInfo();
    ~CProcessInfo();

    const processInfo* getProcessInfo();
    
    const moduleInfo* getModuleInfo(DWORD pid);
     

private: 
    static BOOL CALLBACK EnumWindowsName(HWND hwnd, LPARAM lParam); 

    void clearProcessInfo();
    
    void clearModuleInfo();

private:
    processInfo m_processInfo;
    moduleInfo m_moduleInfo;
};

