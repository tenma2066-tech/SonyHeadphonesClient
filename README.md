# SonyHeadphonesClient — 日本語フォーク

[mos9527/SonyHeadphonesClient](https://github.com/mos9527/SonyHeadphonesClient) (`rewrite` ブランチ) を土台にした **個人開発の非公式 PC クライアント**。日本語 UI 対応と Windows ポータブル版 (単一exe + 任意 `settings.ini`) の同梱を行っています。実機ターゲットは **WH-1000XM6 / WF-1000XM6**。

> [!IMPORTANT]
> Sony および "WH-1000XM..." 等の名称は Sony の登録商標です。本プロジェクトは Sony とは無関係の非公式ツールです。利用は自己責任で。

---

## ダウンロードと使い方

1. [Releases](../../releases) ページから最新の `SonyHeadphonesClient-vX.Y.Z-win-x64-portable.zip` を取得
2. zip を任意のフォルダに解凍
3. `SonyHeadphonesClient.exe` をダブルクリックで起動 — DLL の追加配置は不要

### 日本語で起動したい場合

zip に含まれる `settings.ini.sample` を `settings.ini` にリネームして exe と同じフォルダに置きます。中身：

```ini
locale=ja
```

`settings.ini` が無い場合は英語で起動します（システムタブの「言語」から日本語に切替も可能、その操作で `settings.ini` が自動生成されます）。

### 動作要件

- Windows 10 (1903+) / 11 — UCRT 標準搭載が前提
- Bluetooth Classic 接続のヘッドホン (LE Audio 非対応)
- 対応機種は upstream の [`docs/device-support`](docs/device-support) を参照

---

## 機能

upstream `rewrite` ブランチの全機能をそのまま継承：

- イコライザー (5/10 バンド + プリセット + Clear Bass)
- ノイズキャンセリング / 外音モード切替・外音レベル / 適応感度 (XM6)
- DSEE on/off、BGM、Cinema、リスニングモード
- Speak-to-Chat、ヘッドジェスチャー
- マルチポイント (2台同時接続)、ペアリング済みデバイス管理
- タッチセンサー / NC・AMB ボタン機能割当
- 装着検出、自動電源オフ、音声ガイド、Sidetone
- バッテリー表示 (本体 / L・R / ケース)、コーデック表示、Now Playing メタデータ

このフォーク独自の追加：

- **日本語 UI** — 約 200 文字列を翻訳。システムタブから即時切替可能
- **ポータブル化** — MinGW ランタイムを static link し DLL 同梱不要、`settings.ini` も exe 隣に保存

---

## 制限

- **LE Audio 接続非対応**：MinGW 環境で C++/WinRT が利用できないため、Windows BLE バックエンド (`PlatformWindowsBLE.cpp`) を除外しています。Classic Bluetooth でのみ動作します。XM6 が LE Audio で接続されている場合はペアリング設定で Classic に戻してください。
- **upstream PR 予定なし**：個人運用のため、本フォークから upstream への取り込み計画はありません。

---

## ソースからビルド

詳細は [`CLAUDE.md`](CLAUDE.md) を参照（必要ツールのバージョンや環境変数、典型的なハマりどころを記載）。要点のみ：

```bash
export PATH="/<MinGW>/bin:/<CMake>/bin:/<Ninja>/bin:$PATH"

cmake -G Ninja -B build -DCMAKE_BUILD_TYPE=Release -DMDR_DISABLE_BLE=ON
cmake --build build --target SonyHeadphonesClient -j2

./build/client/SonyHeadphonesClient.exe
```

GitHub Actions のリリースワークフローも同じ手順を実行します（`.github/workflows/release.yml`）。タグを `v*` 形式で push するとリリースが自動生成されます。

---

## 由来 / ライセンス

- **上流**：[mos9527/SonyHeadphonesClient](https://github.com/mos9527/SonyHeadphonesClient) (`rewrite` ブランチ) — そのさらに上流は [Plutoberth/SonyHeadphonesClient](https://github.com/Plutoberth/SonyHeadphonesClient)
- **ライセンス**：上流に従う (MIT)。本フォークの追加・改変部分も同条件で利用可能とします
- **非公式の注意**：Sony 公式アプリ "Sound Connect" の機能を独自に解析・再実装したものです。Sony によるファームウェア更新でプロトコルが変動した場合、動作しなくなる可能性があります
