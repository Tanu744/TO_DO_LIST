#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100           // Maximum number of tasks
#define TASK_LENGTH 100   // Maximum length of each task

typedef struct {
    char tasks[MAX][TASK_LENGTH];
    int top;
} Stack;

void initStack(Stack *s) {
    s->top = -1;  // Initialize stack as empty
}

int push(Stack *s, const char *task) {
    if (s->top == MAX - 1) {
        printf("Stack overflow. Cannot add more tasks.\n");
        return -1;
    }
    s->top++;
    strncpy(s->tasks[s->top], task, TASK_LENGTH);
    s->tasks[s->top][TASK_LENGTH - 1] = '\0';
    return 0;
}

int removeTask(Stack *s, int taskNumber) {
    if (s->top == -1) {
        printf("No tasks to remove.\n");
        return -1;
    }
    if (taskNumber < 1 || taskNumber > s->top + 1) {
        printf("Invalid task number.\n");
        return -1;
    }
    for (int i = taskNumber - 1; i < s->top; i++) {
        strncpy(s->tasks[i], s->tasks[i + 1], TASK_LENGTH);
    }
    s->top--;
    return 0;
}

void displayStack(const Stack *s) {
    if (s->top == -1) {
        printf("No tasks to display.\n");
        return;
    }
    printf("To-Do List:\n");
    for (int i = s->top; i >= 0; i--) {
        printf("%d: %s\n", s->top - i + 1, s->tasks[i]);
    }
}

int main() {
    Stack s;
    initStack(&s);
    char task[TASK_LENGTH];
    int taskNumber;

    printf("Enter initial tasks for the to-do list. Enter 'done' to finish.\n");

    while (1) {
        printf("Enter a task: ");
        fgets(task, TASK_LENGTH, stdin);
        task[strcspn(task, "\n")] = '\0';
        if (strcmp(task, "done") == 0) break;
        if (push(&s, task) == 0) {
            printf("Task added successfully.\n");
        }
    }

    printf("\nInitial To-Do List:\n");
    displayStack(&s);

    while (1) {
        printf("\nEnter the task number to remove: ");
        scanf("%d", &taskNumber);
        getchar();
        if (removeTask(&s, taskNumber) == 0) {
            printf("Task removed successfully.\n");
            break;
        }
    }

    printf("\nTo-Do List after removing the task:\n");
    displayStack(&s);
    printf("\nExiting the program.\n");
    return 0;
}
