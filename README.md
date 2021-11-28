# csgo-minhook-cheat-sdk

This is my improved CSGO cheat SDK which includes the minhook detour hooking library. This was made to 1 up my last SDK which was a little messy and had a bit of code
from a few SDKs. In this SDK, it has examples of automatically updating interfaces (not that they update often anyway), a PaintTraverse hook (a panel we can use to draw with surface - valve's direct-x wrapper
for drawing stuff) and obviously minhook's undetected (for now) hooking library. This is a good base to learn from as it is simple (realistically, everything you'd need
to read is in main.cpp other than hook prototypes in hooks.hpp and valve's source sdk classes).

Credits <br />
PenerSDK - automatically updating interface function <br />
Minhook - open source hooking library <br />
Valve - interface classes <br />
