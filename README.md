# my-shell

OSの基礎概念を学ぶための、最小限のUnixシェル実装。

## 学習目標

- プロセスの生成と管理（fork, exec, wait）
- システムコールの理解
- ファイルディスクリプタとI/Oリダイレクション
- パイプとプロセス間通信
- シグナル処理

## 実装状況

### Phase 1: 基本的なREPLループ ✅

- [x] プロジェクトの基本構造
- [x] REPLループ（Read-Eval-Print Loop）
- [x] コマンドのパース（トークン化）
- [x] 単一コマンドの実行（fork + exec + wait）

### Phase 2: リダイレクション ✅

- [x] 出力リダイレクション（`>`, `>>`）
- [x] 入力リダイレクション（`<`）
- [x] ファイルディスクリプタ操作（`dup2`）

### Phase 3: パイプ 🚧

- [ ] パイプ（`|`）の実装
- [ ] 複数コマンドの連結

### Phase 4: シグナル処理 📋

- [ ] Ctrl+C（SIGINT）
- [ ] バックグラウンド実行（`&`）

### Phase 5: ビルトインコマンド 📋

- [ ] `cd`, `exit`, `export`

## ビルドと実行

```bash
make
./mysh
```

### 使用例

```bash
mysh> ls -la
mysh> echo Hello World
mysh> echo "test" > output.txt
mysh> cat < output.txt
mysh> ls >> log.txt
mysh> exit
```

## プロジェクト構成

```
my-shell/
├── main.c              # メインのシェルプログラム
├── Makefile            # ビルド設定
├── README.md           # このファイル
├── LEARNING.md         # 学習内容の詳細なまとめ
└── demos/              # 実験・デモプログラム
    ├── fork/           # fork関連の実験
    ├── fd/             # ファイルディスクリプタ/リダイレクト関連
    ├── buffer/         # バッファリング関連
    └── pipe/           # パイプ関連
```

## 学習リソース

### ドキュメント

- **[LEARNING.md](LEARNING.md)** - 実装を通じて学んだOS概念の詳細まとめ
  - プロセスモデル、fork/exec/wait
  - ファイルディスクリプタ
  - リダイレクションとパイプの仕組み
  - 図解付きで理解しやすく整理

### デモプログラム

- **[demos/](demos/)** - OS概念を実験・確認するためのプログラム集
  - `fork/` - プロセス複製の動作確認
  - `fd/` - ファイルディスクリプタとdup2の実験
  - `buffer/` - 標準出力のバッファリング確認
  - `pipe/` - パイプのFIFO、ブロッキング、EOF確認

詳細は [demos/README.md](demos/README.md) を参照

## 参考資料

- [Linux man pages](https://man7.org/linux/man-pages/)
- [fork(2)](https://man7.org/linux/man-pages/man2/fork.2.html)
- [exec(3)](https://man7.org/linux/man-pages/man3/exec.3.html)
- [pipe(2)](https://man7.org/linux/man-pages/man2/pipe.2.html)
- [dup2(2)](https://man7.org/linux/man-pages/man2/dup2.2.html)
