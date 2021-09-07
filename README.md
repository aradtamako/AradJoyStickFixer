# AradJoyStickFixer

### Features
- Disable mouse move(right stick)

### Download
https://github.com/aradtamako/AradJoyStickFixer/releases

### How to use
1. Copy DLL to Arad client directory
```
copy AradJoyStickFixer.dll C:\Nexon\ARAD\version.dll
```

2. Start Arad as usual

### Requirements
- Windows 64bit

### Build Requirements
- Visual Studio 2019(MSVC v142) Build Tools
- vcpkg
- Detours

```
vcpkg install detours:x64-windows
```

# Third Party License(s)
- Detours ([MIT License](https://github.com/microsoft/Detours/blob/master/LICENSE.md))

# Tested devices
- Windows 10 64bit 20H2, [BSGP1601BK](https://www.buffalo.jp/product/detail/bsgp1601bk.html) (2021/09/07)
