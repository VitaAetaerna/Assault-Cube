#include "proc.h"

DWORD getProcessID(const wchar_t* procName)
{
	DWORD procID = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (hSnap != INVALID_HANDLE_VALUE) {
		PROCESSENTRY32 procEntry32;
		procEntry32.dwSize = sizeof(procEntry32);

		if (Process32First(hSnap, &procEntry32)) {
			do {
				if (!_wcsicmp(procEntry32.szExeFile, procName)) {
					procID = procEntry32.th32ProcessID;
					break;
				}

			} while (Process32Next(hSnap, &procEntry32));
		}
	}
	CloseHandle(hSnap);
	return procID;
}

DWORD GetModuleBaseAddress(DWORD procID, const wchar_t* modName)
{
	DWORD modBaseAddr = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procID);

	if (hSnap != INVALID_HANDLE_VALUE) 
	{
		MODULEENTRY32 modEntry;
		modEntry.dwSize = sizeof(modEntry);
		if (Module32First(hSnap, &modEntry)) {
			do {
				if (!_wcsicmp(modEntry.szModule, modName)) {
					modBaseAddr = (DWORD)modEntry.modBaseAddr;
					break;
				}
			} while (Module32Next(hSnap, &modEntry));
		}
	}
	CloseHandle(hSnap);
	return modBaseAddr;
}