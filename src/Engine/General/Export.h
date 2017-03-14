#pragma once

////////////////////////////////////////////////////////////
// Define portable import / export macros
////////////////////////////////////////////////////////////
#if defined(ENGINE_EXPORTS)

#define ENGINE_API __declspec(dllexport)

#else

#define ENGINE_API __declspec(dllimport)

#endif
