# RTOS-like Task Scheduler in C

## Project Overview

This is a **cooperative, RTOS-style task scheduler** written in pure C — no OS, no external libraries, no hardware dependencies.  It simulates key features of a real embedded OS: context switching, priority-based scheduling, delays, and event-driven task synchronization.

---

## Key Concepts

- **setjmp/longjmp** – used to simulate context switching between tasks
- **Task Control Blocks** – holds state like priority, delay, context, etc.
- **Cooperative Scheduling** – tasks voluntarily yield or wait
- **Priority Scheduling** – higher priority tasks run before lower ones
- **Task Delays** – simulate sleeping for N ticks
- **Event Signaling** – tasks can wait for and signal events (e.g. semaphores)

---

## Features Implemented

| Feature                  | Description                                               |
|--------------------------|-----------------------------------------------------------|
| Context Switching      | Uses `setjmp/longjmp` to switch between task functions    |
| Round-Robin Scheduling | Selects tasks in a loop (if equal priority)              |
| Priority-Based Exec    | Higher priority tasks run first                           |
| Delays (`sleep`)       | Simulates task blocking for `n` ticks                     |
| Yielding               | Tasks manually yield control                              |
| Event Wait/Signal      | Tasks can wait for and signal specific events             |
| Yield Stats           | Track how often each task yields                          |

---

## Project Structure

```
rtos_scheduler/
├── include/
│   ├── task.h         # Task structures and API
│   └── scheduler.h    # Scheduler API
├── src/
│   ├── task.c         # Task logic (create, yield, sleep, event)
│   └── scheduler.c    # Main scheduling logic
├── test/
│   └── test_tasks.c   # Sample tasks (demo main program)
├── Makefile           # Easy build system
└── README.md          # This file!
```

---

## Build & Run

### Requirements:
- Any C compiler (`gcc` recommended)
- Make (optional but convenient)

### Compile & Run
```bash
make
./rtos
```

---

## Example Output

```
Task 3 doing work: 0
Task 3 doing work: 1
Task 2 sleeping for 2 ticks
Task 1 waiting for event 0
Task 3 doing work: 0
Task 3 doing work: 1
Task 2 signaling event 0
Task 1 resumed after event 0
All tasks finished.

Task Statistics:
Task 0 -> Yields: 2
Task 1 -> Yields: 2
Task 2 -> Yields: 2
```

---

## Potential Extensions

- Stack simulation using heap (`malloc`-based context)
- CLI-based task injection (dynamic creation)
- Preemptive scheduling simulation via signals/timers
- Logging task traces to a file for analysis
- Resource semaphores and mutex simulation

---

## License

Open source & free to use under MIT License.
