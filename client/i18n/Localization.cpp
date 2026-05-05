#include "Localization.hpp"

#include <cstdio>
#include <cstring>
#include <string>
#include <unordered_map>

namespace i18n
{
    namespace
    {
        using Table = std::unordered_map<std::string, std::string>;

        Locale gLocale = Locale::Japanese;
        std::string gSettingsPath;

        const Table& EnglishTable()
        {
            static const Table t = {
#define I18N_STR(k, v) {k, v},
#include "strings_keys.inc"
#undef I18N_STR
            };
            return t;
        }

        const Table& JapaneseTable()
        {
            static const Table t = {
#define I18N_STR(k, v) {k, v},
#include "strings_ja.inc"
#undef I18N_STR
            };
            return t;
        }
    }

    void SetLocale(Locale loc) { gLocale = loc; }
    Locale GetLocale() { return gLocale; }

    const char* LocaleToString(Locale loc)
    {
        switch (loc)
        {
        case Locale::Japanese: return "ja";
        default:               return "en";
        }
    }

    Locale LocaleFromString(const char* s)
    {
        if (s && std::strcmp(s, "ja") == 0) return Locale::Japanese;
        return Locale::English;
    }

    void SetSettingsPath(const char* path) { gSettingsPath = path ? path : ""; }

    bool LoadSettings()
    {
        if (gSettingsPath.empty()) return false;
        FILE* f = std::fopen(gSettingsPath.c_str(), "r");
        if (!f) return false;
        char line[128];
        while (std::fgets(line, sizeof(line), f))
        {
            line[std::strcspn(line, "\r\n")] = '\0';
            if (std::strncmp(line, "locale=", 7) == 0)
                gLocale = LocaleFromString(line + 7);
        }
        std::fclose(f);
        return true;
    }

    bool SaveSettings()
    {
        if (gSettingsPath.empty()) return false;
        FILE* f = std::fopen(gSettingsPath.c_str(), "w");
        if (!f) return false;
        std::fprintf(f, "locale=%s\n", LocaleToString(gLocale));
        std::fclose(f);
        return true;
    }

    const char* tr(const char* key)
    {
        if (gLocale == Locale::Japanese)
        {
            const auto& ja = JapaneseTable();
            auto it = ja.find(key);
            if (it != ja.end())
                return it->second.c_str();
        }
        const auto& en = EnglishTable();
        auto it = en.find(key);
        if (it != en.end())
            return it->second.c_str();
        return key;
    }
}
