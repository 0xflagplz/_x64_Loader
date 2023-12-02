# _x64_Loader
Utilizing Alternative Shellcode Execution Via Callbacks

[Shellcode Generation](https://github.com/AchocolatechipPancake/encode_payload "Shellcode Generation")

1. Run shellcode script
2. Insert Output in main.cpp:
```
    char encryptedShellcode[] = "CHANGEME";
    char key[] = "CHANGEME";
    char cipherType[] = "CHANGEME";
```
3.  Build with Visual Studio

Sandbox check / XORorAES / EnumUILanguagesW & InitOnceExecuteOnce
  
  
https://docs.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-initonceexecuteonce   
https://docs.microsoft.com/en-us/windows/win32/api/winnls/nf-winnls-enumuilanguagesw

