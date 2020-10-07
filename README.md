# pomegranate

## Pre-setup
1. Download repo at https://github.com/antlr/antlr4
1. Cd to <path_to_repo>/runtime/Cpp
1. Run "deploy-windows.cmd Community"
1. Copy output DLLs and libs (found in bin/some subdirectory) to thirdparty/antlr-runtime
1. Copy antlr4-runtime.dll to C:\Windows\System32
1. Run "regsvr32 antlr4-runtime.dll" on command line

1. Download Autodesk FBX SDK (https://www.autodesk.com/developer-network/platform-technologies/fbx-sdk-2020-0) 
1. Find libfbxsdk.dll and copy to C:\Windows\System32 and run "regsvr32 libfbxsdk.dll"