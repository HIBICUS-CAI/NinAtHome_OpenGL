#include "JsonHelper.h"
#include <vector>
#include "main.h"

const unsigned int MAX_NAME = 1024;

void JOSNSplitByRomSymbol(const std::string& s,
    std::vector<std::string>& v, const std::string& c)
{
    v.clear();
    std::string::size_type pos1 = 0, pos2 = s.find(c);
    while (std::string::npos != pos2)
    {
        v.push_back(s.substr(pos1, pos2 - pos1));

        pos1 = pos2 + c.size();
        pos2 = s.find(c, pos1);
    }
    if (pos1 != s.length())
        v.push_back(s.substr(pos1));
}

void LoadJsonFile(JsonFile* json, std::string _path)
{
#ifdef NIN_AT_HOME
    {
        std::vector<std::string> v;
        JOSNSplitByRomSymbol(_path, v, ":/");
        _path = v[0] + "\\" + v[1];
        v.clear();
        JOSNSplitByRomSymbol(_path, v, "/");
        if (v.size() > 1)
        {
            _path = "";
            for (int i = 0; i < v.size(); i++)
            {
                if (i == (v.size() - 1))
                {
                    _path += v[i];
                }
                else
                {
                    _path += v[i] + "\\";
                }
            }
        }
    }

    std::ifstream ifs(_path);
    rapidjson::IStreamWrapper isw(ifs);
    json->ParseStream(isw);
#else
    nn::Result result;
    nn::fs::FileHandle file;
    size_t readSize;
    int64_t fileSize;

    result = nn::fs::OpenFile(&file, _path, nn::fs::OpenMode_Read);
    if (nn::fs::ResultPathNotFound::Includes(result))
    {
        NN_ASSERT(false, "OpenFile:", _path);
    }

    result = nn::fs::GetFileSize(&fileSize, file);

    char* buffer = new char[fileSize + 1];

    nn::fs::ReadFile(&readSize, file, 0, buffer, fileSize + 1);

    buffer[fileSize] = '\0';

    std::string s(buffer);

    json->Parse(buffer);

    delete[] buffer;
#endif // NIN_AT_HOME
}

JsonNode GetJsonNode(JsonFile* _file, std::string _path)
{
    static char name[MAX_NAME];
    sprintf_s(name, MAX_NAME, "%s", _path.c_str());

    rapidjson::Pointer ptr(name);

    return rapidjson::GetValueByPointer(*_file, ptr);
}
