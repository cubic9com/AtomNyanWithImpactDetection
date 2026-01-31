[衝撃を検知して表情を変えるｱﾄﾑﾆｬﾝ（AtomNyan）です。](https://x.com/cubic9com/status/2017193857096761678)

※. [ｱﾄﾑﾆｬﾝ（AtomNyan）](https://x.com/search?q=%23%EF%BD%B1%EF%BE%84%EF%BE%91%EF%BE%86%EF%BD%AC%EF%BE%9D) とは、[aokko2000](https://x.com/aokko2000) さんが作成した [AtomS3](https://docs.m5stack.com/ja/core/AtomS3) と組み合わせて作る可愛いマスコットです。

このプロジェクトは [Takao Akaki](https://github.com/mongonta0716) 様の [m5stack-avatar-mic](https://github.com/mongonta0716/m5stack-avatar-mic) をフォークして、衝撃検知による表情変更処理を追加したものです。

差分の多くは `impact_handler.h` 、 `impact_handler.cpp` に集中させており、 `main.cpp` の修正箇所はわずかです。


# 対応デバイス

- [AtomS3](https://docs.m5stack.com/ja/core/AtomS3) + [Atomic Echo Base](https://docs.m5stack.com/ja/atom/Atomic%20Echo%20Base) + [Atomic Battery Base](https://docs.m5stack.com/en/atom/Atomic%20Battery%20Base)

# ケース

- [ｱﾄﾑﾆｬﾝ V2 Takao](https://booth.pm/en/items/7887161)

# 環境

- [Visual Studio Code](https://code.visualstudio.com/) + [PlatformIO](https://platformio.org/)

## ライブラリ
- M5Stack-Avatar v0.9.2
- M5Unified v0.1.16

## 効果音
- 喜び用音声
    - 元ファイル: [ANMLCat_Cat meow made with mouth (ID 0926)_BigSoundBank.com.wav](https://bigsoundbank.com/cat-meow-made-with-mouth-s0926.html)
    - クレジット:
        - [Additional sounds: Joseph SARDIN - BigSoundBank.com](https://bigsoundbank.com/licenses.html)
        - Licensed under [Creative Commons CC0 1.0 Universal](https://creativecommons.org/publicdomain/zero/1.0/)
- 怒り用音声
    - 元ファイル: [ANMLCat_Little meow of a cat 10 (ID 1480)_BigSoundBank.com.wav](https://bigsoundbank.com/little-meow-of-a-cat-10-s1480.html)
    - クレジット:
        - [Additional sounds: Joseph SARDIN - BigSoundBank.com](https://bigsoundbank.com/licenses.html)
        - Licensed under [Creative Commons CC0 1.0 Universal](https://creativecommons.org/publicdomain/zero/1.0/)

# 使い方

1. Atomic Battery Baseの5pinの方を切り取ります（Atomic Echo Baseの底部には4ピンのコネクタしかないため）。

1. AtomS3にAtomic Echo Baseを接続します。

1. Atomic Echo BaseにAtomic Battery Baseを接続します。

1. 全体をケース（ [ｱﾄﾑﾆｬﾝ V2 Takao](https://booth.pm/en/items/7887161) ）に格納します。

1. リポジトリをクローンします:
    ```sh
    git clone https://github.com/cubic9com/AtomNyanWithImpactDetection.git
    cd AtomNyanWithImpactDetection
    ```
1. まだインストールしていない場合は、[Visual Studio Code](https://code.visualstudio.com/) をインストールします。

1. Visual Studio Code でプロジェクトを開きます:
    ```sh
    code .
    ```

1. `PlatformIO IDE` 拡張機能をインストールします:
    - 左サイドバーの「拡張機能」ビュー (`Ctrl+Shift+X`) を開きます。
    - `PlatformIO IDE` を検索してインストールします。

1. PlatformIO Home を開きます:
    - 左のアクティビティバーで PlatformIO アイコンをクリックします。
    - 左のメインサイドバーから `QUICK ACCESS > PIO Home > Open` を選択します。

1. プロジェクトを開きます:
    - 右のエディターグループ内の `PIO HOME` タブで `Open Project` をクリックします。
    - クローンした `AtomNyanWithImpactDetection` プロジェクトフォルダーを選択します。

1. プロジェクトをビルド＆アップロードします:
    - 左のメインサイドバーから `PROJECT TASKS > m5stack-atoms3-release > General > Upload` を選択します。

# LICENSE
[MIT](https://github.com/cubic9com/AtomNyanWithImpactDetection/blob/main/LICENSE)

# Author

[Takao Akaki](https://github.com/mongonta0716)

衝撃検知による表情変更部分： [きゅーこん](https://github.com/cubic9com)
