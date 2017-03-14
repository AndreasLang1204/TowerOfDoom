#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

#include "easylogging++.h"

#include <memory>

#include <string>

#include <set>
#include <stack>
#include <unordered_map>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#ifndef IsAbstract__
#define IsAbstract__														= 0
#endif

#ifndef IsDeleted__
#define IsDeleted__															= delete
#endif

#ifndef IsDefault__
#define IsDefault__															= default
#endif
