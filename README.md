# pomegranate

## Pre-setup
1. Download repo at https://github.com/antlr/antlr4
2. Cd to <path_to_repo>/runtime/Cpp
3. Run "deploy-windows.cmd Community"
4. Copy output DLLs and libs (found in bin/some subdirectory) to thirdparty/antlr-runtime
5. Copy antlr4-runtime.dll to C:\Windows\System32
6. Run "regsvr32 antlr4-runtime.dll" on command line