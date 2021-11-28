#pragma once
#include <windows.h>

#include "IAppSystem.hpp"
#include "IPanel.hpp"
#include "ISurface.hpp"

namespace interfaces {
	IPanel* g_VGuiPanel;
	ISurface* g_VGuiSurface;
}

namespace tools {
	typedef void* (*create_interface_fn)(const char* Name, int* ReturnCode);
	inline void* captureInterface(const char* Module, const char* InterfaceName) {
		void* Interface = nullptr;
		auto CreateInterface = reinterpret_cast<create_interface_fn>(GetProcAddress(GetModuleHandleA(Module), "CreateInterface"));

		char PossibleInterfaceName[1024];
		for (int i = 1; i < 100; i++) {
			sprintf(PossibleInterfaceName, "%s0%i", InterfaceName, i);
			Interface = CreateInterface(PossibleInterfaceName, 0);
			if (Interface)
				break;

			sprintf(PossibleInterfaceName, "%s00%i", InterfaceName, i);
			Interface = CreateInterface(PossibleInterfaceName, 0);
			if (Interface)
				break;
		}

		return Interface;
	}

	inline unsigned int createVirtual(void* _class, unsigned int index) { 
		return static_cast<unsigned int>((*static_cast<int**>(_class))[index]); 
	}
}