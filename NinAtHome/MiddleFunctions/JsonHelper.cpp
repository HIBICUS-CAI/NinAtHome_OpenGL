#include "JsonHelper.h"
#include <vector>

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
    {
        std::vector<std::string> v;
        JOSNSplitByRomSymbol(_path, v, ":/");
        _path = v[0] + "\\" + v[1];
    }

    std::ifstream ifs(_path);
    rapidjson::IStreamWrapper isw(ifs);
    json->ParseStream(isw);
}
