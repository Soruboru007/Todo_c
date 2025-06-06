#ifndef TODO_H
#define TODO_H

#define MAX_TASKS 100
#define TITLE_LENGTH 100

typedef struct {
    int id;
    char title[TITLE_LENGTH];
    int completed; // 0: 未完了, 1: 完了
} Task;

// 関数のプロトタイプ宣言
void add_task(Task tasks[], int *count);
void list_tasks(Task tasks[], int count);
void complete_task(Task tasks[], int count);
void delete_task(Task tasks[], int *count);
void save_tasks(Task tasks[], int count);
int load_tasks(Task tasks[]);

#endif