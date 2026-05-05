// Japanese overrides. Keys absent here fall back to strings_keys.inc (English).

// --- Tabs ---
I18N_STR("tab.playback", "再生")
I18N_STR("tab.sound",    "サウンド")
I18N_STR("tab.devices",  "デバイス")
I18N_STR("tab.system",   "システム")
I18N_STR("tab.about",    "情報")

// --- AudioCodec --- (codec names are proper nouns, kept as-is)
I18N_STR("audio_codec.unsettled", "<未設定>")
I18N_STR("audio_codec.unknown",   "不明")

// --- UpscalingType (DSEE) --- (DSEE names are proper nouns, kept as-is)
I18N_STR("dsee.unknown", "DSEE 不明")

// --- BatteryChargingStatus ---
I18N_STR("battery.charging", "充電中")
I18N_STR("battery.charged",  "満充電")
I18N_STR("battery.unknown",  "不明")

// --- NoiseAdaptiveSensitivity ---
I18N_STR("nc_sens.standard", "標準")
I18N_STR("nc_sens.high",     "高")
I18N_STR("nc_sens.low",      "低")
I18N_STR("nc_sens.unknown",  "不明")

// --- DetectSensitivity ---
I18N_STR("detect_sens.auto",    "自動")
I18N_STR("detect_sens.high",    "高")
I18N_STR("detect_sens.low",     "低")
I18N_STR("detect_sens.unknown", "不明")

// --- ModeOutTime ---
I18N_STR("mode_out_time.fast",    "短め (約5秒)")
I18N_STR("mode_out_time.mid",     "標準 (約15秒)")
I18N_STR("mode_out_time.slow",    "長め (約30秒)")
I18N_STR("mode_out_time.none",    "自動終了しない")
I18N_STR("mode_out_time.unknown", "不明")

// --- EqPresetId ---
I18N_STR("eq.off",       "オフ")
I18N_STR("eq.rock",      "ロック")
I18N_STR("eq.pop",       "ポップ")
I18N_STR("eq.jazz",      "ジャズ")
I18N_STR("eq.dance",     "ダンス")
I18N_STR("eq.rb_hiphop", "R&B/ヒップホップ")
I18N_STR("eq.acoustic",  "アコースティック")
I18N_STR("eq.bright",    "ブライト")
I18N_STR("eq.excited",   "エキサイテッド")
I18N_STR("eq.mellow",    "メロウ")
I18N_STR("eq.relaxed",   "リラックス")
I18N_STR("eq.vocal",     "ボーカル")
I18N_STR("eq.treble",    "トレブル")
I18N_STR("eq.bass",      "バス")
I18N_STR("eq.speech",    "スピーチ")
I18N_STR("eq.custom",    "カスタム")
I18N_STR("eq.user1",     "ユーザー設定 1")
I18N_STR("eq.user2",     "ユーザー設定 2")
I18N_STR("eq.user3",     "ユーザー設定 3")
I18N_STR("eq.user4",     "ユーザー設定 4")
I18N_STR("eq.user5",     "ユーザー設定 5")
I18N_STR("eq.unknown",   "不明")

// --- Preset (touch sensor functions) ---
I18N_STR("preset.ambient_sound_control", "外音コントロール")
I18N_STR("preset.volume_control",        "音量コントロール")
I18N_STR("preset.playback_control",      "再生コントロール")
I18N_STR("preset.track_control",         "トラックコントロール")
I18N_STR("preset.voice_recognition",     "音声認識")
I18N_STR("preset.quick_access",          "クイックアクセス")
I18N_STR("preset.no_function",           "機能なし")
I18N_STR("preset.unknown",               "不明")

// --- Function (NC/AMB button) ---
I18N_STR("function.no_function", "機能なし")
I18N_STR("function.unknown",     "不明")

// --- AutoPowerOffElements ---
I18N_STR("auto_power_off.5min",    "Bluetooth未接続 5分後")
I18N_STR("auto_power_off.15min",   "Bluetooth未接続 15分後")
I18N_STR("auto_power_off.30min",   "Bluetooth未接続 30分後")
I18N_STR("auto_power_off.60min",   "Bluetooth未接続 1時間後")
I18N_STR("auto_power_off.180min",  "Bluetooth未接続 3時間後")
I18N_STR("auto_power_off.disable", "オフにしない")
I18N_STR("auto_power_off.unknown", "不明")

// --- Common ---
I18N_STR("common.off",              "オフ")
I18N_STR("common.on",               "オン")
I18N_STR("common.enabled",          "有効")
I18N_STR("common.sensitivity",      "感度")
I18N_STR("common.cancel",           "キャンセル")
I18N_STR("common.unknown_brackets", "<不明>")

// --- Discovery / Connection screen ---
I18N_STR("discovery.available_devices", "利用可能なデバイス")
I18N_STR("discovery.no_devices",        " 利用可能なデバイスがありません。Bluetoothがオンで、対応デバイスが接続されているか確認してください。")
I18N_STR("discovery.connect",           " 接続")
I18N_STR("discovery.refresh",           " 更新")
I18N_STR("discovery.init_failed",       " 接続の初期化に失敗しました: {}")
I18N_STR("discovery.bt_select_hint",    " LE Audio接続なら BLE (GATT)、それ以外や不明なら Classic を選んでください。")
I18N_STR("discovery.disclaimer",        " このアプリは Sony とは関係ありません。利用は自己責任で。 ")
I18N_STR("discovery.version_fmt",       "バージョン: {} / ブランチ: {} / コミット: {} / 動作: {}")
// Bluetooth tech names kept as-is

// --- Connecting screen ---
I18N_STR("connecting.title",  "接続中…")
I18N_STR("connecting.cancel", " キャンセル")

// --- Disconnect screen ---
I18N_STR("disconnect.title",          "デバイスとの接続が切れました")
I18N_STR("disconnect.messages",       "メッセージ")
I18N_STR("disconnect.connection_fmt", "接続: %s")
I18N_STR("disconnect.headphones_fmt", "ヘッドホン: %s")
I18N_STR("disconnect.reconnect",      " 再接続")

// --- Header / Menu ---
I18N_STR("header.disconnect",         " 切断")
I18N_STR("header.shutdown",           " 電源を切る")
I18N_STR("header.battery_fmt",        "バッテリー: %.0d%%")
I18N_STR("header.battery_case_fmt",   "ケース: %.0d%%")
I18N_STR("header.now_playing",        " 再生中")
I18N_STR("header.now_playing_title",  "タイトル")
I18N_STR("header.now_playing_album",  "アルバム")
I18N_STR("header.now_playing_artist", "アーティスト")

// --- Playback tab ---
I18N_STR("playback.volume",   "音量")
I18N_STR("playback.controls", "コントロール")
I18N_STR("playback.prev",     " 前へ")
I18N_STR("playback.pause",    " 一時停止")
I18N_STR("playback.play",     " 再生")
I18N_STR("playback.next",     "次へ")

// --- Sound tab ---
I18N_STR("sound.ambient_sound",      "外音コントロール")
I18N_STR("sound.noise_cancelling",   "ノイズキャンセリング")
I18N_STR("sound.ambient_strength",   "外音レベル")
I18N_STR("sound.auto_ambient_sound", "自動外音コントロール")
I18N_STR("sound.voice_passthrough",  "音声を強調")
I18N_STR("sound.speak_to_chat",      "スピーク・トゥ・チャット")
I18N_STR("sound.mode_duration",      "モード解除時間")
I18N_STR("sound.listening_mode",     "リスニングモード")
I18N_STR("sound.bgm",                 "BGM")
I18N_STR("sound.cinema",              "シネマ")
I18N_STR("sound.distance",            "距離")
I18N_STR("sound.my_room",             "マイルーム")
I18N_STR("sound.living_room",         "リビング")
I18N_STR("sound.cafe",                "カフェ")
I18N_STR("sound.eq_dsee",             "イコライザー & DSEE")
I18N_STR("sound.preset",              "プリセット")
I18N_STR("sound.clear_bass",          "クリアベース")
I18N_STR("sound.dsee_on_auto",        "オン (自動)")
I18N_STR("sound.eq_5band",            "5バンド EQ")
I18N_STR("sound.eq_10band",           "10バンド EQ")
I18N_STR("sound.eq_unavailable_fmt",  "EQ 利用不可 (バンド数=%d)")

// --- Devices tab ---
I18N_STR("devices.need_multipoint",   "デバイス管理にはシステム設定の「2台同時接続」を有効にしてください。")
I18N_STR("devices.disconnect",        "切断")
I18N_STR("devices.connect",           "接続")
I18N_STR("devices.unpair",            "ペアリング解除")
I18N_STR("devices.connected",         "接続済み")
I18N_STR("devices.paired",            "ペアリング済み")
I18N_STR("devices.pairing",           "ペアリング中…")
I18N_STR("devices.stop",              "停止")
I18N_STR("devices.enter_pairing_mode","ペアリングモードに入る")
I18N_STR("devices.tws_hint",          " イヤホン (TWS) の場合、ペアリングモードに入るには両方のイヤホンをケースから取り出す必要があります。")

// --- System tab ---
I18N_STR("system.general_setting",     "一般設定")
I18N_STR("system.gs.multipoint",       "2台同時接続")
I18N_STR("system.gs.sidetone",         "通話中に自分の声を聞き取りやすくする")
I18N_STR("system.gs.touch_panel",      "タッチセンサーコントロール")
I18N_STR("system.gs.multipoint_summary",
         "例: PCとスマホの両方で使うとき、接続を切り替えずに快適に使えます。同時接続中は「音質優先」を選んでも LDAC コーデックでは再生できません。")
I18N_STR("system.gs.multipoint_summary_ldac",
         "例: PCとスマホの両方で使うとき、接続を切り替えずに快適に使えます。")
I18N_STR("system.gs.sidetone_summary",
         "通話中に自分の声が聞き取りやすくなります。声が大きすぎたり背景音が気になる場合はこの機能をオフにしてください。")
I18N_STR("system.touch_preset",        "タッチプリセット")
I18N_STR("system.left_touch",          "左タッチ")
I18N_STR("system.right_touch",         "右タッチ")
I18N_STR("system.nc_amb_button",       "NC/AMB ボタン機能")
I18N_STR("system.function",            "機能")
I18N_STR("system.head_gesture",        "ヘッドジェスチャー")
I18N_STR("system.auto_power_off",      "自動電源オフ")
I18N_STR("system.time",                "時間")
I18N_STR("system.pause_when_removed",  "取り外し時に一時停止")
I18N_STR("system.voice_guidance",      "音声ガイダンス")
I18N_STR("system.language",            "言語")

// --- About tab ---
I18N_STR("about.model",        "モデル")
I18N_STR("about.model_label",  "モデル:")
I18N_STR("about.fw_label",     "ファームウェアバージョン:")
I18N_STR("about.series_label", "シリーズ:")
I18N_STR("about.color_label",  "色:")
I18N_STR("about.support_fn1",  "サポート機能 1")
I18N_STR("about.support_fn2",  "サポート機能 2")
// MAC: は英語のまま（万国共通）

// --- Bugcheck ---
I18N_STR("bugcheck.title",        "致命的エラーが発生しました。スクリーンショットを撮って報告してください。")
I18N_STR("bugcheck.to_report",    "報告手順")
I18N_STR("bugcheck.hint_check",   " GitHub の Open/Closed Issue を確認し、重複していないか確認してください。")
I18N_STR("bugcheck.hint_submit",  " 重複がなければ、この画面のスクリーンショットを添えて Issue を新規作成してください。")
