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

}