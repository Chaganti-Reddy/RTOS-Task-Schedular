#ifndef TASK_H
#define TASK_H

#include <setjmp.h>

#define MAX_TASKS 10
#define MAX_EVENTS 5

typedef enum {
    TASK_READY,
    TASK_RUNNING,
    TASK_WAITING,
    TASK_FINISHED
} TaskState;

typedef struct Task {
    int id;
    TaskState state;
    int priority;
    int delay;
    int wait_event;
    jmp_buf context;
    void (*function)(void);
    int started;
    int yields;
} Task;

void task_create(void (*func)(void), int priority);
void task_yield();
void task_sleep(int ticks);
void task_wait_event(int event_id);
void task_signal_event(int event_id);
Task* get_tasks();
int get_task_count();
int* get_current_task_index();
void task_mark_finished();

#endif