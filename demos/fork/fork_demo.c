#include <stdio.h>
#include <unistd.h>

int main(void) {
    int counter = 0;

    printf("=== Before fork ===\n");
    printf("Counter = %d (PID=%d)\n\n", counter, getpid());

    pid_t pid = fork();  // ← ここで分岐

    // この下は2つのプロセスが実行する
    counter++;  // 両方のプロセスが counter をインクリメント

    printf("=== After fork ===\n");
    printf("PID=%d, pid変数=%d, counter=%d\n",
           getpid(), pid, counter);

    return 0;
}
