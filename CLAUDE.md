# SonyHeadphonesClient (mos9527 fork) — 個人開発フォーク

mos9527/SonyHeadphonesClient (`rewrite` ブランチ) を土台にした個人プロジェクト。**スコープは日本語化 (i18n) と Windows ポータブル配布の 2 点のみ** — UI/UX 改修 (Phase 2 系) は明示的に却下済、自発提案しないこと。
ベースはMITライセンス。実機ターゲットは **WH-1000XM6 / WF-1000XM6**。

## リポジトリ位置

ローカル：`E:\dev\SonyHeadphonesClient\`、ブランチ `rewrite`。

| remote | URL | 用途 |
|---|---|---|
| `origin` | `https://github.com/tenma2066-tech/SonyHeadphonesClient` | 自分のフォーク。push 先 |
| `upstream` | `https://github.com/mos9527/SonyHeadphonesClient` | 上流。fetch のみ |

`gh` CLI は `tenma2066-tech` で認証済（`repo` + `workflow` scope）。`gh` 系コマンドはデフォルトで上流を見るため `--repo tenma2066-tech/SonyHeadphonesClient` を明示すること。

## ビルド

### 必要ツール（すべて E:\tools にポータブル配置済み）

- MinGW-w64 GCC 16.1.0 UCRT (winlibs) → `E:\tools\mingw64\bin`
- CMake 4.3.2 → `E:\tools\cmake\bin`
- Ninja 1.13.2 → `E:\tools\bin\ninja.exe`

### PATH（bash）

```bash
export PATH="/e/tools/mingw64/bin:/e/tools/cmake/bin:/e/tools/bin:$PATH"
```

### 既知のハマりどころ

1. **C++/WinRTヘッダ不足**：MinGW環境では `winrt/Windows.Foundation.h` が無く `PlatformWindowsBLE.cpp` がコンパイル不可。
   → CMake オプション `-DMDR_DISABLE_BLE=ON` でBLEバックエンド除外（スタブ `PlatformWindowsBLE_stub.cpp` に差替）。
   → Classic Bluetooth で WH/WF-1000XM6 動作確認済み。LE Audio接続は不可。

2. **MinGW ランタイムは static link 済**：`-static` を `client/CMakeLists.txt` で適用。
   `libgcc_s_seh-1.dll` / `libstdc++-6.dll` / `libwinpthread-1.dll` の同梱は不要。exe 単独で起動可能。

3. **git の dubious ownership**：E ドライブが ownership 非記録のため `safe.directory = *` を `git config --global` 設定済み。

### コマンド例

```bash
export PATH="/e/tools/mingw64/bin:/e/tools/cmake/bin:/e/tools/bin:$PATH"
cd /e/dev/SonyHeadphonesClient

# 初回（既に build/ にdeps揃ってる場合は skip）
mkdir -p build && cd build
cmake -G Ninja -DCMAKE_BUILD_TYPE=Release -DMDR_DISABLE_BLE=ON ..

# ビルド（N200/8GBで5-15分、-j2推奨）
cmake --build . --target SonyHeadphonesClient -j2

# 実行（DLL同梱不要）
./build/client/SonyHeadphonesClient.exe
```

## 配布（GitHub Release 自動化）

`.github/workflows/release.yml` がタグ `v*` の push と `workflow_dispatch` で起動：

1. windows-latest + MSYS2 UCRT64 セットアップ（ローカルと同等の MinGW）
2. `cmake -DMDR_DISABLE_BLE=ON` で configure → `--target SonyHeadphonesClient -j2`
3. `objdump -p` で MinGW DLL 依存（libgcc / libstdc++ / libwinpthread）が exe に残ってないか検証 — 残っていたら fail
4. `dist/` に exe + `settings.ini.sample` + `README.md` をまとめて zip 化
5. tag push の場合：`softprops/action-gh-release@v2` で GitHub Release 作成、zip 添付
6. workflow_dispatch の場合：artifact としてアップロード（リリース作らず確認用）

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

## 注意

- upstream PR は予定なし（個人運用フォーク）
- README に商標 disclaimer・上流帰属あり。公開済 (`tenma2066-tech/SonyHeadphonesClient`) なので新規 commit は商標表記の整合性に注意
- LE Audio 接続は MinGW で C++/WinRT が使えないため非対応。`PlatformWindowsBLE.cpp` の本実装は将来検討
- Sony のファーム更新でプロトコル変動の可能性あり（非公式リバース）
