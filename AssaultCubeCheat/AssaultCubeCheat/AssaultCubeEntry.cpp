#include "includes.h"
int main(){
	DWORD pID, baseModule, localPlayerPointer;
	int health = 9999;
	//Get Process ID and Base Address
	pID = getProcessID(L"ac_client.exe");
	baseModule = GetModuleBaseAddress(pID, L"ac_client.exe");

	std::cout << pID << std::endl;
	std::cout << std::hex << baseModule << std::endl;

	//Open Process with all Rights
	HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, NULL, pID);
	//Getting Local Player Address with Base Address + Pointer
	ReadProcessMemory(handle, (LPCVOID)(baseModule + 0x17E0A8), &localPlayerPointer, sizeof(localPlayerPointer), nullptr);
	std::cout << "Local Player Addr: " << std::hex << localPlayerPointer << std::endl;

	while (true) {
		WriteProcessMemory(handle, (LPVOID)(localPlayerPointer + 0xEC), &health, sizeof(health), nullptr);
	}

}

