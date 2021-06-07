#pragma once

#include "TP\rapidjson\document.h"
#include "TP\rapidjson\istreamwrapper.h"
#include <fstream>
#include <string>

using JsonFile = rapidjson::Document;

void LoadJsonFile(JsonFile* json, std::string _path);
