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

    printf("=== パイプのEOF実験 ===\n\n");

    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) {
        // 子プロセス: 読み取り側
        close(pipefd[1]);  // 書き込み側を閉じる

        char buf[100];
        int n;
        int count = 0;

        printf("[子] パイプから読み取りを開始\n");

        while (1) {
            n = read(pipefd[0], buf, sizeof(buf) - 1);

            if (n == 0) {
                // EOF（書き込み側が全て閉じられた）
                printf("[子] EOF を受信（read() が 0 を返した）\n");
                printf("[子] 書き込み側が閉じられたので終了します\n");
                break;
            }

            buf[n] = '\0';
            count++;
            printf("[子] 読み取り%d: \"%s\"\n", count, buf);
        }

        close(pipefd[0]);
        _exit(0);

    } else {
        // 親プロセス: 書き込み側
        close(pipefd[0]);  // 読み取り側を閉じる

        printf("[親] データを3回書き込みます\n");
        write(pipefd[1], "Data 1\n", 7);
        sleep(1);

        write(pipefd[1], "Data 2\n", 7);
        sleep(1);

        write(pipefd[1], "Data 3\n", 7);
        sleep(1);

        printf("[親] 書き込み側のFDを閉じます（EOFを送る）\n");
        close(pipefd[1]);

        wait(NULL);
        printf("[親] 子プロセスが終了しました\n");
    }

    return 0;
}
