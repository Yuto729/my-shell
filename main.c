#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

#define MAX_LINE 1024
#define MAX_ARGS 64

// リダイレクションの種類
typedef enum {
    REDIRECT_NONE = 0,
    REDIRECT_OUT,      // >
    REDIRECT_IN,       // <
    REDIRECT_APPEND    // >>
} redirect_type_t;

// リダイレクション情報
typedef struct {
    redirect_type_t type;
    char *filename;
} redirect_t;

// コマンド情報
typedef struct {
    char *args[MAX_ARGS];
    int argc;
    redirect_t redirect;
} command_t;

// コマンドをパースして command_t 構造体に格納する
// 戻り値: 成功時 0、失敗時 -1
int parse_command(char *line, command_t *cmd) {
    cmd->argc = 0;
    cmd->redirect.type = REDIRECT_NONE;
    cmd->redirect.filename = NULL;

    char *token = strtok(line, " \t");

    while (token != NULL) {
        // リダイレクション記号をチェック
        if (strcmp(token, ">") == 0) {
            cmd->redirect.type = REDIRECT_OUT;
            token = strtok(NULL, " \t");
            if (token == NULL) {
                fprintf(stderr, "Error: missing filename after >\n");
                return -1;
            }
            cmd->redirect.filename = token;
            token = strtok(NULL, " \t");
            continue;
        } else if (strcmp(token, "<") == 0) {
            cmd->redirect.type = REDIRECT_IN;
            token = strtok(NULL, " \t");
            if (token == NULL) {
                fprintf(stderr, "Error: missing filename after <\n");
                return -1;
            }
            cmd->redirect.filename = token;
            token = strtok(NULL, " \t");
            continue;
        } else if (strcmp(token, ">>") == 0) {
            cmd->redirect.type = REDIRECT_APPEND;
            token = strtok(NULL, " \t");
            if (token == NULL) {
                fprintf(stderr, "Error: missing filename after >>\n");
                return -1;
            }
            cmd->redirect.filename = token;
            token = strtok(NULL, " \t");
            continue;
        }

        // 通常の引数として追加
        if (cmd->argc >= MAX_ARGS - 1) {
            fprintf(stderr, "Error: too many arguments\n");
            return -1;
        }

        cmd->args[cmd->argc] = token;
        cmd->argc++;

        token = strtok(NULL, " \t");
    }

    // 配列の終端にNULLを設定（exec用）
    cmd->args[cmd->argc] = NULL;

    return 0;
}

// コマンドを実行する（fork + exec + wait）
// 戻り値: 成功時 0、失敗時 -1
int execute_command(command_t *cmd) {
    pid_t pid = fork();

    if (pid == 0) {
        // 子プロセス
        fprintf(stderr, "[Child] PID=%d, Parent PID=%d, executing: %s\n",
                getpid(), getppid(), cmd->args[0]);

        // リダイレクション処理
        if (cmd->redirect.type != REDIRECT_NONE) {
            int fd;

            if (cmd->redirect.type == REDIRECT_OUT) {
                // 出力リダイレクト（上書き）
                fd = open(cmd->redirect.filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (fd < 0) {
                    perror("open");
                    exit(1);
                }
                dup2(fd, 1);  // stdout を fd に向ける
                close(fd);
            } else if (cmd->redirect.type == REDIRECT_IN) {
                // 入力リダイレクト
                fd = open(cmd->redirect.filename, O_RDONLY);
                if (fd < 0) {
                    perror("open");
                    exit(1);
                }
                dup2(fd, 0);  // stdin を fd に向ける
                close(fd);
            } else if (cmd->redirect.type == REDIRECT_APPEND) {
                // 出力リダイレクト（追記）
                fd = open(cmd->redirect.filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
                if (fd < 0) {
                    perror("open");
                    exit(1);
                }
                dup2(fd, 1);  // stdout を fd に向ける
                close(fd);
            }
        }

        execvp(cmd->args[0], cmd->args);
        // execvp が戻ってきたら失敗
        perror("execvp");
        exit(1);
    } else if (pid > 0) {
        // 親プロセス
        printf("[Parent] PID=%d, Child PID=%d, waiting...\n",
               getpid(), pid);
        wait(NULL);
        printf("[Parent] Child %d finished\n", pid);
    } else {
        // fork 失敗
        perror("fork");
        return -1;
    }

    return 0;
}

int main(void) {
    char line[MAX_LINE];

    printf("my-shell started. Type 'exit' to quit.\n");

    // REPL: Read-Eval-Print Loop
    while (1) {
        // プロンプト表示
        printf("mysh> ");
        fflush(stdout);  // バッファをフラッシュして即座に表示

        // 入力を読み取る
        if (fgets(line, sizeof(line), stdin) == NULL) {
            // EOF (Ctrl+D) が入力された
            printf("\n");
            break;
        }

        // 末尾の改行を除去
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }

        // 空行は無視
        if (strlen(line) == 0) {
            continue;
        }

        // exitコマンドで終了
        if (strcmp(line, "exit") == 0) {
            printf("Goodbye!\n");
            break;
        }

        // コマンドをパース
        command_t cmd = {0};
        if (parse_command(line, &cmd) < 0) {
            continue;
        }

        // コマンドが空の場合は無視
        if (cmd.argc == 0) {
            continue;
        }

        // コマンドを実行
        if (execute_command(&cmd) < 0) {
            fprintf(stderr, "Error: failed to execute command\n");
        }
    }

    return 0;
}
