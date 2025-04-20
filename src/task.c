#include "../include/task.h"
#include <stdio.h>

static Task tasks[MAX_TASKS];
static int task_count = 0;
static int current_task = -1;
static int event_flags[MAX_EVENTS] = {0};

void task_create(void (*func)(void), int priority) {
    if (task_count >= MAX_TASKS) return;

    tasks[task_count].id = task_count;
    tasks[task_count].function = func;
    tasks[task_count].priority = priority;
    tasks[task_count].state = TASK_READY;
    tasks[task_count].delay = 0;
    tasks[task_count].wait_event = -1;
    tasks[task_count].started = 0;
    tasks[task_count].yields = 0;
    task_count++;
}

void task_yield() {
    tasks[current_task].yields++;
    if (setjmp(tasks[current_task].context) == 0) return;
}

void task_sleep(int ticks) {
    tasks[current_task].delay = ticks;
    tasks[current_task].state = TASK_WAITING;
    task_yield();
}

void task_wait_event(int event_id) {
    tasks[current_task].state = TASK_WAITING;
    tasks[current_task].wait_event = event_id;
    task_yield();
}

void task_signal_event(int event_id) {
    for (int i = 0; i < task_count; ++i) {
        if (tasks[i].state == TASK_WAITING && tasks[i].wait_event == event_id) {
            tasks[i].state = TASK_READY;
            tasks[i].wait_event = -1;
        }
    }
}

Task* get_tasks() { return tasks; }
int get_task_count() { return task_count; }
int* get_current_task_index() { return &current_task; }

void task_mark_finished() {
    tasks[current_task].state = TASK_FINISHED;
}