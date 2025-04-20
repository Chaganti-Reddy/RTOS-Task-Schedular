#include "../include/task.h"
#include "../include/scheduler.h"
#include <stdio.h>

void task1() {
    printf("Task 1 waiting for event 0\n");
    task_wait_event(0);
    printf("Task 1 resumed after event 0\n");
    task_yield();
}

void task2() {
    printf("Task 2 sleeping for 2 ticks\n");
    task_sleep(2);
    printf("Task 2 signaling event 0\n");
    task_signal_event(0);
    task_yield();
}

void task3() {
    for (int i = 0; i < 2; i++) {
        printf("Task 3 doing work: %d\n", i);
        task_yield();
    }
}

int main() {
    task_create(task1, 1);
    task_create(task2, 2);
    task_create(task3, 3);

    scheduler_run();
    printf("All tasks finished.\n");
    return 0;
}