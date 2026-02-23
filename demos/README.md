# デモプログラム

シェル実装で学んだOS概念を実験・確認するためのプログラム集

## ディレクトリ構成

### fork/
プロセスの複製（fork）に関する実験
- `fork_demo.c` - fork() の動作確認（親と子で異なる変数値を持つ）

### fd/
ファイルディスクリプタとリダイレクションに関する実験
- `dup2_demo.c` - dup2() によるFDの付け替え実験

### buffer/
標準出力のバッファリングに関する実験
- `test_buffer.c` - fflush の有無による違い
- `demo_buffer.c` - バッファリングとパイプの挙動
- `progress_demo.c` - プログレスバーでのfflushの重要性
- `test_no_flush.sh` - バッファリング確認スクリプト

### pipe/
パイプ（プロセス間通信）に関する実験
- `pipe_fifo_demo.c` - パイプのFIFO（順序保証）確認
- `pipe_blocking_demo.c` - パイプのブロッキング動作確認
- `pipe_eof_demo.c` - パイプのEOF処理確認
- `pipe_interactive_demo.c` - 対話的なパイプ実験（未完成）

## ビルドと実行

各ディレクトリで：

```bash
cd demos/fork
gcc -o fork_demo fork_demo.c
./fork_demo
```

または、まとめてビルド：

```bash
cd demos/fork && gcc -o fork_demo fork_demo.c && cd ../..
cd demos/fd && gcc -o dup2_demo dup2_demo.c && cd ../..
cd demos/pipe && gcc -o pipe_fifo_demo pipe_fifo_demo.c && cd ../..
# ... など
```
