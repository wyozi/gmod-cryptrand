#include "GarrysMod/Lua/Interface.h"
#include <stdio.h>
#include "security_csprng.h"

using namespace GarrysMod::Lua;

static CubicleSoft::Security::CSPRNG* randGenerator;

const uint64_t MAX_RAND = 0xFFFFFFFF;

int Lua_CryptRand(lua_State* state) {
	uint64_t res = 0;

	if (!randGenerator->GetInteger(res, 0, MAX_RAND)) {
		LUA->PushBool(false);
		LUA->PushString("Failed to generate random integer");
		return 2;
	}

	double val = ((double)res) / ((double)MAX_RAND);
	LUA->PushNumber(val);
	return 1;
}

GMOD_MODULE_OPEN()
{
	randGenerator = new CubicleSoft::Security::CSPRNG(false);

	LUA->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB);
	LUA->PushString("CryptRandom");
	LUA->PushCFunction(Lua_CryptRand);
	LUA->SetTable(-3);

	return 0;
}

GMOD_MODULE_CLOSE()
{
	delete randGenerator;

	return 0;
}