#include <stdio.h>
#include <unistd.h>

int main(void) {
    // Test 1: fflush なし
    fprintf(stderr, "[Test 1] Starting test without fflush...\n");
    printf("Message 1 (no fflush)");  // 改行なし、fflushなし
    sleep(2);
    printf(" [2秒後]\n");

    sleep(1);

    // Test 2: fflush あり
    fprintf(stderr, "\n[Test 2] Starting test with fflush...\n");
    printf("Message 2 (with fflush)");  // 改行なし
    fflush(stdout);  // 即座に出力される
    sleep(2);
    printf(" [2秒後]\n");

    return 0;
}
