#include "stdafx.h"

#include <crtdbg.h>

#include "../Engine/General/Engine.h"

int main()
{
	ToD::Main();

	_CrtDumpMemoryLeaks();

	return 0;
}
