#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    int pipefd[2];

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(1);
    }

    printf("=== パイプのブロッキング実験 ===\n\n");

    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) {
        // 子プロセス: 読み取り側
        close(pipefd[1]);  // 書き込み側を閉じる

        char buf[100];
        printf("[子] パイプからの読み取りを開始...\n");
        printf("[子] データが来るまでブロック（待機）します\n\n");

        // ここでブロックする（親がデータを書き込むまで）
        int n = read(pipefd[0], buf, sizeof(buf) - 1);
        buf[n] = '\0';

        printf("[子] データを受信しました: \"%s\"\n", buf);

        close(pipefd[0]);
        _exit(0);

    } else {
        // 親プロセス: 書き込み側
        close(pipefd[0]);  // 読み取り側を閉じる

        printf("[親] 3秒待ってから書き込みます...\n");
        sleep(3);

        printf("[親] パイプにデータを書き込みます\n");
        write(pipefd[1], "Hello from parent!", 18);

        close(pipefd[1]);  // 閉じることでEOFを送る

        printf("[親] 書き込み完了、子の終了を待ちます\n");
        wait(NULL);
        printf("[親] 子プロセスが終了しました\n");
    }

    return 0;
}
