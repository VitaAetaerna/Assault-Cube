#include "includes.h"
//Process ID and base Module
DWORD pID, baseModule;

//Pointer
DWORD localPlayerPointer;
//Health Pointer = 0xEC

//Values
int healthToSet = 999;
int currentHealth;

int ammoToSet = 100;
int currentAmmo;

int speedToAdd = 1;  
int currentSpeed;
int main(){
	
	//Get Process ID and Base Address
	pID = getProcessID(L"ac_client.exe");
	baseModule = GetModuleBaseAddress(pID, L"ac_client.exe");
	std::cout << "Process name: ac_client.exe" << std::endl;

	std::cout << pID << std::endl;
	std::cout << std::hex << baseModule << std::endl;

	//Open Process with all Rights
	HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, NULL, pID);
	//Getting Local Player Address with Base Address + Pointer
	ReadProcessMemory(handle, (LPCVOID)(baseModule + 0x17E0A8), &localPlayerPointer, sizeof(localPlayerPointer), nullptr);
	std::cout << "Local Player Addr: " << std::hex << localPlayerPointer << std::endl;

	while (true) {
	//Health
		//Read Process memory for current Health | storing it in currentHealth
		ReadProcessMemory(handle, (LPVOID)(localPlayerPointer + 0xEC), &currentHealth, sizeof(currentHealth), nullptr);
		if (currentHealth < 100) {
			//Write healthToSet into Memory Address of Health
			WriteProcessMemory(handle, (LPVOID)(localPlayerPointer + 0xEC), &healthToSet, sizeof(&healthToSet), nullptr);
			std::cout << "Health changed to " << healthToSet << std::endl;
		}

	//Ammo Gun
		ReadProcessMemory(handle, (LPCVOID)(localPlayerPointer + AMMOPOINTER), &currentAmmo, sizeof(currentAmmo), nullptr);
		if (currentAmmo < 10) {
			WriteProcessMemory(handle, (LPVOID)(localPlayerPointer + AMMOPOINTER), &ammoToSet, sizeof(ammoToSet), nullptr);
			std::cout << "Ammo changed to " << ammoToSet << std::endl;
		}

	//Bunnyhop or Speed change
		ReadProcessMemory(handle, (LPCVOID)(localPlayerPointer + SPEEDPOINTER), &currentSpeed, sizeof(currentSpeed), nullptr);
		if (GetKeyState('F') && 0x8000){
			WriteProcessMemory(handle, (LPVOID)(localPlayerPointer + SPEEDPOINTER), &currentSpeed+speedToAdd, sizeof(speedToAdd), nullptr);
		}

	// ?Changing Damage of Weapon?

	// ESP / Wallhack

	// fly?

	//teleport?



	}

}

