#include <mdr-c/Platform/PlatformWindowsBLE.h>

extern "C" {
    MDRConnectionWindowsBLE* mdrConnectionWindowsBLECreate() { return nullptr; }
    MDRConnection* mdrConnectionWindowsBLEGet(MDRConnectionWindowsBLE*) { return nullptr; }
    void mdrConnectionWindowsBLEDestroy(MDRConnectionWindowsBLE*) {}
}
