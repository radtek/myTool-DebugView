// iiii.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>

int main(int argc, char* argv[])
{
    BYTE bbbbb[0x31] = {
    0x06, 0xE0, 0x02, 0x51, 0x20, 0x10, 0x00, 0x00, 0x00, 0x04, 0x63, 0x00, 0x00, 0x00, 0xF7, 
    0x01, 0x01, 0xFF, 0xFF, 0x00, 0x1B, 0x00, 0xFF, 0x0F, 0x00, 0x05, 0x02, 0x0};


    HWND m_hwnd = ::FindWindow(NULL, "packView"); 
    
    char sz[] = "222222222";
    
    if (m_hwnd != NULL)
    {
        COPYDATASTRUCT data = { 0 };
        data.lpData = (LPVOID)bbbbb;
        data.cbData = 31;
        data.dwData = 2;
        ::SendMessage(m_hwnd, WM_COPYDATA, NULL, (LPARAM)&data);
    } 

	return 0;
}

