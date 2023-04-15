#pragma once

// FMOD
#pragma comment(lib, "..\\lib\\fmod_vc.lib")
#include "..\\inc\\fmod.hpp"

// namespace 
using namespace FMOD;
using namespace std;

// C++ / STL
#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <list>
#include <array>

//rapidjson
#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"		// for stringify JSON
#include "rapidjson/filereadstream.h"	// fopen입출력을 위해..
#include "rapidjson/filewritestream.h"
#include "rapidjson/error/error.h"		// 에러판단을 위해서
#include "rapidjson/error/en.h"
#include "rapidjson/encodedstream.h"    // AutoUTFInputStream Json파일 인코딩 해석을 위해서..

#include "Product.h"
#include "Products.h"

#include <Windows.h>
#include <tchar.h>