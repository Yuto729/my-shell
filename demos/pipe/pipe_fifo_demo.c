#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(void) {
    int pipefd[2];

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(1);
    }

    printf("=== パイプのFIFO（順序保証）実験 ===\n\n");

    // 複数のデータを書き込む
    printf("[書き込み]\n");
    write(pipefd[1], "FIRST\n", 6);
    printf("  書き込み1: FIRST\n");

    write(pipefd[1], "SECOND\n", 7);
    printf("  書き込み2: SECOND\n");

    write(pipefd[1], "THIRD\n", 6);
    printf("  書き込み3: THIRD\n");

    printf("\n[読み取り]\n");

    // 順番に読み取る
    char buf[100];
    int n;

    n = read(pipefd[0], buf, 6);
    buf[n] = '\0';
    printf("  読み取り1: %s", buf);

    n = read(pipefd[0], buf, 7);
    buf[n] = '\0';
    printf("  読み取り2: %s", buf);

    n = read(pipefd[0], buf, 6);
    buf[n] = '\0';
    printf("  読み取り3: %s", buf);

    printf("\n結果: 書き込んだ順に読み取れた（FIFO）\n");

    close(pipefd[0]);
    close(pipefd[1]);

    return 0;
}
