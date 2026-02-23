#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(void) {
    printf("=== dup2() の実験 ===\n\n");

    // Step 1: 通常の出力
    printf("Step 1: この行は画面（stdout）に表示されます\n");
    printf("現在の stdout の FD: %d\n\n", 1);

    // Step 2: ファイルを開く
    printf("Step 2: test_dup2.txt を開きます...\n");
    int fd = open("test_dup2.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("open");
        return 1;
    }
    printf("ファイルが FD %d として開かれました\n\n", fd);

    // Step 3: dup2 を実行する前の状態
    printf("Step 3: dup2() を実行する前\n");
    printf("FD 1 (stdout) → 画面\n");
    printf("FD %d → test_dup2.txt\n\n", fd);

    // Step 4: stderr にメッセージを出力（これは dup2 の影響を受けない）
    fprintf(stderr, "Step 4: dup2(%d, 1) を実行します...\n", fd);
    fprintf(stderr, "（この行は stderr なので常に画面に表示されます）\n\n");

    // Step 5: dup2 を実行
    int result = dup2(fd, 1);
    fprintf(stderr, "dup2() の戻り値: %d\n", result);
    fprintf(stderr, "FD 1 (stdout) は test_dup2.txt に向けられました\n\n");

    // Step 6: fd を閉じる
    close(fd);
    fprintf(stderr, "FD %d を閉じました（FD 1 はまだ test_dup2.txt を指しています）\n\n", fd);

    // Step 7: この後の printf は test_dup2.txt に書き込まれる
    fprintf(stderr, "Step 7: これから printf() を実行します（画面には出ません）\n");
    printf("この行は test_dup2.txt に書き込まれます！\n");
    printf("画面には表示されません。\n");
    printf("なぜなら stdout (FD 1) が test_dup2.txt に向けられているからです。\n");

    fprintf(stderr, "\n=== 実験終了 ===\n");
    fprintf(stderr, "test_dup2.txt の内容を確認してください:\n");
    fprintf(stderr, "  cat test_dup2.txt\n");

    return 0;
}
