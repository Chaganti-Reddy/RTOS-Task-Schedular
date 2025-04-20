#include "../include/scheduler.h"
#include "../include/task.h"
#include <stdio.h>
#include <setjmp.h>

extern Task* get_tasks();
extern int get_task_count();
extern int* get_current_task_index();
extern void task_mark_finished();

void tick() {
    Task* tasks = get_tasks();
    int count = get_task_count();
    for (int i = 0; i < count; ++i) {
        if (tasks[i].state == TASK_WAITING && tasks[i].delay > 0) {
            tasks[i].delay--;
            if (tasks[i].delay == 0) {
                tasks[i].state = TASK_READY;
            }
        }
    }
}

void scheduler_run() {
    Task* tasks = get_tasks();
    int task_count = get_task_count();
    int* current_task = get_current_task_index();

    while (1) {
        int all_finished = 1;
        int best_priority = -1;
        int selected = -1;

        for (int i = 0; i < task_count; ++i) {
            if ((tasks[i].state == TASK_READY || tasks[i].state == TASK_RUNNING) && tasks[i].priority > best_priority) {
                best_priority = tasks[i].priority;
                selected = i;
            }
        }

        if (selected != -1) {
            all_finished = 0;
            *current_task = selected;
            tasks[selected].state = TASK_RUNNING;

            if (!tasks[selected].started) {
                tasks[selected].started = 1;
                if (setjmp(tasks[selected].context) == 0) {
                    tasks[selected].function();
                    task_mark_finished();
                }
            } else {
                longjmp(tasks[selected].context, 1);
            }
        }

        tick();
        if (all_finished) break;
    }

    printf("\nTask Statistics:\n");
    for (int i = 0; i < task_count; ++i) {
        printf("Task %d -> Yields: %d\n", tasks[i].id, tasks[i].yields);
    }
}