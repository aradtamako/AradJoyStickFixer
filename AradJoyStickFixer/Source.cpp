#include <Windows.h>
#include <iostream>

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

#include "DetoursHelper.hpp"

#define FUNCTION_INDEX_GET_DEVICE_STATE 9
// #define SHOW_CONSOLE

LPDIRECTINPUT8 pDirectInput = NULL;
LPDIRECTINPUTDEVICE8 pDirectInputDevice = NULL;

HRESULT(*funcGetDeviceState)(IDirectInputDevice8* pThis, DWORD cbData, LPVOID lpvData);

#pragma region Proxy
#define FUNCTION_COUNT 17

extern "C" uintptr_t functions[FUNCTION_COUNT] = { 0 };
std::string functionNames[] =
{
	"GetFileVersionInfoA",
	"GetFileVersionInfoByHandle",
	"GetFileVersionInfoExA",
	"GetFileVersionInfoExW",
	"GetFileVersionInfoSizeA",
	"GetFileVersionInfoSizeExA",
	"GetFileVersionInfoSizeExW",
	"GetFileVersionInfoSizeW",
	"GetFileVersionInfoW",
	"VerFindFileA",
	"VerFindFileW",
	"VerInstallFileA",
	"VerInstallFileW",
	"VerLanguageNameA",
	"VerLanguageNameW",
	"VerQueryValueA",
	"VerQueryValueW"
};

// [index: 000] [ordinal: 001] GetFileVersionInfoA
#pragma comment(linker, "/EXPORT:GetFileVersionInfoA=func_fe4c7fdb42a74533b75718c1a0d72a32,@1")
extern "C" void func_fe4c7fdb42a74533b75718c1a0d72a32();

// [index: 001] [ordinal: 002] GetFileVersionInfoByHandle
#pragma comment(linker, "/EXPORT:GetFileVersionInfoByHandle=func_78e5d8c052c4411ead75ffc003aa15c2,@2")
extern "C" void func_78e5d8c052c4411ead75ffc003aa15c2();

// [index: 002] [ordinal: 003] GetFileVersionInfoExA
#pragma comment(linker, "/EXPORT:GetFileVersionInfoExA=func_7db5a5a62d3840cc90b54aa102d2bcea,@3")
extern "C" void func_7db5a5a62d3840cc90b54aa102d2bcea();

// [index: 003] [ordinal: 004] GetFileVersionInfoExW
#pragma comment(linker, "/EXPORT:GetFileVersionInfoExW=func_d358f83b33cb4691a579fce03067ae51,@4")
extern "C" void func_d358f83b33cb4691a579fce03067ae51();

// [index: 004] [ordinal: 005] GetFileVersionInfoSizeA
#pragma comment(linker, "/EXPORT:GetFileVersionInfoSizeA=func_9f825301df494579abfc09f03f3c54d7,@5")
extern "C" void func_9f825301df494579abfc09f03f3c54d7();

// [index: 005] [ordinal: 006] GetFileVersionInfoSizeExA
#pragma comment(linker, "/EXPORT:GetFileVersionInfoSizeExA=func_d2be5693a866477d88eb95b38bcc43bc,@6")
extern "C" void func_d2be5693a866477d88eb95b38bcc43bc();

// [index: 006] [ordinal: 007] GetFileVersionInfoSizeExW
#pragma comment(linker, "/EXPORT:GetFileVersionInfoSizeExW=func_afd0da792aec4d07bea827125e0ac78f,@7")
extern "C" void func_afd0da792aec4d07bea827125e0ac78f();

// [index: 007] [ordinal: 008] GetFileVersionInfoSizeW
#pragma comment(linker, "/EXPORT:GetFileVersionInfoSizeW=func_71105ab8658e4b6db0b52a07968b528b,@8")
extern "C" void func_71105ab8658e4b6db0b52a07968b528b();

// [index: 008] [ordinal: 009] GetFileVersionInfoW
#pragma comment(linker, "/EXPORT:GetFileVersionInfoW=func_342c1a6a00aa4d46b83df34943550a9e,@9")
extern "C" void func_342c1a6a00aa4d46b83df34943550a9e();

// [index: 009] [ordinal: 010] VerFindFileA
#pragma comment(linker, "/EXPORT:VerFindFileA=func_072a04327c64486c8425c21254736100,@10")
extern "C" void func_072a04327c64486c8425c21254736100();

// [index: 010] [ordinal: 011] VerFindFileW
#pragma comment(linker, "/EXPORT:VerFindFileW=func_b48fcd678a404a7c968d9022fbdac04b,@11")
extern "C" void func_b48fcd678a404a7c968d9022fbdac04b();

// [index: 011] [ordinal: 012] VerInstallFileA
#pragma comment(linker, "/EXPORT:VerInstallFileA=func_c173057a0e1f4deca76facd39bd3a41b,@12")
extern "C" void func_c173057a0e1f4deca76facd39bd3a41b();

// [index: 012] [ordinal: 013] VerInstallFileW
#pragma comment(linker, "/EXPORT:VerInstallFileW=func_a14eafed955447c48f67df119f1d3fcb,@13")
extern "C" void func_a14eafed955447c48f67df119f1d3fcb();

// [index: 013] [ordinal: 014] VerLanguageNameA
#pragma comment(linker, "/EXPORT:VerLanguageNameA=func_9523acace69b47adaad7bd5c6e9e46c9,@14")
extern "C" void func_9523acace69b47adaad7bd5c6e9e46c9();

// [index: 014] [ordinal: 015] VerLanguageNameW
#pragma comment(linker, "/EXPORT:VerLanguageNameW=func_df1cf354a542489cbee049bc15fb16f1,@15")
extern "C" void func_df1cf354a542489cbee049bc15fb16f1();

// [index: 015] [ordinal: 016] VerQueryValueA
#pragma comment(linker, "/EXPORT:VerQueryValueA=func_61afd6e9c83741bb9378beb2d8117e29,@16")
extern "C" void func_61afd6e9c83741bb9378beb2d8117e29();

// [index: 016] [ordinal: 017] VerQueryValueW
#pragma comment(linker, "/EXPORT:VerQueryValueW=func_78983027b5ce46ff863ec460565f99c8,@17")
extern "C" void func_78983027b5ce46ff863ec460565f99c8();
#pragma endregion

uintptr_t GetVirtualFunctionAddress(uintptr_t base, int functionIndex) {
	auto pFunction = reinterpret_cast<uintptr_t*>(base + (functionIndex * sizeof(uintptr_t)));
	return *reinterpret_cast<uintptr_t*>(pFunction);
}

void DetourGetDeviceState() {
	static auto OriginalFunction = funcGetDeviceState;

	decltype(funcGetDeviceState) HookFunction = [](IDirectInputDevice8* pThis, DWORD cbData, LPVOID lpvData) -> HRESULT {
		auto result = OriginalFunction(pThis, cbData, lpvData);

		switch (cbData) {
			case sizeof(DIJOYSTATE) :
				// I don't have any devices run this scene, so i can't implement
				break;
			case sizeof(DIJOYSTATE2) :
				auto data = reinterpret_cast<DIJOYSTATE2*>(lpvData);

				/*
				// EasyDash for keyboard
				if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
					data->lX = -1000;
				}
				else if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
					data->lX = 1000;
				}
				*/

				// Change right stick state
				data->lZ = 0;
				data->lRz = 0;
				break;
		}

		return result;
	};

	DetourFunction(true, reinterpret_cast<LPVOID*>(&OriginalFunction), HookFunction);
}

BOOL CALLBACK EnumDevicesCallback(const LPCDIDEVICEINSTANCE pDirectInputDeviceInstance, VOID* pContext) {
	if (pDirectInput->CreateDevice(pDirectInputDeviceInstance->guidInstance, &pDirectInputDevice, NULL) != DI_OK) {
		pDirectInput->Release();
		return DIENUM_CONTINUE;
	}
	else {
		funcGetDeviceState = reinterpret_cast<decltype(funcGetDeviceState)>(GetVirtualFunctionAddress(*reinterpret_cast<uintptr_t*>(pDirectInputDevice), FUNCTION_INDEX_GET_DEVICE_STATE));

		// Hook GetDeviceState
		DetourGetDeviceState();
		return DIENUM_STOP;
	}
}

void MainThread() {
	auto hInstance = GetModuleHandle(NULL);

	while (true) {
		if (DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, reinterpret_cast<LPVOID*>(&pDirectInput), NULL) != DI_OK) {
			// std::wcout << "DirectInput8Create failed!" << std::endl;
			continue;
		}

		if (pDirectInput->EnumDevices(DI8DEVCLASS_GAMECTRL, EnumDevicesCallback, NULL, DIEDFL_ATTACHEDONLY) != DI_OK) {
			// std::wcout << "Failed to enumerate devices" << std::endl;
			continue;
		}

		// Check every 10 seconds
		Sleep(10 * 1000);
	}
}

#pragma unmanaged
BOOL WINAPI DllMain(HINSTANCE hinstModule, DWORD dwReason, LPVOID lpvReserved) {
	if (dwReason == DLL_PROCESS_ATTACH) {
		DisableThreadLibraryCalls(hinstModule);

		wchar_t buffer[MAX_PATH];
		auto len = GetSystemDirectory(buffer, MAX_PATH);
		std::wstring originalModulePath(buffer, len);
		auto moduleHandle = LoadLibrary(originalModulePath.append(L"\\version.dll").c_str());
		if (moduleHandle != nullptr) {
			for (auto i = 0; i < FUNCTION_COUNT; i++) {
				auto address = GetProcAddress(moduleHandle, functionNames[i].c_str());
				functions[i] = reinterpret_cast<uintptr_t>(address);
			}
		}

#ifdef SHOW_CONSOLE
		AllocConsole();
		AttachConsole(GetCurrentProcessId());
		FILE* pFile = nullptr;
		freopen_s(&pFile, "CON", "r", stdin);
		freopen_s(&pFile, "CON", "w", stdout);
		freopen_s(&pFile, "CON", "w", stderr);
#endif

		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)&MainThread, NULL, NULL, NULL);
	}

	return TRUE;
}
