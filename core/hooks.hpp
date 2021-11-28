#pragma once
#include "../source sdk/sdk.hpp"
#include "../minhook/MinHook.h"

namespace hooks {
	using PaintTraverseFn = void(__thiscall*)(IPanel*, unsigned int, bool, bool);
	void __stdcall PaintTraverseHk(unsigned int panel, bool forceRepaint, bool allowForce);
}

hooks::PaintTraverseFn originalPaintTraverse = nullptr;