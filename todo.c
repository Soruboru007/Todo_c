#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "todo.h"

// タスクを追加する関数
void add_task(Task tasks[], int *count) {
    if (*count >= MAX_TASKS) {
        printf("タスクリストが満杯です。これ以上追加できません。\n");
        return;
    }
    
    Task new_task;
    new_task.id = *count + 1;
    new_task.completed = 0;
    
    printf("新しいタスクのタイトルを入力してください: ");
    fgets(new_task.title, TITLE_LENGTH, stdin);
    
    // 改行文字を削除
    size_t len = strlen(new_task.title);
    if (len > 0 && new_task.title[len - 1] == '\n') {
        new_task.title[len - 1] = '\0';
    }
    
    tasks[*count] = new_task;
    (*count)++;
    
    printf("タスク「%s」を追加しました。(ID: %d)\n", new_task.title, new_task.id);
}

// タスク一覧を表示する関数
void list_tasks(Task tasks[], int count) {
    if (count == 0) {
        printf("タスクがありません。\n");
        return;
    }
    
    printf("\n===== タスク一覧 =====\n");
    printf("%-5s %-50s %-10s\n", "ID", "タイトル", "状態");
    printf("--------------------------------------------------------------\n");
    
    for (int i = 0; i < count; i++) {
        printf("%-5d %-50s %-10s\n", 
               tasks[i].id, 
               tasks[i].title, 
               tasks[i].completed ? "完了" : "未完了");
    }
    
    // 統計情報を表示
    int completed_count = 0;
    for (int i = 0; i < count; i++) {
        if (tasks[i].completed) {
            completed_count++;
        }
    }
    printf("\n合計: %d個のタスク (完了: %d, 未完了: %d)\n", 
           count, completed_count, count - completed_count);
}

// タスクを完了にする関数
void complete_task(Task tasks[], int count) {
    if (count == 0) {
        printf("タスクがありません。\n");
        return;
    }
    
    int id;
    printf("完了にするタスクのIDを入力してください: ");
    if (scanf("%d", &id) != 1) {
        while (getchar() != '\n');
        printf("無効な入力です。\n");
        return;
    }
    getchar(); // 改行文字を消費
    
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (tasks[i].id == id) {
            if (tasks[i].completed) {
                printf("タスク「%s」は既に完了しています。\n", tasks[i].title);
            } else {
                tasks[i].completed = 1;
                printf("タスク「%s」を完了にしました。\n", tasks[i].title);
            }
            found = 1;
            break;
        }
    }
    
    if (!found) {
        printf("ID %d のタスクが見つかりません。\n", id);
    }
}

// タスクを削除する関数
void delete_task(Task tasks[], int *count) {
    if (*count == 0) {
        printf("タスクがありません。\n");
        return;
    }
    
    int id;
    printf("削除するタスクのIDを入力してください: ");
    if (scanf("%d", &id) != 1) {
        while (getchar() != '\n');
        printf("無効な入力です。\n");
        return;
    }
    getchar(); // 改行文字を消費
    
    int found_index = -1;
    for (int i = 0; i < *count; i++) {
        if (tasks[i].id == id) {
            found_index = i;
            break;
        }
    }
    
    if (found_index == -1) {
        printf("ID %d のタスクが見つかりません。\n", id);
        return;
    }
    
    // 確認
    printf("タスク「%s」を削除してもよろしいですか？ (y/n): ", tasks[found_index].title);
    char confirm;
    scanf(" %c", &confirm);
    getchar(); // 改行文字を消費
    
    if (confirm != 'y' && confirm != 'Y') {
        printf("削除をキャンセルしました。\n");
        return;
    }
    
    // タスクを削除（後ろの要素を前に詰める）
    for (int i = found_index; i < *count - 1; i++) {
        tasks[i] = tasks[i + 1];
    }
    (*count)--;
    
    // IDを再割り当て
    for (int i = 0; i < *count; i++) {
        tasks[i].id = i + 1;
    }
    
    printf("タスクを削除しました。\n");
}

// タスクをファイルに保存する関数
void save_tasks(Task tasks[], int count) {
    FILE *file = fopen("tasks.dat", "wb");
    if (file == NULL) {
        printf("ファイルを開けませんでした。\n");
        return;
    }
    
    // タスク数を書き込む
    fwrite(&count, sizeof(int), 1, file);
    
    // タスクデータを書き込む
    fwrite(tasks, sizeof(Task), count, file);
    
    fclose(file);
}

// タスクをファイルから読み込む関数
int load_tasks(Task tasks[]) {
    FILE *file = fopen("tasks.dat", "rb");
    if (file == NULL) {
        // ファイルが存在しない場合は0を返す
        return 0;
    }
    
    int count;
    // タスク数を読み込む
    if (fread(&count, sizeof(int), 1, file) != 1) {
        fclose(file);
        return 0;
    }
    
    // タスク数が有効範囲内かチェック
    if (count < 0 || count > MAX_TASKS) {
        fclose(file);
        return 0;
    }
    
    // タスクデータを読み込む
    if (fread(tasks, sizeof(Task), count, file) != (size_t)count) {
      fclose(file);
      return 0;
  }
    
    fclose(file);
    return count;
}