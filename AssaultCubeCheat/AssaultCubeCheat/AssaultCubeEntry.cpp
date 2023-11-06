#include "includes.h"
//Process ID and base Module
DWORD pID, baseModule;

//Pointer
DWORD localPlayerPointer;
//Health Pointer = 0xEC

//Values
int healthToSet = 999;
int currentHealth;
int main(){
	
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
		//Read Process memory for current Health | storing it in currentHealth
		ReadProcessMemory(handle, (LPVOID)(localPlayerPointer + 0xEC), &currentHealth, sizeof(currentHealth), nullptr);
		if (currentHealth < 100) {
			//Write healthToSet into Memory Address of Health
			WriteProcessMemory(handle, (LPVOID)(localPlayerPointer + 0xEC), &healthToSet, sizeof(&healthToSet), nullptr);
			std::cout << "Health changed to " << healthToSet << std::endl;
		}
	}

}

