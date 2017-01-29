//
// Created by faiaz on 25.01.17.
//
#include <cstdio>
#include <windows.h>

int main() {

    STARTUPINFO cif;
    PROCESS_INFORMATION pi;

    ZeroMemory(&cif,sizeof(STARTUPINFO));

    if (CreateProcess("path2App", NULL, NULL, NULL, FALSE, NULL, NULL, NULL, &cif, &pi)==TRUE)

    return 0;
};
