# SonyHeadphonesClient (mos9527 fork) — 個人開発フォーク

mos9527/SonyHeadphonesClient (`rewrite` ブランチ) を土台にした個人プロジェクト。
ベースはMITライセンス。実機ターゲットは **WH-1000XM6 / WF-1000XM6**。

**スコープ**：
- Phase 1: 日本語化 (i18n) — **完了**
- Phase 2: Windows ポータブル配布 — **完了 (v0.1.0)**
- Phase 3: BLE GATT バックエンド有効化 + MSVC toolchain 移行 — **ビルド系完了 (2026-05-06)、実機検証保留**
- UI/UX 改修系 (Sound Connect 風ダッシュボード、EQ ビジュアライザ、NC 視覚化、カード化等) は引き続き却下、自発提案しないこと
- 上流 PR は予定なし

## リポジトリ位置

ローカル：`E:\dev\SonyHeadphonesClient\`、ブランチ `rewrite`。

| remote | URL | 用途 |
|---|---|---|
| `origin` | `https://github.com/tenma2066-tech/SonyHeadphonesClient` | 自分のフォーク。push 先 |
| `upstream` | `https://github.com/mos9527/SonyHeadphonesClient` | 上流。fetch のみ |

`gh` CLI は `tenma2066-tech` で認証済（`repo` + `workflow` scope）。`gh` 系コマンドはデフォルトで上流を見るため `--repo tenma2066-tech/SonyHeadphonesClient` を明示すること。

## ビルド

### 必要ツール（すべて E:\tools にポータブル配置済み）

**MSVC 主系（Phase 3 以降の標準）**：
- MSVC v143 (cl 19.44.35226 / VC Tools 14.44.35207) + Windows SDK 10.0.26100 → `E:\tools\msvc`
  - [PortableBuildTools](https://github.com/Data-Oriented-House/PortableBuildTools) (v2.10.2) で展開 (1.4 GB、サービス登録/レジストリ/C: 書き込みなし)
  - 環境設定スクリプト：`E:\tools\msvc\devcmd.bat` / `devcmd.ps1`
- CMake 4.3.2 → `E:\tools\cmake\bin`
- Ninja 1.13.2 → `E:\tools\bin\ninja.exe`

**MinGW 副系（fallback、`MDR_DISABLE_BLE=ON` 専用）**：
- MinGW-w64 GCC 16.1.0 UCRT (winlibs) → `E:\tools\mingw64\bin`
- C++/WinRT 不可 → BLE バックエンド除外時のみ使用

### PATH と env activation（bash）

**MSVC 主系**：
```bash
# devcmd.bat は INCLUDE/LIB/PATH をまとめてセット。bash から呼ぶには cmd を経由
cmd /c 'call E:\tools\msvc\devcmd.bat && cmake -G Ninja -DCMAKE_BUILD_TYPE=Release ..'
# cmake と ninja は別途 PATH へ通す
export PATH="/e/tools/cmake/bin:/e/tools/bin:$PATH"
```

**MinGW 副系**：
```bash
export PATH="/e/tools/mingw64/bin:/e/tools/cmake/bin:/e/tools/bin:$PATH"
```

### 既知のハマりどころ

1. **MSVC ランタイムは `/MT` 静的リンク**：ルート `CMakeLists.txt` で `set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")` をグローバル設定 (CMP0091 NEW)。SDL3 / imgui 含む全 target に伝播。`vcruntime140.dll` / `msvcp140.dll` / `ucrtbase.dll` 同梱不要、vcredist 不要。

2. **MinGW fallback も static**：`client/CMakeLists.txt` の `if (MINGW)` 分岐で `-static` を適用。`libgcc_s_seh-1.dll` / `libstdc++-6.dll` / `libwinpthread-1.dll` 同梱不要。

3. **C++/WinRT は MSVC + Win SDK 必須**：MinGW では `winrt/Windows.Foundation.h` が入手できず `PlatformWindowsBLE.cpp` (747 行) がビルド不可。
   → MSVC ビルドでは `windowsapp.lib` リンクで自動有効化 (`libmdr/src/Platform/Windows/CMakeLists.txt`)。
   → MinGW で逃げる場合は `-DMDR_DISABLE_BLE=ON` でスタブ `PlatformWindowsBLE_stub.cpp` に差し替え。

4. **PortableBuildTools の文字化け事故**：`E:\tools\dl\PortableBuildTools.exe` は CLI 引数を受け付けるが、内部で **`SetConsoleOutputCP(437)`** を call し **`WriteConsole` (Wide API) で出力** する。
   - bash から直接呼ぶと CP437 (米国 OEM) が UTF-8 デコーダに食われ、ロシア語/罫線文字風の文字化けでターミナル状態機械が壊れる。
   - `WriteConsole` はリダイレクト先 (パイプ/ファイル) では失敗して何も書かない → ログ取れない。
   - **回避策**：PowerShell の `Start-Process` で **新しい console 窓を開いて起動** (CP437 汚染をその窓に閉じ込める)。または `-NoNewWindow` で CLI モード強制 + 親 console の文字化けを覚悟。
   - 起動判定ロジック：`base.h:917` で `GetWindowThreadProcessId(GetConsoleWindow(), &pid); invoked_from_console = (GetCurrentProcessId() != pid);`。`Start-Process` (新窓) だと自分が console 所有者になり GUI モード判定。

5. **git の dubious ownership**：E ドライブが ownership 非記録のため `safe.directory = *` を `git config --global` 設定済み。

### コマンド例

**MSVC 主系（BLE 有効、推奨）**：
```bash
export PATH="/e/tools/cmake/bin:/e/tools/bin:$PATH"
cd /e/dev/SonyHeadphonesClient
mkdir -p build-msvc

# configure（cl.exe + Win SDK の env activation を cmd 経由で）
cmd /c 'call E:\tools\msvc\devcmd.bat && cd /d E:\dev\SonyHeadphonesClient\build-msvc && cmake -G Ninja -DCMAKE_BUILD_TYPE=Release ..'

# ビルド（N200/8GB で 2〜3 分、SDL3+imgui 同梱で 309 ステップ）
cmd /c 'call E:\tools\msvc\devcmd.bat && cmake --build E:\dev\SonyHeadphonesClient\build-msvc --target SonyHeadphonesClient -j2'

# 実行（DLL 同梱不要）
./build-msvc/client/SonyHeadphonesClient.exe

# DLL 依存検証（vcruntime/msvcp/ucrt が出ないこと）
cmd /c 'call E:\tools\msvc\devcmd.bat && dumpbin /dependents E:\dev\SonyHeadphonesClient\build-msvc\client\SonyHeadphonesClient.exe'
```

**MinGW 副系（BLE 除外、fallback）**：
```bash
export PATH="/e/tools/mingw64/bin:/e/tools/cmake/bin:/e/tools/bin:$PATH"
cd /e/dev/SonyHeadphonesClient
mkdir -p build && cd build
cmake -G Ninja -DCMAKE_BUILD_TYPE=Release -DMDR_DISABLE_BLE=ON ..
cmake --build . --target SonyHeadphonesClient -j2
./client/SonyHeadphonesClient.exe
```

## 配布（GitHub Release 自動化）

`.github/workflows/release.yml` がタグ `v*` の push と `workflow_dispatch` で起動：

1. windows-latest + `ilammy/msvc-dev-cmd@v1` で MSVC v143 + Win SDK 環境を activation (windows-latest は VS 2022 + SDK プリインストール済)
2. `lukka/get-cmake@latest` で CMake + Ninja を確保
3. `cmake -G Ninja -DCMAKE_BUILD_TYPE=Release` で configure（`MDR_DISABLE_BLE` 指定なし = BLE 有効）→ `--target SonyHeadphonesClient -j2`
4. `dumpbin /dependents` で `vcruntime` / `msvcp` / `ucrtbase` が exe に残ってないか検証 — 残っていたら fail
5. `dist/` に exe + `settings.ini.sample` + `README.md` をまとめて 7-Zip で zip 化
6. tag push の場合：`softprops/action-gh-release@v2` で GitHub Release 作成、zip 添付
7. workflow_dispatch の場合：artifact としてアップロード（リリース作らず確認用）

リリース手順：
```bash
git tag -a v0.x.y -m "..."
git push origin v0.x.y
```

**workflow に `permissions: contents: write` 必須**（無いと release 作成が "Resource not accessible by integration" で失敗する。v0.1.0 で踏んで commit `af0658e` で修正済）。

リリース zip 命名：`SonyHeadphonesClient-vX.Y.Z-win-x64-portable.zip`

## i18n アーキテクチャ（Phase 1で導入）

### 構成ファイル

```
client/i18n/
├── Localization.hpp       # tr() / SetLocale() / LoadSettings() API
├── Localization.cpp       # X-macro でテーブル構築、ファイルIO
├── strings_keys.inc       # 全キー＋英語デフォルト（正本）
└── strings_ja.inc         # 日本語上書き
```

### 使い方

```cpp
#include "i18n/Localization.hpp"

ImGui::Text(i18n::tr("playback.title"));                         // テキストのみ
ImGui::TreeNodeEx(i18n::trIcon(PSI_VOLUME_UP, "header.now_playing").c_str()); // アイコン+テキスト
ImGui::Text(i18n::tr("header.battery_fmt"), batteryLevel);       // フォーマット文字列
fmt::format(fmt::runtime(i18n::tr("discovery.version_fmt")), ...); // fmtライブラリは fmt::runtime() 必須
```

### 新しい文字列を追加する手順

1. `strings_keys.inc` に `I18N_STR("category.name", "English text")` を追加
2. `strings_ja.inc` に同キーで日本語訳を追加（共通化したい場合は `common.*` を使用）
3. Client.cpp の該当箇所で `i18n::tr("category.name")` を使う
4. ビルド & 動作確認

### キー命名規則

- `tab.*` ：タブ名
- `header.*` ：上部メニュー、Now Playing、バッテリー
- `playback.*` ：再生タブ
- `sound.*` ：サウンドタブ（NC/AMB、EQ、DSEE等）
- `devices.*` ：デバイスタブ
- `system.*` ：システムタブ（言語、一般設定、Touch、ボタン等）
- `system.gs.*` ：機種ごと変動する一般設定の subject/summary
- `about.*` ：情報タブ
- `discovery.*` ：起動時の接続画面
- `connecting.*` / `disconnect.*` / `bugcheck.*` ：状態画面
- `audio_codec.*` / `dsee.*` / `battery.*` / `nc_sens.*` / `detect_sens.*` / `mode_out_time.*` / `eq.*` / `preset.*` / `function.*` / `auto_power_off.*` ：FormatEnum返り値
- `common.*` ：複数箇所で使う共通文字列（off/on/enabled/sensitivity/cancel/unknown_brackets）

### フォントロード

`client/Platform/Windows/PlatformWindows.cpp` の `clientPlatformLocateFontBinary` で
`%WINDIR%\Fonts\` から日本語フォントを優先順に試す：
1. `YuGothR.ttc` (Yu Gothic, Win10+)
2. `meiryo.ttc` (Win Vista+)
3. `msgothic.ttc` (XP+)

ImGui の `merge_config` で PlexSansIcon の上に重ね、欠落グリフ（漢字・かな）を補う。

### 言語切替UI と永続化

- 設定ファイル：exe と同じディレクトリの `settings.ini`（ポータブル運用）
- 中身：`locale=en` または `locale=ja` の1行
- UI：システムタブの一番上「言語」ツリーノードのコンボボックス
- 切替は即時反映（フォントは両言語をカバー済みなので再ロード不要）
- 起動時に `i18n::LoadSettings()`、選択時に `i18n::SaveSettings()`

## Phase 1 完了状態（2026-05-05）

- [x] **1a** i18n基盤（Localization.hpp/cpp + .inc + CMake組み込み）
- [x] **1b** 日本語フォント同梱（Win同梱フォント自動検出）
- [x] **1c** FormatEnum 10個 約80文字列の翻訳化
- [x] **1d** UI骨格 約120文字列の翻訳化（Discovery/Header/Playback/Sound/Devices/System/About/Disconnect/Bugcheck）
- [x] **1e** 言語切替UI ＋ 設定永続化

合計 **約200文字列** が日英スイッチ可能。動作確認：実機 WH/WF-1000XM6 で全タブ表示OK。

## Phase 3 完了状態（2026-05-06）— BLE GATT バックエンド + MSVC 移行

**動機**：Classic Bluetooth (RFCOMM) では届かない GATT サービス読み書き — 具体的には `Windows.Devices.Bluetooth.GenericAttributeProfile` 経由で XM6 が露出する追加プロファイル — を扱えるよう、`libmdr/src/Platform/Windows/PlatformWindowsBLE.cpp` (上流の C++/WinRT 実装、747 行) を有効ビルドする必要があった。MinGW では C++/WinRT projection ヘッダが入手できないため、toolchain ごと MSVC へ移行。

**注意 — 用語**：本実装は **BLE 4.0+ の GATT 制御チャネル** であって、**LE Audio (LC3 codec / Auracast / CIS / BIS) ではない**。LE Audio は `Windows.Media.Audio` 系 API + BT 5.2 ハードウェア + Win11 22H2+ ドライバが必要な別案件で、本フォークの scope 外。v0.2.0 直後の docs で「LE Audio 対応」と書いた箇所は誤記、v0.2.1 で訂正。

**制約**：C ドライブは一切消費不可。MSVC 公式インストーラは `%ProgramData%\Microsoft\VisualStudio\` 等に GB 単位で書き込むため使用不可。
→ [PortableBuildTools](https://github.com/Data-Oriented-House/PortableBuildTools) v2.10.2 で Microsoft 公式ペイロードから MSVC v143 + Windows SDK 10.0 を `E:\tools\msvc` (1.4 GB) に展開。サービス登録・レジストリ・C: 書き込みなし。

- [x] **3a** PortableBuildTools で `E:\tools\msvc` 展開 (MSVC 14.44.35207 + Win SDK 10.0.26100、`devcmd.bat` 自動生成)
- [x] **3b** ルート `CMakeLists.txt` に `CMAKE_MSVC_RUNTIME_LIBRARY=MultiThreaded$<...>` をグローバル設定 (CMP0091 NEW)
- [x] **3c** `build-msvc/` で BLE 入りビルド成功 (309/309 ステップ、`PlatformWindowsBLE.cpp` C++/WinRT コンパイル通過、exe 3.55 MB)
- [x] **3d** `dumpbin /dependents` で `vcruntime` / `msvcp` / `ucrtbase` 不要を確認 (`/MT` 静的リンク確認)
- [x] **3e** `.github/workflows/release.yml` を `ilammy/msvc-dev-cmd@v1` + `lukka/get-cmake@latest` ベースに置換、`MDR_DISABLE_BLE=ON` 削除、検証ロジックを `objdump` → `dumpbin` に切替
- [ ] **3f** 実機 WH / WF-1000XM6 で BLE GATT 接続 + 追加プロファイル動作検証（保留中）
- [ ] **3g** `v0.2.0` タグ push（実機検証通過後）

**MinGW 環境 (`E:\tools\mingw64`) は保守用に保持**。`MDR_DISABLE_BLE=ON` flag + `if (MINGW)` 分岐 (`-static`) も全て残しているので、いつでも fallback 可能。

## 注意

- upstream PR は予定なし（個人運用フォーク）
- README に商標 disclaimer・上流帰属あり。公開済 (`tenma2066-tech/SonyHeadphonesClient`) なので新規 commit は商標表記の整合性に注意
- Sony のファーム更新でプロトコル変動の可能性あり（非公式リバース）
