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
        getchar(); // 改行文字を消費
        
        switch (choice) {
            case 1:
                add_task(tasks, &task_count);
                break;
            case 2:
                list_tasks(tasks, task_count);
                break;
            case 3:
                complete_task(tasks, task_count);
                break;
            case 4:
                delete_task(tasks, &task_count);
                break;
            case 5:
                save_tasks(tasks, task_count);
                printf("タスクを保存しました。\n");
                printf("アプリケーションを終了します。\n");
                return 0;
            case 6:
                printf("保存せずに終了します。よろしいですか？ (y/n): ");
                char confirm;
                scanf(" %c", &confirm);
                if (confirm == 'y' || confirm == 'Y') {
                    printf("アプリケーションを終了します。\n");
                    return 0;
                }
                break;
            default:
                printf("無効な選択です。1-6の数字を入力してください。\n");
        }
    }
    
    return 0;
}