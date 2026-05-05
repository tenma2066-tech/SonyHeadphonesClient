#include "../Platform.hpp"
#include <mdr/Protocol.hpp>
#include <mdr-c/Platform/PlatformWindows.h>
#include <mdr-c/Platform/PlatformWindowsBLE.h>

#include <cstdio>
#include <cstdlib>
#include <string>

static MDRConnectionWindows* gConnClassic = nullptr;
static MDRConnectionWindowsBLE* gConnBLE = nullptr;
extern "C" {
    int clientPlatformConnectionInit(int flags)
    {
        MDR_CHECK_MSG(gConnBLE == nullptr && gConnClassic == nullptr, "Platform already initialized. You MUST call clientPlatformDestroy() before initializing again.");
        if (flags & MDR_INIT_BT_BLE)
            gConnBLE = mdrConnectionWindowsBLECreate(), gConnClassic = nullptr;
        else
            gConnClassic = mdrConnectionWindowsCreate(), gConnBLE = nullptr;
        return MDR_RESULT_OK;
    }

    void clientPlatformConnectionDestroy()
    {
        if (gConnClassic)
            mdrConnectionWindowsDestroy(gConnClassic), gConnClassic = nullptr;
        if (gConnBLE)
            mdrConnectionWindowsBLEDestroy(gConnBLE), gConnBLE = nullptr;
    }

    MDRConnection* clientPlatformConnectionGet()
    {
        if (gConnClassic)
            return mdrConnectionWindowsGet(gConnClassic);
        if (gConnBLE)
            return mdrConnectionWindowsBLEGet(gConnBLE);
        [[unlikely]] return nullptr;
    }

    int clientPlatformLocateFontBinary(const char** outData)
    {
        // Loads a system Japanese font for ImGui to merge with PlexSansIcon.
        // Buffer is malloc'd and ownership transfers to the ImGui font atlas.
        *outData = nullptr;
        const char* winDir = std::getenv("WINDIR");
        if (!winDir) winDir = "C:\\Windows";
        static const char* kCandidates[] = {
            "\\Fonts\\YuGothR.ttc",
            "\\Fonts\\meiryo.ttc",
            "\\Fonts\\msgothic.ttc",
        };
        for (const char* suffix : kCandidates) {
            std::string path = std::string(winDir) + suffix;
            FILE* f = std::fopen(path.c_str(), "rb");
            if (!f) continue;
            std::fseek(f, 0, SEEK_END);
            long size = std::ftell(f);
            std::fseek(f, 0, SEEK_SET);
            if (size > 0) {
                char* buf = static_cast<char*>(std::malloc(static_cast<size_t>(size)));
                if (buf) {
                    size_t n = std::fread(buf, 1, static_cast<size_t>(size), f);
                    std::fclose(f);
                    if (n == static_cast<size_t>(size)) {
                        *outData = buf;
                        return static_cast<int>(size);
                    }
                    std::free(buf);
                    continue;
                }
            }
            std::fclose(f);
        }
        return 0;
    }
    void clientPlatformDestroy()
    {
        clientPlatformConnectionDestroy();
        // TODO
    }
}
