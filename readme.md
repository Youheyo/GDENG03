Initial Requirements
Visual Studio 2022. Version 17.7.2 or higher
Desktop development with C++ and Game Development with C++ workloads

Check for individual packages
Windows 11 SDK (10.0.22621.0)
Windows 10 SDK (10.0.19041.0)

# For linking on Visual Studio Community

Go to Project->Properties

VC+++ Directories
Library Directories:
```
$(ProjectDir)Libs\DirectXTex\bin
$(ProjectDir)Libs\ReactPhysics3D\
```
C/C++
Additional Include Directories
```
$(ProjectDir)Libs\ReactPhysics3D\Include
```
Linker
Input
```
D3DCompiler.lib
d3d11.lib
DirectXTexD.lib
reactphysics3d.lib
```

Preprocessor
```
NOMINMAX
_CRT_SECURE_NO_WARNINGS
_DEBUG
-CONSOLE
```
