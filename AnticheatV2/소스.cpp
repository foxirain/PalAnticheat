#include "pch.h"
#include <stdio.h>
#include <windows.h>
#include "C:/Users/Path"
#include <winternl.h>
#include <tchar.h>
#include <set>
#include <string>

#pragma comment(lib, "C:/Users/Path")
std::set<std::string> DLLset;

// �Լ� ���� ����  ==============================================================||
typedef HANDLE(WINAPI* CreateRemoteThread_t)(
	HANDLE hProcess,
	LPSECURITY_ATTRIBUTES lpThreadAttributes,
	SIZE_T dwStackSize,
	LPTHREAD_START_ROUTINE lpStartAddress,
	LPVOID lpParameter,
	DWORD dwCreationFlags,
	LPDWORD lpThreadId
	);

typedef HMODULE(WINAPI* LoadLibraryA_t)(LPCSTR lpLibFileName);
typedef HMODULE(WINAPI* LoadLibraryW_t)(LPCWSTR lpLibFileName);
typedef HMODULE(WINAPI* LoadLibraryExA_t)(LPCSTR lpLibFileName, HANDLE hFile, DWORD dwFlags);
typedef HMODULE(WINAPI* LoadLibraryExW_t)(LPCWSTR lpLibFileName, HANDLE hFile, DWORD dwFlags);




//  =============================================================================||



// ��ŷ ���� ���� �Լ� ���� ����  ===============================================||

CreateRemoteThread_t Real_CreateRemoteThread = NULL;
LoadLibraryA_t Real_LoadLibraryA = NULL;
LoadLibraryW_t Real_LoadLibraryW = NULL;
LoadLibraryExA_t Real_LoadLibraryExA = NULL;
LoadLibraryExW_t Real_LoadLibraryExW = NULL;

//  =============================================================================||



//hook �Լ� ����  ===============================================||

HANDLE WINAPI Hooked_CreateRemoteThread(
	HANDLE hProcess,
	LPSECURITY_ATTRIBUTES lpThreadAttributes,
	SIZE_T dwStackSize,
	LPTHREAD_START_ROUTINE lpStartAddress,
	LPVOID lpParameter,
	DWORD dwCreationFlags,
	LPDWORD lpThreadId
) {

	MessageBox(NULL, TEXT("CreateRemoteThread called! Blocking this call By Anticheat_WG"), TEXT("Anticheat_WG"), MB_OK);
	return NULL;
}

HMODULE WINAPI Hooked_LoadLibraryA(LPCSTR lpLibFileName) {
	std::string dllname(lpLibFileName);
	if (DLLset.find(dllname) == DLLset.end()) {

		MessageBox(NULL, TEXT("LoadLibraryA called! Blocking this call By Anticheat_WG"), TEXT("Anticheat_WG"), MB_OK);
		return NULL;
	}
	else {
		return Real_LoadLibraryA(lpLibFileName);
	}
	
}

//  ==============================================================||



// Known dll ����  ==============================================================||


void Known_dll_init() {

	DLLset.insert("AkSoundSeedAir.dll");
	DLLset.insert("AkRoomVerb.dll");
	DLLset.insert("AkSilenceGenerator.dll");
	DLLset.insert("AkPeakLimiter.dll");
	DLLset.insert("AkTimeStretch.dll");
	DLLset.insert("AkGain.dll");
	DLLset.insert("MasteringSuite.dll");
	DLLset.insert("AkToneGen.dll");
	DLLset.insert("AkFlanger.dll");
	DLLset.insert("AkRecorder.dll");
	DLLset.insert("AkSineTone.dll");
	DLLset.insert("AkSynthOne.dll");
	DLLset.insert("AkStereoDelay.dll");
	DLLset.insert("AkMatrixReverb.dll");
	DLLset.insert("AkParametricEQ.dll");
	DLLset.insert("AkExpander.dll");
	DLLset.insert("AkGuitarDistortion.dll");
	DLLset.insert("boost_thread-vc142-mt-x64-1_70.dll");
	DLLset.insert("boost_python39-vc142-mt-x64-1_70.dll");
	DLLset.insert("boost_atomic-vc142-mt-x64-1_70.dll");
	DLLset.insert("boost_system-vc142-mt-x64-1_70.dll");
	DLLset.insert("libvorbisfile_64.dll");
	DLLset.insert("libogg_64.dll");
	DLLset.insert("dvp.dll");
	DLLset.insert("boost_chrono-vc142-mt-x64-1_70.dll");
	DLLset.insert("boost_iostreams-vc142-mt-x64-1_70.dll");
	DLLset.insert("McDSP.dll");
	DLLset.insert("AkSoundEngineDLL.dll");
	DLLset.insert("Auro.dll");
	DLLset.insert("iZotope.dll");
	DLLset.insert("AkReflect.dll");
	DLLset.insert("nvngx_dlss.dll");
	DLLset.insert("OpenImageDenoise.dll");
	DLLset.insert("tbb.dll");
	DLLset.insert("tbb12.dll");
	DLLset.insert("D3D12Core.dll");
	DLLset.insert("boost_program_options-vc142-mt-x64-1_70.dll");
	DLLset.insert("boost_regex-vc142-mt-x64-1_70.dll");
	DLLset.insert("tbb.dll");
	DLLset.insert("EOSSDK-Win64-Shipping.dll");
	DLLset.insert("xaudio2_9redist.dll");
	DLLset.insert("libvorbis_64.dll");
	DLLset.insert("steam_api64.dll");
	DLLset.insert("GFSDK_Aftermath_Lib.x64.dll");
	DLLset.insert("dbghelp.dll");
	DLLset.insert("libEGL.dll");
	DLLset.insert("libGLESv2.dll");
	DLLset.insert("libcef.dll");
	DLLset.insert("libEGL.dll");
	DLLset.insert("libGLESv2.dll");
	DLLset.insert("chrome_elf.dll");
	DLLset.insert("d3dcompiler_47.dll");
	DLLset.insert("AkCompressor.dll");
	DLLset.insert("AkHarmonizer.dll");
	DLLset.insert("AkDelay.dll");
	DLLset.insert("AkAudioInput.dll");
	DLLset.insert("AkTremolo.dll");
	DLLset.insert("AkPitchShifter.dll");
	DLLset.insert("Ak3DAudioBedMixer.dll");


}
//  ==============================================================||




//  �̸����� ����� üũ ============================( high overhead ) ||

BOOL IsWinDbgRunning() {
	HWND hwnd = GetTopWindow(NULL);
	TCHAR className[256];

	while (hwnd != NULL) {
		if (GetClassName(hwnd, className, sizeof(className) / sizeof(TCHAR))) {
			// Ŭ���� �̸��� ���ڿ��� ���ԵǴ��� Ȯ��
			if (_tcsstr(className, TEXT("HwndWrapper[DbgX.Shell;;")) != NULL) {   // spy++  �� Ȯ���� ���ڿ�
				return TRUE; // WinDbg ���� ��
			}
		}
		hwnd = GetNextWindow(hwnd, GW_HWNDNEXT);
	}
	return FALSE; // WinDbg ���� �� �ƴ�
}

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam) {
	TCHAR windowTitle[256];
	GetWindowText(hwnd, windowTitle, sizeof(windowTitle) / sizeof(TCHAR));

	// â ���� CheatEngine �� ���ԵǾ����� Ȯ��
	if (_tcsstr(windowTitle, TEXT("Cheat Engine")) != NULL) {
		*((BOOL*)lParam) = TRUE;
		return FALSE; // ã�����Ƿ� ��!
	}
	return TRUE; // ��� ����
}

BOOL IsCheatEngineRunning() {
	BOOL CheatEngineFound = FALSE;
	EnumWindows(EnumWindowsProc, (LPARAM)&CheatEngineFound);
	return CheatEngineFound;
}

//  ==============================================================||



// ����� üũ �Լ�   ==================================================================||



bool IsDebuggerPresentViaException() {

	BOOL debuggerDetected = true;
	__try {
		// ���ܸ� ����
		RaiseException(EXCEPTION_BREAKPOINT, 0, 0, NULL);	
	}
	__except (EXCEPTION_EXECUTE_HANDLER) {
		return false;
	}
	return debuggerDetected;
}



void CheckForDebugger() {
	// IsDebuggerPresent
	if (IsDebuggerPresent()) {
		MessageBox(NULL, TEXT("Debugger detected by Anticheat_WG"), TEXT("Anticheat_WG"), MB_OK);
		return;
	}

	// CheckRemoteDebuggerPresent
	BOOL debuggerPresent = FALSE;
	CheckRemoteDebuggerPresent(GetCurrentProcess(), &debuggerPresent);
	if (debuggerPresent) {
		MessageBox(NULL, TEXT("Remote debugger detected  by Anticheat_WG"), TEXT("Anticheat_WG"), MB_OK);
		return;
	}

	// NtQueryInformationProcess
	typedef NTSTATUS(WINAPI* NtQueryInformationProcess_t)(HANDLE, UINT, PVOID, ULONG, PULONG);
	NtQueryInformationProcess_t NtQueryInformationProcess = (NtQueryInformationProcess_t)GetProcAddress(GetModuleHandle(TEXT("ntdll.dll")), "NtQueryInformationProcess");
	if (NtQueryInformationProcess) {
		DWORD debugger = 0;
		NTSTATUS status = NtQueryInformationProcess(GetCurrentProcess(), 0x1F, &debugger, sizeof(debugger), NULL);
		if (status == 0x00000000 && debugger) {
			MessageBox(NULL, TEXT("Debugger detected by NtQueryInformationProcess (Anticheat_WG) "), TEXT("Anticheat_WG"), MB_OK);
			return;
		}
	}


	// UnhandledExceptionFilter
	if (IsDebuggerPresentViaException()) {
		MessageBox(NULL, TEXT("Debugger detected by UnhandledExceptionFilter (Anticheat_WG)"), TEXT("Anticheat_WG"), MB_OK);
	}
	else {
		//MessageBox(NULL, TEXT("No debugger detected by UnhandledExceptionFilter (Anticheat_WG)"), TEXT("Anticheat_WG"), MB_OK);
	}

	// ����� �������� üũ
	CONTEXT context = { 0 };
	context.ContextFlags = CONTEXT_DEBUG_REGISTERS;
	if (GetThreadContext(GetCurrentThread(), &context)) {
		if (context.Dr0 || context.Dr1 || context.Dr2 || context.Dr3 || context.Dr6 || context.Dr7) {
			MessageBox(NULL, TEXT("Hardware breakpoint detected!"), TEXT("Anticheat_WG"), MB_OK);
			return;
		}
	}

	MessageBox(NULL, TEXT("No debugger detected."), TEXT("Anticheat_WG"), MB_OK);
}

void CALLBACK TimerProc(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime) {
	CheckForDebugger();
}

// Ÿ�̸� ���� 
void SetDebuggerCheckTimer() {
	SetTimer(NULL, 0, 5000, (TIMERPROC)TimerProc); // 5�ʸ���
}



// ========================================================================================||




// Anticheat�� ���� �ɶ�
void HookFunctions() {
	DetourRestoreAfterWith();  // Detours �ʱ�ȭ
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());

	fflush(stdout);
	//Real_CreateRemoteThread �� ���� RemoteThread �Լ��� �ּ�
	Real_CreateRemoteThread = (CreateRemoteThread_t)GetProcAddress(GetModuleHandle(TEXT("kernel32.dll")), "CreateRemoteThread");
	if (Real_CreateRemoteThread != NULL) {

		//printf("Real_CreateRemoteThread address: %p\n", (void*)Real_CreateRemoteThread);
		//fflush(stdout);


		char message[256];
		sprintf_s(message, sizeof(message), "Real_CreateRemoteThread address: %p", (void*)Real_CreateRemoteThread);
		MessageBoxA(NULL, message, "Anticheat_WG", MB_OK);


		LONG error = DetourAttach(&(PVOID&)Real_CreateRemoteThread, (PVOID)Hooked_CreateRemoteThread);
		if (error == NO_ERROR) {
			//printf("DetourAttach succeeded.\n");
			//fflush(stdout);
		}
		else {
			MessageBox(NULL, TEXT(" Detour Attach Failed."), TEXT("Anticheat_WG Error"), MB_OK);
		}
	}

	Real_LoadLibraryA = (LoadLibraryA_t)GetProcAddress(GetModuleHandle(TEXT("kernel32.dll")), "LoadLibraryA");
	if (Real_LoadLibraryA != NULL) {

		//printf("Real_LoadLibraryA address: %p\n", (void*)Real_LoadLibraryA);
		//fflush(stdout);

		char message[256];
		sprintf_s(message, sizeof(message), "Real_LoadLibraryA address: %p", (void*)Real_LoadLibraryA);
		MessageBoxA(NULL, message, "Anticheat_WG", MB_OK);

		LONG error = DetourAttach(&(PVOID&)Real_LoadLibraryA, (PVOID)Hooked_LoadLibraryA);
		if (error == NO_ERROR) {
			//printf("DetourAttach for LoadLibraryA succeeded.\n");
			//fflush(stdout);
		}
		else {
			MessageBox(NULL, TEXT(" Detour Attach Failed."), TEXT("Anticheat_WG Error"), MB_OK);
		}
	}





	Real_LoadLibraryW = (LoadLibraryW_t)GetProcAddress(GetModuleHandle(TEXT("kernel32.dll")), "LoadLibraryW");
	if (Real_LoadLibraryW != NULL) {


		char message[256];
		sprintf_s(message, sizeof(message), "Real_LoadLibraryW address: %p", (void*)Real_LoadLibraryW);
		MessageBoxA(NULL, message, "Anticheat_WG", MB_OK);

		LONG error = DetourAttach(&(PVOID&)Real_LoadLibraryW, (PVOID)Hooked_LoadLibraryA);
		if (error == NO_ERROR) {

		}
		else {
			MessageBox(NULL, TEXT(" Detour Attach Failed."), TEXT("Anticheat_WG Error"), MB_OK);
		}
	}


	Real_LoadLibraryExA = (LoadLibraryExA_t)GetProcAddress(GetModuleHandle(TEXT("kernel32.dll")), "LoadLibraryExA");
	if (LoadLibraryExA != NULL) {


		char message[256];
		sprintf_s(message, sizeof(message), "Real_LoadLibraryExA address: %p", (void*)Real_LoadLibraryExA);
		MessageBoxA(NULL, message, "Anticheat_WG", MB_OK);

		LONG error = DetourAttach(&(PVOID&)Real_LoadLibraryExA, (PVOID)Hooked_LoadLibraryA);
		if (error == NO_ERROR) {

		}
		else {
			MessageBox(NULL, TEXT(" Detour Attach Failed."), TEXT("Anticheat_WG Error"), MB_OK);
		}
	}

	Real_LoadLibraryExW = (LoadLibraryExW_t)GetProcAddress(GetModuleHandle(TEXT("kernel32.dll")), "LoadLibraryExW");
	if (LoadLibraryExA != NULL) {


		char message[256];
		sprintf_s(message, sizeof(message), "Real_LoadLibraryExW address: %p", (void*)Real_LoadLibraryExW);
		MessageBoxA(NULL, message, "Anticheat_WG", MB_OK);

		LONG error = DetourAttach(&(PVOID&)Real_LoadLibraryExW, (PVOID)Hooked_LoadLibraryA);
		if (error == NO_ERROR) {

		}
		else {
			MessageBox(NULL, TEXT(" Detour Attach Failed."), TEXT("Anticheat_WG Error"), MB_OK);
		}
	}










	DetourTransactionCommit();
}

// Anticheat�� ��ü �ɶ�
void UnhookFunctions() {
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	if (Real_CreateRemoteThread != NULL) {
		DetourDetach(&(PVOID&)Real_CreateRemoteThread, (PVOID)Hooked_CreateRemoteThread);
	}

	if (Real_LoadLibraryA != NULL) {
		DetourDetach(&(PVOID&)Real_LoadLibraryA, (PVOID)Hooked_LoadLibraryA);
	}
	DetourTransactionCommit();
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
	BOOL Init_Antidbg = false;
	Known_dll_init();
	switch (ul_reason_for_call) {
	case DLL_PROCESS_ATTACH:
		//printf("Anticheat working now.\n");
		//fflush(stdout);
		MessageBox(NULL, TEXT("Anticheat working now."), TEXT("Anticheat_WG"), MB_OK);
		HookFunctions();
		

		// FindWindow�� ����Ͽ� WinDbg â �˻�
		if (IsWinDbgRunning()) {
			Init_Antidbg = true;
			MessageBox(NULL, TEXT("WinDbg detected!"), TEXT("Anticheat_WG"), MB_OK);
		}
		else if (IsCheatEngineRunning()) {
			Init_Antidbg = true;
			MessageBox(NULL, TEXT("CheatEngine detected!"), TEXT("Anticheat_WG"), MB_OK);

		}
		else {
			SetDebuggerCheckTimer(); // ����� üũ ����
		}

		break;
	case DLL_PROCESS_DETACH:
		//printf("Anticheat ending now.\n");
		//fflush(stdout);
		MessageBox(NULL, TEXT("Anticheat ending."), TEXT("Anticheat_WG"), MB_OK);
		UnhookFunctions();
		if (!Init_Antidbg)
			KillTimer(NULL, 0); // ����� üũ ��!
		break;
	}
	return TRUE;
}
