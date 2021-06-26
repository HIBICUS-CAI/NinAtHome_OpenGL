#pragma once

#include "TP\rapidjson\document.h"
#include "TP\rapidjson\istreamwrapper.h"
#include "TP\rapidjson\pointer.h"
#include "TP\rapidjson\filereadstream.h"
#include <fstream>
#include <string>

using JsonFile = rapidjson::Document;
using JsonNode = rapidjson::Value*;

void LoadJsonFile(JsonFile* json, std::string _path);

JsonNode GetJsonNode(JsonFile* _file, std::string _path);
