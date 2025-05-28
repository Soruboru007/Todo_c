#ifndef TODO_H
#define TODO_H

#define MAX_TASKS 100
#define TITLE_LENGTH 100

typedef struct 
{
  int id;
  char title[TITLE_LENGTH];
  int completed;
}Task;

void add_task(Task tasks[], int *count);
void list_tasks(Task tasks[], int count);

#endif