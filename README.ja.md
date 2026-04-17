# localtimes-cli

`localtimes-cli` は、様々なタイムゾーンの現在時刻を表示する、C言語で書かれたシンプルなコマンドラインツールです。標準Cライブラリのタイムゾーン処理を使用しており、設定により特定の「重要な」タイムゾーンや「現在」のタイムゾーンをハイライト表示することができます。

## 特徴

- 複数のタイムゾーンの現在時刻を表示。
- 表示するタイムゾーンのリストを設定可能。
- ハイライト表示のサポート:
  - **緑色**: 現在のタイムゾーン。
  - **黄色**: 重要なタイムゾーン（16色 ANSI のため、基本的な端末でも表示されます）。
- シンプルで依存関係が少ない（標準CおよびPOSIXを使用）。

## 必須条件

- Cコンパイラ (例: GCC)。
- `make` ユーティリティ。
- POSIX準拠の環境 (`setenv`, `gettimeofday` などを使用するため)。

## インストール

1. リポジトリをクローンします:
   ```bash
   git clone https://github.com/c1t0d0s0/localtimes-cli.git
   cd localtimes-cli
   ```

2. プロジェクトをビルドしてインストールします:
   ```bash
   make
   make install
   ```
   *注意: これにより `localtimes` バイナリが `~/bin` にインストールされます。*

## 設定

このツールは `config.yml` で設定します。ビルド時に `Makefile` がこのファイルを解析して、ヘッダーファイル (`zones.inc`) を生成します。

- `timezones`: 表示する IANA タイムゾーン名のリスト。
- `color.current`: 緑色でハイライトするタイムゾーン。
- `color.important`: 黄色でハイライトするタイムゾーンのリスト。

`config.yml` の例:
```yaml
timezones:
  - "UTC"
  - "Asia/Tokyo"
  - "America/Los_Angeles"
color:
  current: "Asia/Tokyo"
  important:
    - "America/Los_Angeles"
```

*注意: `config.yml` を変更した後は、変更を適用するために再度 `make` を実行する必要があります。*

## 使い方

インストールされたバイナリを実行します:
```bash
localtimes
```

## ライセンス

このプロジェクトは [LICENSE](LICENSE) ファイルの通りにライセンスされています。
