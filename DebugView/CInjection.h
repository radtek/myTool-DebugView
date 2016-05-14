#pragma once
class CInjection
{
public:
    CInjection();
    ~CInjection();

    void injectionDLL(DWORD pid, char* dllPaht);

    void removeDLL(DWORD pid, DWORD removeBase);
};

