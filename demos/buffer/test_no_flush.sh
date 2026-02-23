#!/bin/bash
# このスクリプトは、fflushなしのシェルの挙動を確認するためのもの

echo "=== Testing shell WITHOUT fflush ==="
echo "プロンプトが即座に表示されるか確認してください"
echo ""

# シェルを起動（バックグラウンドではなく、標準入力をパイプに接続）
(
    sleep 1
    echo "hello"
    sleep 1
    echo "world"
    sleep 1
    echo "exit"
) | ./mysh

echo ""
echo "=== 観察ポイント ==="
echo "プロンプト 'mysh>' が入力の前に表示されましたか？"
echo "それとも入力と同時/後に表示されましたか？"
