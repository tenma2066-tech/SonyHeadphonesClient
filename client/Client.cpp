#include <ranges>
#include <algorithm>

#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui.h>
#include <imgui_internal.h>
#include <SDL3/SDL.h>

#include <mdr/Headphones.hpp>
#include <Platform/Platform.hpp>
#include "Fonts/PlexSansIcon.h"
#include "Platform/Platform.hpp"
#include "MaterialYouTheme.hpp"
#include "i18n/Localization.hpp"
using namespace mdr;

mdr::MDRHeadphones gDevice;
String gBugcheckMessage;

#pragma region Enum Names
const char* FormatEnum(v2::t1::AudioCodec codec)
{
    using enum v2::t1::AudioCodec;
    const char* key = "audio_codec.unknown";
    switch (codec)
    {
    case UNSETTLED: key = "audio_codec.unsettled"; break;
    case SBC:       key = "audio_codec.sbc"; break;
    case AAC:       key = "audio_codec.aac"; break;
    case LDAC:      key = "audio_codec.ldac"; break;
    case APT_X:     key = "audio_codec.aptx"; break;
    case APT_X_HD:  key = "audio_codec.aptx_hd"; break;
    case LC3:       key = "audio_codec.lc3"; break;
    default:
    case OTHER:     key = "audio_codec.unknown"; break;
    }
    return i18n::tr(key);
}

const char* FormatEnum(v2::t1::UpscalingType codec)
{
    using enum v2::t1::UpscalingType;
    const char* key = "dsee.unknown";
    switch (codec)
    {
    case DSEE_HX:       key = "dsee.hx"; break;
    case DSEE:          key = "dsee.dsee"; break;
    case DSEE_HX_AI:    key = "dsee.hx_ai"; break;
    case DSEE_ULTIMATE: key = "dsee.ultimate"; break;
    default:            key = "dsee.unknown"; break;
    }
    return i18n::tr(key);
}

const char* FormatEnum(v2::t1::BatteryChargingStatus status)
{
    using enum v2::t1::BatteryChargingStatus;
    const char* key = "battery.unknown";
    switch (status)
    {
    case CHARGING:     key = "battery.charging"; break;
    case CHARGED:      key = "battery.charged"; break;
    case NOT_CHARGING: key = "battery.not_charging"; break; // Hidden (empty string)
    default:
    case UNKNOWN:      key = "battery.unknown"; break;
    }
    return i18n::tr(key);
}

const char* FormatEnum(v2::t1::NoiseAdaptiveSensitivity status)
{
    using enum v2::t1::NoiseAdaptiveSensitivity;
    const char* key = "nc_sens.unknown";
    switch (status)
    {
    case STANDARD: key = "nc_sens.standard"; break;
    case HIGH:     key = "nc_sens.high"; break;
    case LOW:      key = "nc_sens.low"; break;
    default:       key = "nc_sens.unknown"; break;
    }
    return i18n::tr(key);
}

const char* FormatEnum(v2::t1::DetectSensitivity status)
{
    using enum v2::t1::DetectSensitivity;
    const char* key = "detect_sens.unknown";
    switch (status)
    {
    case AUTO: key = "detect_sens.auto"; break;
    case HIGH: key = "detect_sens.high"; break;
    case LOW:  key = "detect_sens.low"; break;
    default:   key = "detect_sens.unknown"; break;
    }
    return i18n::tr(key);
}

const char* FormatEnum(v2::t1::ModeOutTime status)
{
    using enum v2::t1::ModeOutTime;
    const char* key = "mode_out_time.unknown";
    switch (status)
    {
    case FAST: key = "mode_out_time.fast"; break;
    case MID:  key = "mode_out_time.mid"; break;
    case SLOW: key = "mode_out_time.slow"; break;
    case NONE: key = "mode_out_time.none"; break;
    default:   key = "mode_out_time.unknown"; break;
    }
    return i18n::tr(key);
}

const char* FormatEnum(v2::t1::EqPresetId id)
{
    using enum v2::t1::EqPresetId;
    const char* key = "eq.unknown";
    switch (id)
    {
    case OFF:             key = "eq.off"; break;
    case ROCK:            key = "eq.rock"; break;
    case POP:             key = "eq.pop"; break;
    case JAZZ:            key = "eq.jazz"; break;
    case DANCE:           key = "eq.dance"; break;
    case EDM:             key = "eq.edm"; break;
    case R_AND_B_HIP_HOP: key = "eq.rb_hiphop"; break;
    case ACOUSTIC:        key = "eq.acoustic"; break;
    case BRIGHT:          key = "eq.bright"; break;
    case EXCITED:         key = "eq.excited"; break;
    case MELLOW:          key = "eq.mellow"; break;
    case RELAXED:         key = "eq.relaxed"; break;
    case VOCAL:           key = "eq.vocal"; break;
    case TREBLE:          key = "eq.treble"; break;
    case BASS:            key = "eq.bass"; break;
    case SPEECH:          key = "eq.speech"; break;
    case CUSTOM:          key = "eq.custom"; break;
    case USER_SETTING1:   key = "eq.user1"; break;
    case USER_SETTING2:   key = "eq.user2"; break;
    case USER_SETTING3:   key = "eq.user3"; break;
    case USER_SETTING4:   key = "eq.user4"; break;
    case USER_SETTING5:   key = "eq.user5"; break;
    default:              key = "eq.unknown"; break;
    }
    return i18n::tr(key);
}

const char* FormatEnum(v2::t1::Preset preset)
{
    using enum v2::t1::Preset;
    const char* key = "preset.unknown";
    switch (preset)
    {
    case AMBIENT_SOUND_CONTROL:                       key = "preset.ambient_sound_control"; break;
    case VOLUME_CONTROL:                              key = "preset.volume_control"; break;
    case PLAYBACK_CONTROL:                            key = "preset.playback_control"; break;
    case TRACK_CONTROL:                               key = "preset.track_control"; break;
    case PLAYBACK_CONTROL_VOICE_ASSISTANT_LIMITATION: key = "preset.playback_control"; break;
    case VOICE_RECOGNITION:                           key = "preset.voice_recognition"; break;
    case GOOGLE_ASSIST:                               key = "preset.google_assist"; break;
    case AMAZON_ALEXA:                                key = "preset.amazon_alexa"; break;
    case TENCENT_XIAOWEI:                             key = "preset.tencent_xiaowei"; break;
    case AMBIENT_SOUND_CONTROL_QUICK_ACCESS:          key = "preset.ambient_sound_control"; break;
    case QUICK_ACCESS:                                key = "preset.quick_access"; break;
    case NO_FUNCTION:                                 key = "preset.no_function"; break;
    default:                                          key = "preset.unknown"; break;
    }
    return i18n::tr(key);
}

const char* FormatEnum(v2::t1::Function function)
{
    using enum v2::t1::Function;
    const char* key = "function.unknown";
    switch (function)
    {
    case NO_FUNCTION: key = "function.no_function"; break;
    case NC_ASM_OFF:  key = "function.nc_asm_off"; break;
    case NC_ASM:      key = "function.nc_asm"; break;
    case NC_OFF:      key = "function.nc_off"; break;
    case ASM_OFF:     key = "function.asm_off"; break;
    default:          key = "function.unknown"; break;
    }
    return i18n::tr(key);
}

const char* FormatEnum(v2::t1::AutoPowerOffElements off)
{
    using enum v2::t1::AutoPowerOffElements;
    const char* key = "auto_power_off.unknown";
    switch (off)
    {
    case POWER_OFF_IN_5_MIN:   key = "auto_power_off.5min"; break;
    case POWER_OFF_IN_15_MIN:  key = "auto_power_off.15min"; break;
    case POWER_OFF_IN_30_MIN:  key = "auto_power_off.30min"; break;
    case POWER_OFF_IN_60_MIN:  key = "auto_power_off.60min"; break;
    case POWER_OFF_IN_180_MIN: key = "auto_power_off.180min"; break;
    case POWER_OFF_DISABLE:    key = "auto_power_off.disable"; break;
    default:                   key = "auto_power_off.unknown"; break;
    }
    return i18n::tr(key);
}
#pragma endregion
#pragma region ImGui Extra
constexpr ImGuiWindowFlags kImWindowFlagsTopMost = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
    ImGuiWindowFlags_NoTitleBar;

// -- https://github.com/ocornut/imgui/issues/3379#issuecomment-2943903877
void ImScrollWhenDraggingOnVoid(const ImVec2& delta, ImGuiMouseButton mouse_button)
{
    using namespace ImGui;

    ImGuiContext& g = *GetCurrentContext();
    ImGuiWindow* window = g.CurrentWindow;
    ImGuiID id = window->GetID("##scrolldraggingoverlay");
    KeepAliveID(id);

    // Passing 0 to ItemHoverable means it doesn't set HoveredId, which is what we want.
    if (g.ActiveId == 0 && ItemHoverable(window->Rect(), 0, g.CurrentItemFlags) && IsMouseClicked(mouse_button, ImGuiInputFlags_None, id))
        SetActiveID(id, window);
    if (g.ActiveId == id && !g.IO.MouseDown[mouse_button])
        ClearActiveID();

    // Set keep underlying highlight. However, mouse not necessarily hovering same item creates a weird disconnect.
    //if (g.ActiveId == id)
    //    g.ActiveIdAllowOverlap = true;

    // if (g.ActiveId == id && delta.x != 0.0f)
    //     SetScrollX(window, window->Scroll.x + delta.x);
    if (g.ActiveId == id && delta.y != 0.0f)
        SetScrollY(window, window->Scroll.y - delta.y);
}

void ImScrollWhenDraggingAnywhere(const ImVec2& delta, ImGuiMouseButton mouse_button)
{
    ImGuiContext& g = *ImGui::GetCurrentContext();
    const bool backup_hovered_id_allow_overlap = g.HoveredIdAllowOverlap;
    g.HoveredIdAllowOverlap = true;
    ImScrollWhenDraggingOnVoid(delta, mouse_button);
    g.HoveredIdAllowOverlap = backup_hovered_id_allow_overlap; // As we know ScrollWhenDraggingOnVoid() doesn't changed HoveredId we can unconditionally restore.
}
// --

// Only useful if you're manipulating the DrawList which has positions
// that are _NOT_ window local
Tuple<ImVec2, ImVec2, ImDrawList*> ImWindowDrawOffsetRegionList()
{
    ImVec2 offset = ImGui::GetCursorScreenPos();
    ImVec2 region = ImGui::GetContentRegionAvail();
    ImDrawList* drawList = ImGui::GetWindowDrawList();
    return {offset, region, drawList};
}

// Centered text.
void ImTextCentered(const char* text)
{
    ImVec2 size = ImGui::CalcTextSize(text);
    ImGui::SetCursorPosX(ImGui::GetContentRegionAvail().x / 2 - size.x / 2 + ImGui::GetStyle().FramePadding.x);
    ImGui::Text("%s", text);
}

// Generate linear, monotonous ints of [0, count - 1] at interval of intervalMS
int ImBlink(int intervalMS, int count)
{
    size_t time = ImGui::GetTime() * 1000;
    time = time % (intervalMS * count);
    return time / intervalMS;
}

// Generate linear, monotonous float in range of [0, 1] at interval of intervalMS
float ImBlinkF(float intervalMS)
{
    float time = ImGui::GetTime();
    intervalMS /= 1000.0f;
    time = fmod(time, intervalMS);
    return time / intervalMS;
}

// CSS linear easing function on x of range [0,1]
constexpr float ImEaseLinear(float x)
{
    return x;
}

// CSS easeInOutCubic easing function on x of range [0,1]
constexpr float ImEaseInOutCubic(float x)
{
    return x < 0.5f ? 4 * pow(x, 3.0f) : 1.0f - pow(-2.0f * x + 2.0f, 3.0f) / 2.0f;
}

// Your next favourite spinner
void ImSpinner(float interval, float size, int color, float thickness = 1.0f, bool centerX = false, bool centerY = false,
               float cycles = 1.0f, float (*easing)(float) = ImEaseLinear)
{
    constexpr ImVec2 kPoints[] = {{-1, 1}, {-1, -1}, {1, -1}, {1, 1}};
    auto& style = ImGui::GetStyle();
    ImVec2 points[std::size(kPoints)];
    if (centerX)
        ImGui::SetCursorPosX(ImGui::GetContentRegionAvail().x / 2 - size / 2);
    if (centerY)
        ImGui::SetCursorPosY((ImGui::GetTextLineHeight() + style.FramePadding.y * 2 - size) / 2 );
    auto [offset, region, draw] = ImWindowDrawOffsetRegionList();
    float t = ImBlinkF(interval), theta = easing(t) * acos(-1) * cycles;
    for (int i = 0; auto p : kPoints)
    {
        auto& pp = points[i++] = {
            p.x * cos(theta) - p.y * sin(theta),
            p.x * sin(theta) + p.y * cos(theta),
        };
        pp *= size, pp += offset, pp.x += size, pp.y += size;
    }
    draw->AddPolyline(points, std::size(kPoints), color, ImDrawFlags_Closed, thickness);
    ImGui::Dummy({sqrt(2.0f) * size, sqrt(2.0f) * size + style.FramePadding.y * 2.0f});
}

// Fill the available horizontal region with lineTotal amount of buttons
// This is used for modal dialogues
bool ImModalButton(const char* label, int lineIndex = 0, int lineTotal = 1)
{
    MDR_CHECK(lineIndex < lineTotal);
    auto& style = ImGui::GetStyle();
    float padding = style.FramePadding.x;
    float width = ImGui::GetContentRegionAvail().x / lineTotal;
    if (lineIndex)
        ImGui::SameLine();
    return ImGui::Button(label, lineTotal > 1 ? ImVec2{width - padding, 0} : ImVec2{width, 0});
}

void ImSetNextWindowCentered()
{
    auto& style = ImGui::GetStyle();
    float padding = style.FramePadding.x;
    ImGui::SetNextWindowPos(
        {0.0f, ImGui::GetContentRegionAvail().y / 2 + padding},
        0, {0.0f, 0.5f}
        );
    ImGui::SetNextWindowSize({ImGui::GetIO().DisplaySize.x, 0});
}

void ImTextWithBorder(const char* text, int color, float rounding = 0.0f, float thickness = 1.0f)
{
    auto& style = ImGui::GetStyle();
    ImVec2 size = ImGui::CalcTextSize(text);
    auto [offset, region, draw] = ImWindowDrawOffsetRegionList();
    ImVec2 pad = style.FramePadding / 2;
    ImGui::Text("%s", text);
    offset.y += style.FramePadding.y;
    draw->AddRect(offset - pad, offset + size + pad, color, rounding, ImDrawFlags_None, thickness);
    ImGui::Dummy({pad.x, 0});
}

template <typename T>
void ImComboBoxItems(const char* label, Span<const T> items, T& selection)
{
    if (ImGui::BeginCombo(label, FormatEnum(selection)))
    {
        for (T const& i : items)
        {
            bool selected = i == selection;
            if (ImGui::Selectable(FormatEnum(i), selected))
                selection = i;
            if (selected)
                ImGui::SetItemDefaultFocus();
        }
        ImGui::EndCombo();
    }
}

void ImEqualizer(Span<int> bands)
{
    constexpr const char* kBand5[] = {"400", "1k", "2.5k", "6.3k", "16k"};
    constexpr const char* kBand10[] = {"31", "63", "125", "250", "500", "1k", "2k", "4k", "8k", "16k"};
    const char* const* kBands = nullptr;
    int numBands = static_cast<int>(bands.size());
    int mn = 0, mx = 0;
    if (numBands == 10)
        kBands = kBand10, mn = -6, mx = 6;
    if (numBands == 5)
        kBands = kBand5, mn = -10, mx = 10;
    if (!kBands)
        return ImGui::Text(i18n::tr("sound.eq_unavailable_fmt"), numBands);
    auto& style = ImGui::GetStyle();
    float padding = style.FramePadding.x;
    auto [offset, region, draw] = ImWindowDrawOffsetRegionList();
    float bandWidth = region.x / numBands - padding;
    float bandHeight = std::max(region.y, 160.0f);
    if (numBands == 5)
        ImGui::SeparatorText(i18n::tr("sound.eq_5band"));
    if (numBands == 10)
        ImGui::SeparatorText(i18n::tr("sound.eq_10band"));
    for (int i = 0; i < numBands; ++i)
    {
        ImGui::BeginGroup();
        ImGui::PushID(i);
        ImGui::VSliderInt("##v", ImVec2{bandWidth, bandHeight}, &bands[i], mn, mx);
        ImGui::PopID();

        float textWidth = ImGui::CalcTextSize(kBands[i]).x;
        float textOffset = (bandWidth - textWidth) * 0.5f;
        if (textOffset > 0.0f)
            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + textOffset);
        ImGui::TextUnformatted(kBands[i]);

        ImGui::EndGroup();
        if (i != numBands - 1)
            ImGui::SameLine(0.0f, padding);
    }
}
struct ImStylesRAII
{
    size_t numVars = 0, numColors = 0, numFonts = 0;
    template <typename... Args>
    void PushVar(ImGuiStyleVar idx, Args&&... args) { ImGui::PushStyleVar(idx, args...), numVars++; }
    template <typename... Args>
    void PushCol(ImGuiCol idx, Args&&... args) { ImGui::PushStyleColor(idx, args...), numColors++; }
    template <typename... Args>
    void PushFont(ImFont* font, Args&&... args) { ImGui::PushFont(font, args...), numFonts++; }
    ~ImStylesRAII()
    {
        ImGui::PopStyleVar(numVars);
        ImGui::PopStyleColor(numColors);
        while (numFonts--)
            ImGui::PopFont();
    }
};
#pragma endregion

#pragma region States
enum
{
    APP_STATE_RUNNING,
    APP_STATE_BUGCHECK
} appState{APP_STATE_RUNNING};

enum
{
    CONN_STATE_NO_CONNECTION,
    CONN_STATE_CONNECTING,
    CONN_STATE_CONNECTED,
    CONN_STATE_DISCONNECTED
} connState{CONN_STATE_NO_CONNECTION};
#pragma endregion

void ExceptionHandler(auto&& func)
{
    try
    {
        func();
    }
    catch (const std::runtime_error& exc)
    {
        gBugcheckMessage = exc.what();
        appState = APP_STATE_BUGCHECK;
    }
}

void DrawDeviceDiscovery()
{
    MDR_CHECK(connState == CONN_STATE_NO_CONNECTION);
    ImSetNextWindowCentered();
    static bool popup = false;
    if (!popup)
        ImGui::OpenPopup("DeviceDiscovery"), popup = true;
    if (ImGui::BeginPopupModal("DeviceDiscovery", nullptr, kImWindowFlagsTopMost))
    {
        static MDRDeviceInfo* pDeviceInfo = nullptr;
        static int nDeviceInfo = 0;
        ImGui::PushFont(nullptr, ImGui::GetContentRegionAvail().x * 0.05f);
        ImTextCentered("SonyHeadphonesClient");
        ImGui::PopFont();
        ImTextCentered(fmt::format(fmt::runtime(i18n::tr("discovery.version_fmt")), CLIENT_VERSION, MDR_GIT_BRANCH_NAME, MDR_GIT_COMMIT_HASH, MDR_PLATFORM_OS).c_str());
        // Chose, and have the GATT backend active
        static bool usingBLE = false;
        static int connInitResult = MDR_RESULT_INPROGRESS;
        // BLE / Classic toggle
        bool needSwitchClientPlatform = clientPlatformConnectionGet() == nullptr;
        {
            ImStylesRAII styles;
            styles.PushFont(nullptr, 12.0f);
            styles.PushVar(ImGuiStyleVar_FramePadding,ImVec2{});
            styles.PushVar(ImGuiStyleVar_FrameRounding, 0.0f);
            {
                ImStylesRAII styles;
                if (usingBLE)
                    styles.PushCol(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
                if (ImModalButton(i18n::trIcon(PSI_BLUETOOTH, "discovery.classic").c_str(), 0, 2))
                    usingBLE = false, needSwitchClientPlatform = true;
            }
            {
                ImStylesRAII styles;
                if (!usingBLE)
                    styles.PushCol(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
                if (ImModalButton(i18n::trIcon(PSI_BLUETOOTH_ALT, "discovery.ble_gatt").c_str(), 1, 2))
                    usingBLE = true, needSwitchClientPlatform = true;
            }
        }
        auto RefreshDeviceList = [&]()
        {
            MDRConnection* conn = clientPlatformConnectionGet();
            if (conn) // TODO: Error modals
                mdrConnectionGetDevicesList(conn, &pDeviceInfo, &nDeviceInfo);
        };
        if (needSwitchClientPlatform)
        {
            int flags = 0;
            if (usingBLE) flags |= MDR_INIT_BT_BLE;
            MDRConnection* conn = clientPlatformConnectionGet();
            if (conn && pDeviceInfo)
                mdrConnectionFreeDevicesList(conn, &pDeviceInfo), pDeviceInfo = nullptr, nDeviceInfo = 0;
            clientPlatformConnectionDestroy();
            connInitResult = clientPlatformConnectionInit(flags);
            RefreshDeviceList();
        }
        auto DrawDeviceList = [&]()
        {
            ImGui::SeparatorText(i18n::tr("discovery.available_devices"));
            static int deviceIndex = 0;
            Span<MDRDeviceInfo> devices{pDeviceInfo, static_cast<size_t>(nDeviceInfo)};
            if (!devices.empty())
            {
                int btnIndex = 0;
                for (const auto& device : devices)
                {
                    ImGui::PushID(device.szDeviceMacAddress);
                    ImGui::RadioButton(device.szDeviceName, &deviceIndex, btnIndex++);
                    ImGui::PopID();
                }
            } else
            {
                ImGui::TextWrapped("%s", i18n::trIcon(PSI_WARNING_SIGN, "discovery.no_devices").c_str());
            }
            ImGui::BeginDisabled(devices.empty());
            if (ImModalButton(i18n::trIcon(PSI_LINK, "discovery.connect").c_str(), 0, 2))
            {
                const char* serviceUUID = usingBLE ? MDR_BLE_SERVICE_UUID_TANDEM_OVER_BLE_HPC : MDR_SERVICE_UUID_XM5;
                int res = mdrConnectionConnect(clientPlatformConnectionGet(), devices[deviceIndex].szDeviceMacAddress, serviceUUID);
                if (res != MDR_RESULT_OK && res != MDR_RESULT_INPROGRESS)
                    connState = CONN_STATE_DISCONNECTED;
                else
                    connState = CONN_STATE_CONNECTING;
            }
            ImGui::EndDisabled();
            if (ImModalButton(i18n::trIcon(PSI_REFRESH, "discovery.refresh").c_str(), 1, 2))
                RefreshDeviceList();
        };
        if (connInitResult != MDR_RESULT_OK && connInitResult != MDR_RESULT_INPROGRESS)
        {
            ImTextCentered(fmt::format(fmt::runtime(i18n::trIcon(PSI_EXCLAMATION_SIGN, "discovery.init_failed")), mdrResultString(connInitResult)).c_str());
        }
        DrawDeviceList();
        ImGui::SeparatorText(i18n::trIcon(PSI_INFO_SIGN_ALT, "discovery.bt_select_hint").c_str());
        ImTextCentered((std::string(PSI_WARNING_SIGN) + i18n::tr("discovery.disclaimer") + PSI_WARNING_SIGN).c_str());
        ImGui::EndPopup();
    } else
        popup = false;
}

void DrawDeviceConnecting()
{
    MDR_CHECK(connState == CONN_STATE_CONNECTING);
    MDRConnection* conn = clientPlatformConnectionGet();
    switch (mdrConnectionPoll(conn, 0))
    {
    case MDR_RESULT_OK:
        connState = CONN_STATE_CONNECTED;
        gDevice = mdr::MDRHeadphones(conn);
        // Do an init - this should always be possible when @ref MDRHeadphones
        // is first created.
        MDR_CHECK(gDevice.Invoke(gDevice.RequestInitV2()) == MDR_RESULT_OK);
        return;
    case MDR_RESULT_ERROR_TIMEOUT:
    case MDR_RESULT_INPROGRESS:
    {
        ImSetNextWindowCentered();
        static bool popup = false;
        if (!popup)
            ImGui::OpenPopup("Connection"), popup = true;
        if (ImGui::BeginPopupModal("Connection", nullptr, kImWindowFlagsTopMost))
        {
            ImGui::NewLine();
            ImTextCentered(i18n::tr("connecting.title"));
            ImGui::Dummy({0, 16.0f});
            ImSpinner(1000.0f, 24.0f, MaterialYouTheme::ArgbToImU32(MaterialYouTheme::FixedSurfaceColors::onSurface), 2.0f, true, false, 2.0f, ImEaseInOutCubic);
            ImGui::NewLine();
            ImTextCentered(mdrConnectionGetLastError(conn));
            ImGui::NewLine();
            if (ImModalButton(i18n::trIcon(PSI_REMOVE, "connecting.cancel").c_str()))
            {
                mdrConnectionDisconnect(conn);
                connState = CONN_STATE_NO_CONNECTION;
            }
            ImGui::EndPopup();
        } else
            popup = false;
        return;
    }
    default:
    {
        connState = CONN_STATE_DISCONNECTED;
        mdrConnectionDisconnect(conn);
        MaterialYouTheme::ApplyDefault();
        break;
    }
    }
}

void DrawDeviceControlsHeader()
{
    MDRConnection* conn = clientPlatformConnectionGet();
    if (ImGui::BeginMenuBar())
    {
        auto& style = ImGui::GetStyle();
        /* Disconnect & Shutdown */
        if (ImGui::BeginMenu(fmt::format( PSI_CHEVRON_DOWN " {}", gDevice.mModelName).c_str()))
        {
            if (ImGui::MenuItem(i18n::trIcon(PSI_UNLINK, "header.disconnect").c_str()))
            {
                mdrConnectionDisconnect(conn);
                connState = CONN_STATE_NO_CONNECTION;
            }
            if (gDevice.mSupport.contains(v2::MessageMdrV2FunctionType_Table1::POWER_OFF))
            {
                if (ImGui::MenuItem(i18n::trIcon(PSI_OFF, "header.shutdown").c_str()))
                    gDevice.mShutdown.desired = true;
            }
            ImGui::EndMenu();
        }
        if (!gDevice.IsReady())
            ImSpinner(1000, style.FontSizeBase * 0.5f, MaterialYouTheme::ArgbToImU32(MaterialYouTheme::FixedSurfaceColors::onSurface, 0.5f), 2.0f, false, true, 1.0f, ImEaseInOutCubic);
        /* Cool Badges */
        // Title, Border Color, Text Color
        using Badge = Tuple<const char*, int, int>;
        Array<Badge, 4> badges4;
        Badge *badgeFirst = &badges4[0], *badgeLast = &badges4[0];
        /* Codec */
        if (gDevice.mSupport.contains(v2::MessageMdrV2FunctionType_Table1::CODEC_INDICATOR))
        {
            *(badgeLast++) = {FormatEnum(gDevice.mAudioCodec), ~0u, ~0u};
        }
        /* DSEE */
        if (gDevice.mUpscalingEnabled.current)
        {
            *(badgeLast++) = {FormatEnum(gDevice.mUpscalingType), ~0u, ~0u};
        }
        Span<Badge> badges{badgeFirst, static_cast<size_t>(badgeLast - badgeFirst)};
        // Right-align and draw them
        // XXX: This is surprisingly painful to do.
        ImVec2 padding = style.FramePadding;
        float badgeRegionX = 0, badgeRegionY = 0;
        ImGui::PushFont(ImGui::GetFont(), style.FontSizeBase - padding.y / 2);
        for (auto& [s, border, text] : badges)
        {
            ImVec2 size = ImGui::CalcTextSize(s);
            badgeRegionX += size.x + padding.x * 2, badgeRegionY = std::max(badgeRegionY, size.y);
        }
        ImGui::SameLine(ImGui::GetCursorPosX() + ImGui::GetContentRegionAvail().x - badgeRegionX);
        float rounding = style.FrameRounding;
        float offsetY = padding.y / 2;
        for (auto& [s, border, text] : badges)
        {
            ImGui::SetCursorPosY(offsetY);
            ImTextWithBorder(s, border, rounding, 2.0f);
        }
        ImGui::PopFont();
        ImGui::EndMenuBar();
    }
    // Stats
    if (ImGui::BeginTable("##Stats", 2, ImGuiTableFlags_SizingStretchSame | ImGuiTableFlags_Resizable))
    {
        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);
        /* Batteries */
        {
            bool supportSingle = gDevice.mSupport.
                                         contains(v2::MessageMdrV2FunctionType_Table1::BATTERY_LEVEL_INDICATOR);
            supportSingle |= gDevice.mSupport.contains(
                v2::MessageMdrV2FunctionType_Table1::BATTERY_LEVEL_WITH_THRESHOLD);
            bool supportLR = gDevice.mSupport.contains(
                v2::MessageMdrV2FunctionType_Table1::LEFT_RIGHT_BATTERY_LEVEL_INDICATOR);
            supportLR |= gDevice.mSupport.
                                 contains(v2::MessageMdrV2FunctionType_Table1::LR_BATTERY_LEVEL_WITH_THRESHOLD);
            bool supportCase = gDevice.mSupport.contains(
                v2::MessageMdrV2FunctionType_Table1::CRADLE_BATTERY_LEVEL_INDICATOR);
            supportCase |= gDevice.mSupport.contains(
                v2::MessageMdrV2FunctionType_Table1::CRADLE_BATTERY_LEVEL_WITH_THRESHOLD);
            if (ImGui::BeginTable("##Battery", 2, ImGuiTableFlags_SizingStretchProp))
            {
                if (supportSingle && !supportLR && gDevice.mBatteryL.threshold)
                {
                    ImGui::TableNextRow();
                    Uint32 single = gDevice.mBatteryL.level;
                    ImGui::TableSetColumnIndex(0);
                    ImGui::Text(i18n::tr("header.battery_fmt"), single);
                    ImGui::TableSetColumnIndex(1);
                    ImGui::ProgressBar(single / 100.0f, {-1, 0}, FormatEnum(gDevice.mBatteryL.charging));
                }
                if (supportLR && gDevice.mBatteryL.threshold && gDevice.mBatteryR.threshold)
                {
                    Uint32 single = gDevice.mBatteryL.level;
                    ImGui::TableNextRow();
                    ImGui::TableSetColumnIndex(0);
                    ImGui::Text(i18n::tr("header.battery_l_fmt"), single);
                    ImGui::TableSetColumnIndex(1);
                    ImGui::ProgressBar(single / 100.0f, {-1, 0}, FormatEnum(gDevice.mBatteryL.charging));
                    single = gDevice.mBatteryR.level;
                    ImGui::TableNextRow();
                    ImGui::TableSetColumnIndex(0);
                    ImGui::Text(i18n::tr("header.battery_r_fmt"), single);
                    ImGui::TableSetColumnIndex(1);
                    ImGui::ProgressBar(single / 100.0f, {-1, 0}, FormatEnum(gDevice.mBatteryR.charging));
                }
                if (supportCase && gDevice.mBatteryCase.threshold)
                {
                    Uint32 single = gDevice.mBatteryCase.level;
                    ImGui::TableNextRow();
                    ImGui::TableSetColumnIndex(0);
                    ImGui::Text(i18n::tr("header.battery_case_fmt"), single);
                    ImGui::TableSetColumnIndex(1);
                    ImGui::ProgressBar(single / 100.0f, {-1, 0}, FormatEnum(gDevice.mBatteryCase.charging));
                }
                ImGui::EndTable();
            }
        }
        ImGui::TableSetColumnIndex(1);
        /* Now Playing */
        {
            ImGui::Text("%s", i18n::trIcon(PSI_VOLUME_UP, "header.now_playing").c_str());
            if (ImGui::BeginTable("##NowPlaying", 2, ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_BordersInnerH))
            {
                ImGui::TableNextRow();
                ImGui::TableSetColumnIndex(0);
                ImGui::Text("%s", i18n::tr("header.now_playing_title"));
                ImGui::TableSetColumnIndex(1);
                ImGui::Text("%s", gDevice.mPlayTrackTitle.c_str());
                ImGui::TableNextRow();
                ImGui::TableSetColumnIndex(0);
                ImGui::Text("%s", i18n::tr("header.now_playing_album"));
                ImGui::TableSetColumnIndex(1);
                ImGui::Text("%s", gDevice.mPlayTrackAlbum.c_str());
                ImGui::TableNextRow();
                ImGui::TableSetColumnIndex(0);
                ImGui::Text("%s", i18n::tr("header.now_playing_artist"));
                ImGui::TableSetColumnIndex(1);
                ImGui::Text("%s", gDevice.mPlayTrackArtist.c_str());
                ImGui::EndTable();
            }
        }
        ImGui::EndTable();
    }
}

void DrawDeviceControlsPlayback()
{
    using enum v2::t1::PlaybackControl;
    ImGui::SeparatorText(i18n::tr("playback.volume"));
    ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
    ImGui::SliderInt("##Volume", &gDevice.mPlayVolume.desired, 0, 30);
    ImGui::SeparatorText(i18n::tr("playback.controls"));
    if (ImModalButton(i18n::trIcon(PSI_STEP_BACKWARD, "playback.prev").c_str(), 0, 3))
        gDevice.mPlayControl.desired = TRACK_DOWN;
    if (gDevice.mPlayPause == v2::t1::PlaybackStatus::PLAY)
    {
        if (ImModalButton(i18n::trIcon(PSI_PAUSE, "playback.pause").c_str(), 1, 3))
            gDevice.mPlayControl.desired = PAUSE;
    }
    else
    {
        if (ImModalButton(i18n::trIcon(PSI_PLAY, "playback.play").c_str(), 1, 3))
            gDevice.mPlayControl.desired = PLAY;
    }
    if (ImModalButton(i18n::trIcon(PSI_STEP_FORWARD, "playback.next").c_str(), 2, 3))
        gDevice.mPlayControl.desired = TRACK_UP;
}

void DrawDeviceControlsSound()
{
    using F1 = v2::MessageMdrV2FunctionType_Table1;
    constexpr auto kSupports = [](auto x) { return gDevice.mSupport.contains(x); };
    bool supportNC = kSupports(F1::NOISE_CANCELLING_ONOFF)
        || kSupports(F1::NOISE_CANCELLING_ONOFF_AND_AMBIENT_SOUND_MODE_ONOFF)
        || kSupports(F1::NOISE_CANCELLING_DUAL_SINGLE_OFF_AND_AMBIENT_SOUND_MODE_ONOFF)
        || kSupports(F1::NOISE_CANCELLING_ONOFF_AND_AMBIENT_SOUND_MODE_LEVEL_ADJUSTMENT)
        || kSupports(F1::NOISE_CANCELLING_DUAL_SINGLE_OFF_AMBIENT_SOUND_MODE_LEVEL_ADJUSTMENT)
        || kSupports(F1::MODE_NC_ASM_NOISE_CANCELLING_DUAL_AUTO_AMBIENT_SOUND_MODE_LEVEL_ADJUSTMENT)
        || kSupports(F1::MODE_NC_ASM_NOISE_CANCELLING_DUAL_SINGLE_AMBIENT_SOUND_MODE_LEVEL_ADJUSTMENT)
        || kSupports(F1::MODE_NC_ASM_NOISE_CANCELLING_DUAL_AMBIENT_SOUND_MODE_LEVEL_ADJUSTMENT)
        || kSupports(F1::MODE_NC_NCSS_ASM_NOISE_CANCELLING_DUAL_AMBIENT_SOUND_MODE_LEVEL_ADJUSTMENT_WITH_TEST_MODE)
        || kSupports(F1::MODE_NC_ASM_NOISE_CANCELLING_DUAL_AMBIENT_SOUND_MODE_LEVEL_ADJUSTMENT_NOISE_ADAPTATION);
    bool supportASM = kSupports(F1::NOISE_CANCELLING_ONOFF_AND_AMBIENT_SOUND_MODE_ONOFF)
        || kSupports(F1::NOISE_CANCELLING_DUAL_SINGLE_OFF_AND_AMBIENT_SOUND_MODE_ONOFF)
        || kSupports(F1::NOISE_CANCELLING_ONOFF_AND_AMBIENT_SOUND_MODE_LEVEL_ADJUSTMENT)
        || kSupports(F1::NOISE_CANCELLING_DUAL_SINGLE_OFF_AMBIENT_SOUND_MODE_LEVEL_ADJUSTMENT)
        || kSupports(F1::AMBIENT_SOUND_MODE_ONOFF)
        || kSupports(F1::AMBIENT_SOUND_MODE_LEVEL_ADJUSTMENT)
        || kSupports(F1::MODE_NC_ASM_NOISE_CANCELLING_DUAL_AUTO_AMBIENT_SOUND_MODE_LEVEL_ADJUSTMENT)
        || kSupports(F1::AMBIENT_SOUND_CONTROL_MODE_SELECT)
        || kSupports(F1::MODE_NC_ASM_NOISE_CANCELLING_DUAL_SINGLE_AMBIENT_SOUND_MODE_LEVEL_ADJUSTMENT)
        || kSupports(F1::MODE_NC_ASM_NOISE_CANCELLING_DUAL_AMBIENT_SOUND_MODE_LEVEL_ADJUSTMENT)
        || kSupports(F1::MODE_NC_NCSS_ASM_NOISE_CANCELLING_DUAL_AMBIENT_SOUND_MODE_LEVEL_ADJUSTMENT_WITH_TEST_MODE)
        || kSupports(F1::MODE_NC_ASM_NOISE_CANCELLING_DUAL_AMBIENT_SOUND_MODE_LEVEL_ADJUSTMENT_NOISE_ADAPTATION);
    bool supportAutoASM = kSupports(
        F1::MODE_NC_ASM_NOISE_CANCELLING_DUAL_AMBIENT_SOUND_MODE_LEVEL_ADJUSTMENT_NOISE_ADAPTATION);
    using enum v2::t1::NcAsmMode;
    /* NC/ASM */
    if (supportASM || supportNC)
    {
        if (ImGui::TreeNodeEx(i18n::tr("sound.ambient_sound"), ImGuiTreeNodeFlags_DefaultOpen))
        {
            if (supportNC)
            {
                if (ImGui::RadioButton(
                    i18n::tr("sound.noise_cancelling"),
                    gDevice.mNcAsmEnabled.current && (!supportASM || gDevice.mNcAsmMode.desired == NC))
                )
                {
                    gDevice.mNcAsmEnabled.desired = true;
                    gDevice.mNcAsmMode.desired = NC;
                }
                ImGui::SameLine();
            }
            if (supportASM)
            {
                if (ImGui::RadioButton(
                    i18n::tr("sound.ambient_sound"),
                    gDevice.mNcAsmEnabled.current && (!supportNC || gDevice.mNcAsmMode.desired == ASM))
                )
                {
                    gDevice.mNcAsmEnabled.desired = true;
                    gDevice.mNcAsmMode.desired = ASM;
                    if (gDevice.mNcAsmAmbientLevel.desired == 0)
                        gDevice.mNcAsmAmbientLevel.desired = 20;
                }
                ImGui::SameLine();
            }
            if (ImGui::RadioButton(i18n::tr("common.off"), !gDevice.mNcAsmEnabled.desired))
                gDevice.mNcAsmEnabled.desired = false;
            ImGui::SeparatorText(i18n::tr("sound.ambient_strength"));
            ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
            ImGui::SliderInt("##AmbStrength", &gDevice.mNcAsmAmbientLevel.desired, 1, 20);
            if (supportAutoASM)
            {
                ImGui::Checkbox(i18n::tr("sound.auto_ambient_sound"), &gDevice.mNcAsmAutoAsmEnabled.desired);
                ImGui::BeginDisabled(!gDevice.mNcAsmAutoAsmEnabled.desired);
                using enum v2::t1::NoiseAdaptiveSensitivity;
                auto& desired = gDevice.mNcAsmNoiseAdaptiveSensitivity.desired;
                constexpr v2::t1::NoiseAdaptiveSensitivity kSelections[] = {STANDARD, HIGH, LOW};
                ImComboBoxItems<v2::t1::NoiseAdaptiveSensitivity>(i18n::tr("common.sensitivity"), kSelections, desired);
                ImGui::EndDisabled();
            }
            ImGui::Checkbox(i18n::tr("sound.voice_passthrough"), &gDevice.mNcAsmFocusOnVoice.desired);
            ImGui::TreePop();
        }
    }
    /* STC */
    if (kSupports(F1::SMART_TALKING_MODE_TYPE2))
    {
        if (ImGui::TreeNodeEx(i18n::tr("sound.speak_to_chat"), ImGuiTreeNodeFlags_DefaultOpen))
        {
            ImGui::Checkbox(i18n::tr("common.enabled"), &gDevice.mSpeakToChatEnabled.desired);
            ImGui::BeginDisabled(!gDevice.mSpeakToChatEnabled.desired);
            {
                using enum v2::t1::DetectSensitivity;
                constexpr v2::t1::DetectSensitivity kSelections[] = {AUTO, HIGH, LOW};
                ImComboBoxItems<v2::t1::DetectSensitivity>(i18n::tr("common.sensitivity"), kSelections,
                                                           gDevice.mSpeakToChatDetectSensitivity.desired);
            }
            {
                using enum v2::t1::ModeOutTime;
                constexpr v2::t1::ModeOutTime kSelections[] = {FAST, MID, SLOW, NONE};
                ImComboBoxItems<v2::t1::ModeOutTime>(i18n::tr("sound.mode_duration"), kSelections,
                                                     gDevice.mSpeakToModeOutTime.desired);
            }
            ImGui::EndDisabled();
            ImGui::TreePop();
        }
    }
    /* Listening Mode */
    if (kSupports(F1::LISTENING_OPTION))
    {
        if (ImGui::TreeNodeEx(i18n::tr("sound.listening_mode"), ImGuiTreeNodeFlags_DefaultOpen))
        {
            // Derive effective mode from current state
            bool bgmActive    = gDevice.mBGMModeEnabled.current;
            bool cinemaActive = gDevice.mUpmixCinemaEnabled.current;

            // 0 = Standard, 1 = BGM, 2 = Cinema
            int effectiveMode = bgmActive ? 1 : (cinemaActive ? 2 : 0);

            bool radioChanged = false;
            if (ImGui::RadioButton(i18n::tr("nc_sens.standard"), effectiveMode == 0))
                radioChanged = true, effectiveMode = 0;
            if (ImGui::RadioButton(i18n::tr("sound.bgm"), effectiveMode == 1))
                radioChanged = true, effectiveMode = 1;

            ImGui::Indent();
            ImGui::BeginDisabled(!bgmActive);
            // Distance combo box
            using namespace v2::t1;
            static const std::pair<RoomSize, const char*> kBGMDistanceModes[] = {
                { RoomSize::SMALL,  "sound.my_room"     },
                { RoomSize::MIDDLE, "sound.living_room" },
                { RoomSize::LARGE,  "sound.cafe"        },
            };
            const char* currentDistKey = "common.unknown_brackets";
            for (auto const& [k, v] : kBGMDistanceModes)
                if (k == gDevice.mBGMModeRoomSize.current)
                    currentDistKey = v;
            if (ImGui::BeginCombo(i18n::tr("sound.distance"), i18n::tr(currentDistKey)))
            {
                for (auto const& [k, v] : kBGMDistanceModes)
                {
                    bool is_selected = k == gDevice.mBGMModeRoomSize.desired;
                    if (ImGui::Selectable(i18n::tr(v), is_selected))
                        gDevice.mBGMModeRoomSize.desired = k;
                    if (is_selected)
                        ImGui::SetItemDefaultFocus();
                }
                ImGui::EndCombo();
            }
            ImGui::EndDisabled();
            ImGui::Unindent();

            if (ImGui::RadioButton(i18n::tr("sound.cinema"), effectiveMode == 2))
                radioChanged = true, effectiveMode = 2;

            if (radioChanged)
            {
                gDevice.mBGMModeEnabled.desired     = (effectiveMode == 1);
                gDevice.mUpmixCinemaEnabled.desired = (effectiveMode == 2);
            }

            ImGui::TreePop();
        }
    }
    /* EQ & DSEE */
    if (ImGui::TreeNodeEx(i18n::tr("sound.eq_dsee"), ImGuiTreeNodeFlags_DefaultOpen))
    {
        using enum v2::t1::EqPresetId;
        constexpr v2::t1::EqPresetId kSelections[] = {
            OFF, ROCK, POP, JAZZ, DANCE, EDM, R_AND_B_HIP_HOP, ACOUSTIC, BRIGHT, EXCITED,
            MELLOW, RELAXED, VOCAL, TREBLE, BASS, SPEECH,
            CUSTOM, USER_SETTING1, USER_SETTING2, USER_SETTING3, USER_SETTING4, USER_SETTING5
        };
        ImComboBoxItems<v2::t1::EqPresetId>(i18n::tr("sound.preset"), kSelections, gDevice.mEqPresetId.desired);
        ImEqualizer(gDevice.mEqConfig.desired);
        if (gDevice.mEqConfig.desired.size() == 5)
        {
            ImGui::SeparatorText(i18n::tr("sound.clear_bass"));
            ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
            ImGui::SliderInt("##", &gDevice.mEqClearBass.desired, -10, 10);
        }
        ImGui::SeparatorText(i18n::tr("sound.dsee"));
        ImGui::BeginDisabled(!gDevice.mUpscalingAvailable);
        if (ImGui::RadioButton(i18n::tr("common.off"), gDevice.mUpscalingEnabled.desired == false))
            gDevice.mUpscalingEnabled.desired = false;
        if (ImGui::RadioButton(i18n::tr("sound.dsee_on_auto"), gDevice.mUpscalingEnabled.desired == true))
            gDevice.mUpscalingEnabled.desired = true;
        ImGui::EndDisabled();
        ImGui::TreePop();
    }
}

void DrawDeviceControlsDevices()
{
    using F2 = v2::MessageMdrV2FunctionType_Table2;
    constexpr auto kSupports = [](auto x) { return gDevice.mSupport.contains(x); };
    bool supportDeviceMgmt = kSupports(F2::PAIRING_DEVICE_MANAGEMENT_CLASSIC_BT)
        || kSupports(F2::PAIRING_DEVICE_MANAGEMENT_WITH_BLUETOOTH_CLASS_OF_DEVICE_CLASSIC_BT)
        || kSupports(F2::PAIRING_DEVICE_MANAGEMENT_WITH_BLUETOOTH_CLASS_OF_DEVICE_CLASSIC_LE);
    if (!supportDeviceMgmt)
        ImGui::Text("%s", i18n::tr("devices.need_multipoint"));
    ImGui::BeginDisabled(!supportDeviceMgmt);
    auto DrawDeviceElement = [&](const mdr::MDRHeadphones::PeripheralDevice& device, bool selected) -> bool
    {
        ImGui::BeginGroup();
        if (device.macAddress == gDevice.mMultipointDeviceMac.current)
            ImGui::Text(PSI_VOLUME_DOWN " "), ImGui::SameLine();
        bool res = ImGui::Selectable(device.name.c_str(), selected);
        if (selected)
        {
            ImGui::Separator();
            if (device.connected)
            {
                if (ImModalButton(i18n::trIcon(PSI_UNLINK, "devices.disconnect").c_str(), 0, 2))
                    gDevice.mPairedDeviceDisconnectMac.desired = device.macAddress;
                if (res)
                    gDevice.mMultipointDeviceMac.desired = device.macAddress;
            }
            else
            {
                if (ImModalButton(i18n::trIcon(PSI_LINK, "devices.connect").c_str(), 0, 2))
                    gDevice.mPairedDeviceConnectMac.desired = device.macAddress;
            }
            if (ImModalButton(i18n::trIcon(PSI_BLUETOOTH_ALT, "devices.unpair").c_str(), 1, 2))
                gDevice.mPairedDeviceUnpairMac.desired = device.macAddress;
        }
        ImGui::EndGroup();
        return res;
    };
    auto devices = std::views::all(gDevice.mPairedDevices);
    auto connectedDevices = devices | std::views::filter([](auto const& x) { return x.connected; });
    auto unconncetedDevices = devices | std::views::filter([](auto const& x) { return !x.connected; });
    static String connectSelectedMac;
    if (ImGui::TreeNodeEx(i18n::tr("devices.connected"), ImGuiTreeNodeFlags_DefaultOpen))
    {
        for (auto& device : connectedDevices)
            if (DrawDeviceElement(device, connectSelectedMac == device.macAddress))
                connectSelectedMac = connectSelectedMac == device.macAddress ? "" : device.macAddress;
        ImGui::TreePop();
    }
    if (ImGui::TreeNodeEx(i18n::tr("devices.paired"), ImGuiTreeNodeFlags_DefaultOpen))
    {
        for (auto& device : unconncetedDevices)
            if (DrawDeviceElement(device, connectSelectedMac == device.macAddress))
                connectSelectedMac = connectSelectedMac == device.macAddress ? "" : device.macAddress;
        ImGui::TreePop();
    }
    if (gDevice.mPairingMode.desired)
    {
        ImTextCentered(i18n::tr("devices.pairing"));
        ImSpinner(1000.0f, 16.0f, MaterialYouTheme::ArgbToImU32(MaterialYouTheme::ThemeForModelColor(static_cast<uint8_t>(gDevice.mModelColor)).primary), 2.0f, true, false, 1.0f, ImEaseInOutCubic);
        if (ImModalButton(i18n::tr("devices.stop")))
            gDevice.mPairingMode.desired = false;
    }
    else
    {
        if (ImModalButton(i18n::trIcon(PSI_BLUETOOTH, "devices.enter_pairing_mode").c_str()))
            gDevice.mPairingMode.desired = true;
        ImGui::TextWrapped("%s", i18n::trIcon(PSI_INFO_SIGN_ALT, "devices.tws_hint").c_str());
    }
    ImGui::EndDisabled();
}

void DrawDeviceControlsSystem()
{
    using F1 = v2::MessageMdrV2FunctionType_Table1;
    constexpr auto kSupports = [](auto x) { return gDevice.mSupport.contains(x); };
    /* Language */
    {
        if (ImGui::TreeNodeEx(i18n::tr("system.language"), ImGuiTreeNodeFlags_DefaultOpen))
        {
            static const std::pair<i18n::Locale, const char*> kLanguages[] = {
                { i18n::Locale::English,  "English" },
                { i18n::Locale::Japanese, "日本語" },
            };
            auto current = i18n::GetLocale();
            const char* currentLabel = "?";
            for (auto const& [loc, lbl] : kLanguages)
                if (loc == current) currentLabel = lbl;
            if (ImGui::BeginCombo(i18n::tr("system.language"), currentLabel))
            {
                for (auto const& [loc, lbl] : kLanguages)
                {
                    bool sel = loc == current;
                    if (ImGui::Selectable(lbl, sel))
                    {
                        i18n::SetLocale(loc);
                        i18n::SaveSettings();
                    }
                    if (sel) ImGui::SetItemDefaultFocus();
                }
                ImGui::EndCombo();
            }
            ImGui::TreePop();
        }
    }
    /* General Settings */
    {
        // vvv Lexicographically sort these vvv
        using StringPair = Pair<const char*, const char*>;
        constexpr auto kFormatGSString = [](const char* key, Span<const StringPair> strings) -> const char*
        {
            auto it = std::lower_bound(strings.begin(), strings.end(), key, [](const StringPair& lhs, const char* rhs)
            {
                return strcmp(lhs.first, rhs) < 0;
            });
            if (it == strings.end() || strcmp(it->first, key) != 0)
                return "common.unknown_brackets";
            return it->second;
        };
        // ^^^
        auto DrawGSBoolElement = [&](mdr::MDRHeadphones::GsCapability const& caps, MDRProperty<bool>& prop)
        {
            // Maps device-reported subject/summary tags to i18n keys; resolved at display time.
            constexpr StringPair kGSSubjectStrings[] = {
                {"MULTIPOINT_SETTING",   "system.gs.multipoint"},
                {"SIDETONE_SETTING",     "system.gs.sidetone"},
                {"TOUCH_PANEL_SETTING",  "system.gs.touch_panel"},
            };
            constexpr StringPair kGSSummaryStrings[] = {
                {"MULTIPOINT_SETTING_SUMMARY",                "system.gs.multipoint_summary"},
                {"MULTIPOINT_SETTING_SUMMARY_LDAC_AVAILABLE", "system.gs.multipoint_summary_ldac"},
                {"SIDETONE_SETTING_SUMMARY",                  "system.gs.sidetone_summary"},
            };

            using namespace v2::t1;
            if (caps.type != GsSettingType::BOOLEAN_TYPE)
                return;
            bool noSubject = caps.value.subject.value.empty();
            bool noSummary = caps.value.summary.value.empty();
            auto subject = i18n::tr(kFormatGSString(caps.value.subject.value.c_str(), kGSSubjectStrings));
            auto summary = i18n::tr(kFormatGSString(caps.value.summary.value.c_str(), kGSSummaryStrings));
            ImGui::BeginDisabled(noSubject);
            ImGui::Checkbox(subject, &prop.desired);
            if (!noSummary)
            {
                ImGui::Bullet();
                ImGui::SameLine();
                ImGui::TextWrapped("%s", summary);
            }
            ImGui::EndDisabled();
        };
        if (ImGui::TreeNodeEx(i18n::tr("system.general_setting"), ImGuiTreeNodeFlags_DefaultOpen))
        {
            if (kSupports(F1::GENERAL_SETTING_1))
                DrawGSBoolElement(gDevice.mGsCapability1, gDevice.mGsParamBool1);
            if (kSupports(F1::GENERAL_SETTING_2))
                DrawGSBoolElement(gDevice.mGsCapability2, gDevice.mGsParamBool2);
            if (kSupports(F1::GENERAL_SETTING_3))
                DrawGSBoolElement(gDevice.mGsCapability3, gDevice.mGsParamBool3);
            if (kSupports(F1::GENERAL_SETTING_4))
                DrawGSBoolElement(gDevice.mGsCapability4, gDevice.mGsParamBool4);
            ImGui::TreePop();
        }
    }
    /* Assignable Settings */
    {
        using enum v2::t1::Preset;
        constexpr v2::t1::Preset kSelections[] = {PLAYBACK_CONTROL, AMBIENT_SOUND_CONTROL_QUICK_ACCESS, NO_FUNCTION};
        if (kSupports(F1::ASSIGNABLE_SETTING))
        {
            if (ImGui::TreeNodeEx(i18n::tr("system.touch_preset"), ImGuiTreeNodeFlags_DefaultOpen))
            {
                ImComboBoxItems<v2::t1::Preset>(i18n::tr("system.left_touch"), kSelections, gDevice.mTouchFunctionLeft.desired);
                ImComboBoxItems<v2::t1::Preset>(i18n::tr("system.right_touch"), kSelections, gDevice.mTouchFunctionRight.desired);
                ImGui::TreePop();
            }
        }
    }
    /* NC/ASM Button Settings */
    {
        using enum v2::t1::Function;
        constexpr v2::t1::Function kSelections[] = { NO_FUNCTION, NC_ASM_OFF, NC_ASM,NC_OFF,ASM_OFF };
        if (kSupports(F1::AMBIENT_SOUND_CONTROL_MODE_SELECT))
        {
            if (ImGui::TreeNodeEx(i18n::tr("system.nc_amb_button"),ImGuiTreeNodeFlags_DefaultOpen))
            {
                ImComboBoxItems<v2::t1::Function>(i18n::tr("system.function"), kSelections, gDevice.mNcAsmButtonFunction.desired);
                ImGui::TreePop();
            }
        }
    }
    /* Head Gesture */
    {
        if (kSupports(F1::HEAD_GESTURE_ON_OFF_TRAINING))
        {
            if (ImGui::TreeNodeEx(i18n::tr("system.head_gesture"),ImGuiTreeNodeFlags_DefaultOpen))
            {
                ImGui::Checkbox(i18n::tr("common.enabled"), &gDevice.mHeadGestureEnabled.desired);
                ImGui::TreePop();
            }
        }
    }
    /* Auto Power Off */
    {
        using enum v2::t1::AutoPowerOffElements;
        constexpr v2::t1::AutoPowerOffElements kSelections[] = {
            POWER_OFF_DISABLE,POWER_OFF_IN_5_MIN, POWER_OFF_IN_15_MIN,POWER_OFF_IN_30_MIN,POWER_OFF_IN_60_MIN,POWER_OFF_IN_180_MIN
        };
        bool supportAutoOff = kSupports(F1::AUTO_POWER_OFF), supportAutoOffWear =kSupports(F1::AUTO_POWER_OFF_WITH_WEARING_DETECTION);
        if (supportAutoOff || supportAutoOffWear)
        {
            if (ImGui::TreeNodeEx(i18n::tr("system.auto_power_off"),ImGuiTreeNodeFlags_DefaultOpen))
            {
                ImComboBoxItems<v2::t1::AutoPowerOffElements>(i18n::tr("system.time"), kSelections, gDevice.mPowerAutoOff.desired);
                ImGui::TreePop();
            }
        }
    }
    /* Auto Pause */
    {
        if (kSupports(F1::PLAYBACK_CONTROL_BY_WEARING_REMOVING_HEADPHONE_ON_OFF))
        {
            if (ImGui::TreeNodeEx(i18n::tr("system.pause_when_removed"), ImGuiTreeNodeFlags_DefaultOpen))
            {
                ImGui::Checkbox(i18n::tr("common.enabled"), &gDevice.mAutoPauseEnabled.desired);
                ImGui::TreePop();
            }
        }
    }
    /* Voice Guidance */
    {
        if (ImGui::TreeNodeEx(i18n::tr("system.voice_guidance"), ImGuiTreeNodeFlags_DefaultOpen))
        {
            ImGui::Checkbox(i18n::tr("common.enabled"), &gDevice.mVoiceGuidanceEnabled.desired);
            ImGui::SeparatorText(i18n::tr("playback.volume"));
            ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
            if (kSupports(v2::MessageMdrV2FunctionType_Table2::VOICE_GUIDANCE_SETTING_MTK_TRANSFER_WITHOUT_DISCONNECTION_SUPPORT_LANGUAGE_SWITCH_AND_VOLUME_ADJUSTMENT))
                ImGui::SliderInt("##Volume", &gDevice.mVoiceGuidanceVolume.desired, -2, 2);
            ImGui::TreePop();
        }
    }
}
void DrawDeviceControlsAbout()
{
    if (ImGui::TreeNodeEx(i18n::tr("about.model"), ImGuiTreeNodeFlags_DefaultOpen))
    {
        if (ImGui::BeginTable("##ModelTable", 2, ImGuiTableFlags_RowBg | ImGuiTableFlags_SizingFixedFit))
        {
            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::Text("%s", i18n::tr("about.model_label"));
            ImGui::TableSetColumnIndex(1);
            ImGui::Text("%s", gDevice.mModelName.c_str());

            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::Text("%s", i18n::tr("about.mac_label"));
            ImGui::TableSetColumnIndex(1);
            ImGui::Text("%s", gDevice.mUniqueId.c_str());

            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::Text("%s", i18n::tr("about.fw_label"));
            ImGui::TableSetColumnIndex(1);
            ImGui::Text("%s", gDevice.mFWVersion.c_str());


            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::Text("%s", i18n::tr("about.series_label"));
            ImGui::TableSetColumnIndex(1);
            ImGui::Text("%s", format_as(gDevice.mModelSeries));

            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::Text("%s", i18n::tr("about.color_label"));
            ImGui::TableSetColumnIndex(1);
            ImGui::Text("%s", format_as(gDevice.mModelColor));

            ImGui::EndTable();
        }
        ImGui::TreePop();
    }
    if (ImGui::TreeNodeEx(i18n::tr("about.support_fn1"), ImGuiTreeNodeFlags_DefaultOpen))
    {
        if (ImGui::BeginTable("##SF1", 2, ImGuiTableFlags_RowBg | ImGuiTableFlags_SizingFixedFit))
        {
            for (int i = 0; i < 256;i++)
            {
                auto elem = static_cast<v2::MessageMdrV2FunctionType_Table1>(i);
                if (!is_valid(elem)) continue;
                ImGui::TableNextRow();
                ImGui::TableSetColumnIndex(0);
                ImGui::Text("%s", format_as(elem));
                ImGui::TableSetColumnIndex(1);
                ImGui::Text(gDevice.mSupport.contains(elem) ? PSI_OK : PSI_REMOVE);
            }
            ImGui::EndTable();
        }
        ImGui::TreePop();
    }
    if (ImGui::TreeNodeEx(i18n::tr("about.support_fn2"), ImGuiTreeNodeFlags_DefaultOpen))
    {
        if (ImGui::BeginTable("##SF2", 2, ImGuiTableFlags_RowBg | ImGuiTableFlags_SizingFixedFit))
        {
            for (int i = 0; i < 256;i++)
            {
                auto elem = static_cast<v2::MessageMdrV2FunctionType_Table2>(i);
                if (!is_valid(elem)) continue;
                ImGui::TableNextRow();
                ImGui::TableSetColumnIndex(0);
                ImGui::Text("%s", format_as(elem));
                ImGui::TableSetColumnIndex(1);
                ImGui::Text(gDevice.mSupport.contains(elem) ? PSI_OK : PSI_REMOVE);
            }
            ImGui::EndTable();
        }
        ImGui::TreePop();
    }
}
void DrawDeviceControlsTabs()
{    
    if (ImGui::BeginTabBar("##Controls"))
    {
        if (ImGui::BeginTabItem(i18n::tr("tab.playback")))
        {
            DrawDeviceControlsPlayback();
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem(i18n::tr("tab.sound")))
        {
            DrawDeviceControlsSound();
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem(i18n::tr("tab.devices")))
        {
            DrawDeviceControlsDevices();
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem(i18n::tr("tab.system")))
        {
            DrawDeviceControlsSystem();
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem(i18n::tr("tab.about")))
        {
            DrawDeviceControlsAbout();
            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }
}

void DrawDeviceControls()
{
    MDRConnection* conn = clientPlatformConnectionGet();
    int event = gDevice.PollEvents();
    DrawDeviceControlsHeader();
    ImGui::Separator();
    ImGui::BeginChild("##ControlTabs");
    DrawDeviceControlsTabs();
    ImScrollWhenDraggingAnywhere(ImGui::GetIO().MouseDelta, ImGuiMouseButton_Left);
    ImGui::EndChild();
    ExceptionHandler([&]
    {
        switch (event)
        {
        case MDR_HEADPHONES_TASK_INIT_OK:
            // Request for a stat update ASAP
            // User may request for this themselves - we don't do periodic checks this time
            MDR_CHECK(gDevice.Invoke(gDevice.RequestSyncV2()) == MDR_RESULT_OK);
            return;
        case MDR_HEADPHONES_IDLE:
            // Commit changes if needed to
            if (gDevice.IsDirty())
                MDR_CHECK(gDevice.Invoke(gDevice.RequestCommitV2()) == MDR_RESULT_OK);
            return;
        case MDR_HEADPHONES_ERROR:
            // Irrecoverable. Disconnect now.
            mdrConnectionDisconnect(conn);
            connState = CONN_STATE_DISCONNECTED;
        case MDR_HEADPHONES_EVT_DEVICE_INFO:
            // Dynamic theme for the headphone's own colors
            // Contributed by @salmon-21 in https://github.com/mos9527/SonyHeadphonesClient/pull/41
            MaterialYouTheme::ApplyForModelColor(static_cast<uint8_t>(gDevice.mModelColor));
        case MDR_HEADPHONES_INPROGRESS:
        default:
            break;
        }
    });
}

void DrawDeviceDisconnect()
{
    MDRConnection* conn = clientPlatformConnectionGet();
    static bool popup = false;
    if (!popup)
        ImGui::OpenPopup("Disconnected"), popup = true;
    ImSetNextWindowCentered();

    if (ImGui::BeginPopupModal("Disconnected", nullptr, kImWindowFlagsTopMost))
    {
        ImGui::NewLine();
        ImTextCentered(i18n::tr("disconnect.title"));
        ImGui::NewLine();
        ImSpinner(5000.0f, 24.0f, MaterialYouTheme::ArgbToImU32(MaterialYouTheme::FixedSurfaceColors::error), 4.0f, true, false);
        ImGui::NewLine();
        ImGui::SeparatorText(i18n::tr("disconnect.messages"));
        ImGui::TextWrapped(i18n::tr("disconnect.connection_fmt"), mdrConnectionGetLastError(conn));
        ImGui::TextWrapped(i18n::tr("disconnect.headphones_fmt"), gDevice.GetLastError());
        ImGui::NewLine();
        ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
        if (ImModalButton(i18n::trIcon(PSI_LINK, "disconnect.reconnect").c_str()))
        {
            mdrConnectionDisconnect(conn);
            connState = CONN_STATE_NO_CONNECTION;
        }

        ImGui::EndPopup();
    } else
        popup = false;
}

void DrawApp()
{    
    auto& io = ImGui::GetIO();
    auto& g = *ImGui::GetCurrentContext();
    ImGui::SetNextWindowPos({0, 0});
    ImGui::SetNextWindowSize(io.DisplaySize);
    ImGuiWindowFlags flags = kImWindowFlagsTopMost;
    switch (connState)
    {
    case CONN_STATE_CONNECTED:
        flags |= ImGuiWindowFlags_MenuBar;
        break;
    default:
        break;
    }
    if (ImGui::Begin("SonyHeadphonesClient", nullptr, flags))
    {
        ExceptionHandler([&]
        {
            switch (connState)
            {
            case CONN_STATE_NO_CONNECTION:
                DrawDeviceDiscovery();
                break;
            case CONN_STATE_CONNECTING:
                DrawDeviceConnecting();
                break;
            case CONN_STATE_CONNECTED:
                DrawDeviceControls();
                break;
            case CONN_STATE_DISCONNECTED:
                DrawDeviceDisconnect();
                break;
            }
        });
    }
    ImGui::End();
}

// You know this one.
void DrawBugcheck()
{
    auto& style = ImGui::GetStyle();
    float padding = style.FramePadding.x;
    auto& io = ImGui::GetIO();
    ImGui::SetNextWindowPos({0, 0});
    ImGui::SetNextWindowSize(io.DisplaySize);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::PushStyleColor(ImGuiCol_WindowBg, MaterialYouTheme::ArgbToImU32(MaterialYouTheme::FixedSurfaceColors::surface));
    if (ImGui::Begin("##", nullptr, kImWindowFlagsTopMost))
    {
        auto [offset, region, draw] = ImWindowDrawOffsetRegionList();
        float fontBase = std::max(ImGui::CalcTextSize(gBugcheckMessage.c_str()).x, region.x);
        fontBase = (region.x - padding * 4) / (fontBase + padding * 4);
        ImGui::PushFont(ImGui::GetFont(), ImGui::GetStyle().FontSizeBase * fontBase);
        float sizeV = ImGui::CalcTextSize(gBugcheckMessage.c_str()).y + ImGui::GetTextLineHeight() * 2;
        ImVec2 tl{padding, padding}, br{region.x - padding, sizeV + padding * 8};
        tl += offset, br += offset;
        auto errorCol = MaterialYouTheme::ArgbToImU32(MaterialYouTheme::FixedSurfaceColors::error);
        auto errorContCol = MaterialYouTheme::ArgbToImU32(MaterialYouTheme::FixedSurfaceColors::errorContainer);
        draw->AddRectFilled(tl, br, ImBlink(1000u, 2u) ? errorCol : errorContCol);
        draw->AddRectFilled(tl + tl, br - tl, MaterialYouTheme::ArgbToImU32(MaterialYouTheme::FixedSurfaceColors::surface));
        ImGui::SetCursorPosY(offset.y + padding * 4);
        ImGui::PushStyleColor(ImGuiCol_Text, errorCol);
        ImTextCentered(i18n::tr("bugcheck.title"));
        ImTextCentered(fmt::format("{}@{}, {} on {}", MDR_GIT_BRANCH_NAME, MDR_GIT_COMMIT_HASH, CLIENT_VERSION, MDR_PLATFORM_OS).c_str());
        ImTextCentered(gBugcheckMessage.c_str());
        ImGui::PopStyleColor();
        ImGui::SetCursorPosY(br.y + padding * 2);
        ImGui::SeparatorText(i18n::tr("bugcheck.to_report"));
        ImGui::TextWrapped("%s", i18n::trIcon(PSI_INFO_SIGN_ALT, "bugcheck.hint_check").c_str());
        ImGui::TextWrapped("%s", i18n::trIcon(PSI_INFO_SIGN_ALT, "bugcheck.hint_submit").c_str());
        ImGui::Separator();
        ImGui::TextWrapped("%s", i18n::trIcon(PSI_GITHUB, "bugcheck.issues_link").c_str());
        ImGui::PopFont();
        ImGui::PopStyleVar();
        ImGui::PopStyleColor();
    }
    ImGui::End();
}

bool clientShouldExit()
{
    // Defines like IMGUI_DISABLE_OBSOLETE_FUNCTIONS changes ImGui struct sizes
    // and can lead to very, very bad results. Check them here too to ensure than this TU got the correct ones.
    IMGUI_CHECKVERSION();
    switch (appState)
    {
    case APP_STATE_RUNNING:
        DrawApp();
        break;
    case APP_STATE_BUGCHECK:
        DrawBugcheck();
        break;
    }
    return false;
}
