#include "stdafx.h"
#include "CInjection.h"
#include <windows.h>


CInjection::CInjection()
{
}


CInjection::~CInjection()
{
}

void CInjection::injectionDLL(DWORD pid, char* dllPaht)
{
    LPVOID buff = nullptr;
    SIZE_T out = 0;
    HANDLE crt = 0;
    DWORD exitCode = 0;

    HANDLE handle = ::OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
    if (handle == nullptr)
    {
        ::MessageBox(nullptr, L"进程打开失败，无法注入!", nullptr, MB_OK);
        return;
    }

    buff = ::VirtualAllocEx(handle, nullptr, 0x42, MEM_COMMIT, PAGE_READWRITE);
    if (buff == nullptr)
    {
        ::MessageBox(nullptr, L"申请远程线程内存失败!", nullptr, MB_OK);
        goto _ret;
    }

    if (::WriteProcessMemory(handle, buff, (LPVOID)dllPaht, strlen(dllPaht) + 1, &out) == FALSE)
    {
        ::MessageBox(nullptr, L"写入远程线程内存失败!", nullptr, MB_OK);
        goto _ret;
    }

    HMODULE k32 = ::LoadLibrary(L"kernel32.dll");
    if (k32 == nullptr)
    {
        ::MessageBox(nullptr, L"加载kernel32失败!", nullptr, MB_OK);
        goto _ret;
    }

    crt = ::CreateRemoteThread(
        handle,
        nullptr,
        0,
        (LPTHREAD_START_ROUTINE)::GetProcAddress(k32, "LoadLibraryA"),
        buff,
        0,
        nullptr);
    if (crt == nullptr)
    {
        ::MessageBox(nullptr, L"创建远程线程内存失败!", nullptr, MB_OK);
        goto _ret;
    }

    ::MessageBox(nullptr, L"DLL注入成功!", nullptr, MB_OK);

    ::WaitForSingleObject(crt, INFINITE);

    ::GetExitCodeThread(crt, &exitCode);

    ::VirtualFreeEx(crt, buff, 0x0, MEM_RELEASE);

_ret:
    if (crt != nullptr)
    {
        ::CloseHandle(crt);
    }

    if (handle != nullptr)
    {
        ::CloseHandle(handle);
    }
}

void CInjection::removeDLL(DWORD pid, DWORD removeBase)
{      
    HANDLE crt = 0;
    DWORD exitCode = 0;

    HANDLE handle = ::OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
    if (handle == nullptr)
    {
        ::MessageBox(nullptr, L"进程打开失败，无法移除!", nullptr, MB_OK);
        return;
    }

    HMODULE k32 = ::LoadLibrary(L"kernel32.dll");
    if (k32 == nullptr)
    {
        ::MessageBox(nullptr, L"加载kernel32失败!", nullptr, MB_OK);
        goto _ret;
    }
     
    crt = ::CreateRemoteThread(
        handle,
        nullptr,
        0,
        (LPTHREAD_START_ROUTINE)::GetProcAddress(k32, "FreeLibrary"),
        (LPVOID)removeBase,
        0,
        nullptr);
    if (crt == nullptr)
    {
        ::MessageBox(nullptr, L"创建远程线程内存失败!", nullptr, MB_OK);
        goto _ret;
    }
     
    ::WaitForSingleObject(crt, INFINITE);

    ::GetExitCodeThread(crt, &exitCode);
    if ((BOOL)exitCode == FALSE)
    {
        ::MessageBox(nullptr, L"远程DLL释放失败!", nullptr, MB_OK);
    }
    else
    {
        ::MessageBox(nullptr, L"远程DLL释放成功!", nullptr, MB_OK);
    } 

_ret:
    if (crt != nullptr)
    {
        ::CloseHandle(crt);
    }

    if (handle != nullptr)
    {
        ::CloseHandle(handle);
    } 
}