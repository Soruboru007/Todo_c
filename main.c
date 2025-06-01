#include <stdio.h>
#include <stdlib.h>
#include "todo.h"

int main() {
    Task tasks[MAX_TASKS];
    int task_count = 0;
    int choice;

    // 起動時にタスクをロード
    task_count = load_tasks(tasks);
    printf("TODOアプリケーションへようこそ！\n");
    printf("%d個のタスクをロードしました。\n\n", task_count);

    while (1) {
        printf("\n===== TODOメニュー =====\n");
        printf("1. タスクを追加\n");
        printf("2. タスク一覧を表示\n");
        printf("3. タスクを完了にする\n");
        printf("4. タスクを削除\n");
        printf("5. 保存して終了\n");
        printf("6. 保存せずに終了\n");
        printf("選択してください: ");
        
        if (scanf("%d", &choice) != 1) {
            // 入力エラーの処理
            while (getchar() != '\n');
            printf("無効な入力です。数字を入力してください。\n");
            continue;
        }
}