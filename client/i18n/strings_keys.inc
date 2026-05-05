// Canonical key list with default English values.
// Add entries via I18N_STR(key, english_text). Keys absent in strings_ja.inc fall back here.

// --- Tabs ---
I18N_STR("tab.playback", "Playback")
I18N_STR("tab.sound",    "Sound")
I18N_STR("tab.devices",  "Devices")
I18N_STR("tab.system",   "System")
I18N_STR("tab.about",    "About")

// --- AudioCodec ---
I18N_STR("audio_codec.unsettled", "<unsettled>")
I18N_STR("audio_codec.sbc",       "SBC")
I18N_STR("audio_codec.aac",       "AAC")
I18N_STR("audio_codec.ldac",      "LDAC")
I18N_STR("audio_codec.aptx",      "aptX")
I18N_STR("audio_codec.aptx_hd",   "aptX HD")
I18N_STR("audio_codec.lc3",       "LC3")
I18N_STR("audio_codec.unknown",   "Unknown")

// --- UpscalingType (DSEE) ---
I18N_STR("dsee.hx",       "DSEE HX")
I18N_STR("dsee.dsee",     "DSEE")
I18N_STR("dsee.hx_ai",    "DSEE HX AI")
I18N_STR("dsee.ultimate", "DSEE ULTIMATE")
I18N_STR("dsee.unknown",  "DSEE Unknown")

// --- BatteryChargingStatus ---
I18N_STR("battery.charging",     "Charging")
I18N_STR("battery.charged",      "Charged")
I18N_STR("battery.not_charging", "")
I18N_STR("battery.unknown",      "Unknown")

// --- NoiseAdaptiveSensitivity ---
I18N_STR("nc_sens.standard", "Standard")
I18N_STR("nc_sens.high",     "High")
I18N_STR("nc_sens.low",      "Low")
I18N_STR("nc_sens.unknown",  "Unknown")

// --- DetectSensitivity ---
I18N_STR("detect_sens.auto",    "Auto")
I18N_STR("detect_sens.high",    "High")
I18N_STR("detect_sens.low",     "Low")
I18N_STR("detect_sens.unknown", "Unknown")

// --- ModeOutTime ---
I18N_STR("mode_out_time.fast",    "Short (~5s)")
I18N_STR("mode_out_time.mid",     "Standard (~15s)")
I18N_STR("mode_out_time.slow",    "Long (~30s)")
I18N_STR("mode_out_time.none",    "Don't end automatically")
I18N_STR("mode_out_time.unknown", "Unknown")

// --- EqPresetId ---
I18N_STR("eq.off",       "Off")
I18N_STR("eq.rock",      "Rock")
I18N_STR("eq.pop",       "Pop")
I18N_STR("eq.jazz",      "Jazz")
I18N_STR("eq.dance",     "Dance")
I18N_STR("eq.edm",       "EDM")
I18N_STR("eq.rb_hiphop", "R&B/Hip-Hop")
I18N_STR("eq.acoustic",  "Acoustic")
I18N_STR("eq.bright",    "Bright")
I18N_STR("eq.excited",   "Excited")
I18N_STR("eq.mellow",    "Mellow")
I18N_STR("eq.relaxed",   "Relaxed")
I18N_STR("eq.vocal",     "Vocal")
I18N_STR("eq.treble",    "Treble")
I18N_STR("eq.bass",      "Bass")
I18N_STR("eq.speech",    "Speech")
I18N_STR("eq.custom",    "Custom")
I18N_STR("eq.user1",     "User Setting 1")
I18N_STR("eq.user2",     "User Setting 2")
I18N_STR("eq.user3",     "User Setting 3")
I18N_STR("eq.user4",     "User Setting 4")
I18N_STR("eq.user5",     "User Setting 5")
I18N_STR("eq.unknown",   "Unknown")

// --- Preset (touch sensor functions) ---
I18N_STR("preset.ambient_sound_control", "Ambient Sound Control")
I18N_STR("preset.volume_control",        "Volume Control")
I18N_STR("preset.playback_control",      "Playback Control")
I18N_STR("preset.track_control",         "Track Control")
I18N_STR("preset.voice_recognition",     "Voice Recognition")
I18N_STR("preset.google_assist",         "Google Assistant")
I18N_STR("preset.amazon_alexa",          "Amazon Alexa")
I18N_STR("preset.tencent_xiaowei",       "Tencent Xiaowei")
I18N_STR("preset.quick_access",          "Quick Access")
I18N_STR("preset.no_function",           "No Function")
I18N_STR("preset.unknown",               "Unknown")

// --- Function (NC/AMB button) ---
I18N_STR("function.no_function", "No Function")
I18N_STR("function.nc_asm_off",  "NC-ASM-OFF")
I18N_STR("function.nc_asm",      "NC-ASM")
I18N_STR("function.nc_off",      "NC-OFF")
I18N_STR("function.asm_off",     "ASM-OFF")
I18N_STR("function.unknown",     "Unknown")

// --- AutoPowerOffElements ---
I18N_STR("auto_power_off.5min",    "5 minutes of no Bluetooth connection")
I18N_STR("auto_power_off.15min",   "15 minutes of no Bluetooth connection")
I18N_STR("auto_power_off.30min",   "30 minutes of no Bluetooth connection")
I18N_STR("auto_power_off.60min",   "1 hour of no Bluetooth connection")
I18N_STR("auto_power_off.180min",  "3 hours of no Bluetooth connection")
I18N_STR("auto_power_off.disable", "Do not turn off")
I18N_STR("auto_power_off.unknown", "Unknown")

// --- Common (shared UI words) ---
I18N_STR("common.off",         "Off")
I18N_STR("common.on",           "On")
I18N_STR("common.enabled",      "Enabled")
I18N_STR("common.sensitivity",  "Sensitivity")
I18N_STR("common.cancel",       "Cancel")
I18N_STR("common.unknown_brackets", "<Unknown>")

// --- Discovery / Connection screen ---
I18N_STR("discovery.available_devices", "Available Devices")
I18N_STR("discovery.no_devices",        " No devices available. Make sure your Bluetooth radio is turned on, and a compatible device is connected.")
I18N_STR("discovery.connect",           " Connect")
I18N_STR("discovery.refresh",           " Refresh")
I18N_STR("discovery.init_failed",       " Failed to initialize connection: {}")
I18N_STR("discovery.bt_select_hint",    " Select BLE (GATT) if your device is connected via LE Audio, and Classic if you don't know what that means or otherwise.")
I18N_STR("discovery.disclaimer",        " This product is not affiliated with Sony. Use at your own risk. ")
I18N_STR("discovery.version_fmt",       "Version: {}, Branch: {}, Commit: {}, On {}")
I18N_STR("discovery.classic",           " Classic")
I18N_STR("discovery.ble_gatt",          " BLE (GATT)")

// --- Connecting screen ---
I18N_STR("connecting.title",  "Connecting...")
I18N_STR("connecting.cancel", " Cancel")

// --- Disconnect screen ---
I18N_STR("disconnect.title",     "Device Disconnected")
I18N_STR("disconnect.messages",  "Messages")
I18N_STR("disconnect.connection_fmt", "Connection: %s")
I18N_STR("disconnect.headphones_fmt", "Headphones: %s")
I18N_STR("disconnect.reconnect", " Reconnect")

// --- Header / Menu ---
I18N_STR("header.disconnect",       " Disconnect")
I18N_STR("header.shutdown",         " Shutdown")
I18N_STR("header.battery_fmt",      "Battery: %.0d%%")
I18N_STR("header.battery_l_fmt",    "L: %.0d%%")
I18N_STR("header.battery_r_fmt",    "R: %.0d%%")
I18N_STR("header.battery_case_fmt", "Case: %.0d%%")
I18N_STR("header.now_playing",      " Now Playing")
I18N_STR("header.now_playing_title",  "Title")
I18N_STR("header.now_playing_album",  "Album")
I18N_STR("header.now_playing_artist", "Artist")

// --- Playback tab ---
I18N_STR("playback.volume",   "Volume")
I18N_STR("playback.controls", "Controls")
I18N_STR("playback.prev",     " Prev")
I18N_STR("playback.pause",    " Pause")
I18N_STR("playback.play",     " Play")
I18N_STR("playback.next",     "Next")

// --- Sound tab ---
I18N_STR("sound.ambient_sound",            "Ambient Sound")
I18N_STR("sound.noise_cancelling",         "Noise Cancelling")
I18N_STR("sound.ambient_strength",         "Ambient Strength")
I18N_STR("sound.auto_ambient_sound",       "Auto Ambient Sound")
I18N_STR("sound.voice_passthrough",        "Voice Passthrough")
I18N_STR("sound.speak_to_chat",            "Speak To Chat")
I18N_STR("sound.mode_duration",            "Mode Duration")
I18N_STR("sound.listening_mode",           "Listening Mode")
I18N_STR("sound.bgm",                       "BGM")
I18N_STR("sound.cinema",                    "Cinema")
I18N_STR("sound.distance",                  "Distance")
I18N_STR("sound.my_room",                   "My Room")
I18N_STR("sound.living_room",               "Living Room")
I18N_STR("sound.cafe",                      "Cafe")
I18N_STR("sound.eq_dsee",                   "Equalizer & DSEE")
I18N_STR("sound.preset",                    "Preset")
I18N_STR("sound.clear_bass",                "Clear Bass")
I18N_STR("sound.dsee",                      "DSEE")
I18N_STR("sound.dsee_on_auto",              "On (Auto)")
I18N_STR("sound.eq_5band",                  "5-Band EQ")
I18N_STR("sound.eq_10band",                 "10-Band EQ")
I18N_STR("sound.eq_unavailable_fmt",        "EQ Unavailable (bands=%d)")

// --- Devices tab ---
I18N_STR("devices.need_multipoint",  "Please enable \"Connect to 2 devices simultaneously\" in System settings to manage devices.")
I18N_STR("devices.disconnect",        "Disconnect")
I18N_STR("devices.connect",           "Connect")
I18N_STR("devices.unpair",            "Unpair")
I18N_STR("devices.connected",         "Connected")
I18N_STR("devices.paired",            "Paired")
I18N_STR("devices.pairing",           "Pairing...")
I18N_STR("devices.stop",              "Stop")
I18N_STR("devices.enter_pairing_mode","Enter Pairing Mode")
I18N_STR("devices.tws_hint",          " For TWS (Earbuds) devices, you may need to take both of your headphones out from your case to enter Pairing Mode.")

// --- System tab ---
I18N_STR("system.general_setting",     "General Setting")
I18N_STR("system.gs.multipoint",       "Connect to 2 devices simultaneously")
I18N_STR("system.gs.sidetone",         "Capture Voice During a Phone Call")
I18N_STR("system.gs.touch_panel",      "Touch sensor control panel")
I18N_STR("system.gs.multipoint_summary",
         "For example, when using the audio device with both a PC and a smartphone, you can use it comfortably without needing to switch connections. During simultaneous connections, playback with the LDAC codec is not possible even if Prioritize Sound Quality is selected.")
I18N_STR("system.gs.multipoint_summary_ldac",
         "For example, when using the audio device with both a PC and a smartphone, you can use it comfortably without needing to switch connections.")
I18N_STR("system.gs.sidetone_summary",
         "Your own voice will be easier to hear during calls. If your voice sounds too loud or background noise is distracting, please turn off this feature.")
I18N_STR("system.touch_preset",        "Touch Preset")
I18N_STR("system.left_touch",          "Left Touch")
I18N_STR("system.right_touch",         "Right Touch")
I18N_STR("system.nc_amb_button",       "NC/AMB Button Function")
I18N_STR("system.function",            "Function")
I18N_STR("system.head_gesture",        "Head Gesture")
I18N_STR("system.auto_power_off",      "Auto Power Off")
I18N_STR("system.time",                "Time")
I18N_STR("system.pause_when_removed",  "Pause when removed")
I18N_STR("system.voice_guidance",      "Voice Guidance")
I18N_STR("system.language",            "Language")

// --- About tab ---
I18N_STR("about.model",        "Model")
I18N_STR("about.model_label",  "Model:")
I18N_STR("about.mac_label",    "MAC:")
I18N_STR("about.fw_label",     "Firmware Version:")
I18N_STR("about.series_label", "Series:")
I18N_STR("about.color_label",  "Color:")
I18N_STR("about.support_fn1",  "Support Functions 1")
I18N_STR("about.support_fn2",  "Support Functions 2")

// --- Bugcheck ---
I18N_STR("bugcheck.title",        "Guru Meditation. Please screenshot and report.")
I18N_STR("bugcheck.to_report",    "To Report")
I18N_STR("bugcheck.hint_check",   " Check the Open/Closed Github Issue tickets and see if it's a duplicate.")
I18N_STR("bugcheck.hint_submit",  " If not, take a screenshot of this screen and submit a new one")
I18N_STR("bugcheck.issues_link",  " Issues: https://github.com/mos9527/SonyHeadphonesClient/issues")
