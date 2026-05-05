#pragma once

#include <string>

namespace i18n
{
    enum class Locale
    {
        English,
        Japanese,
    };

    void SetLocale(Locale loc);
    Locale GetLocale();

    // Locale serialization for settings file persistence.
    const char* LocaleToString(Locale loc);
    Locale LocaleFromString(const char* s);

    // Settings persistence. Path is set once at startup; load/save use that path.
    void SetSettingsPath(const char* path);
    bool LoadSettings();
    bool SaveSettings();

    // Returns a UTF-8 C string for the active locale.
    // Falls back to English, then to the key itself if neither table has it.
    const char* tr(const char* key);

    // Concatenates a PlexSansIcon glyph with the translated text.
    // Caller passes .c_str() to ImGui; the returned std::string lives until end of statement.
    inline std::string trIcon(const char* icon, const char* key)
    {
        return std::string(icon) + tr(key);
    }
}
