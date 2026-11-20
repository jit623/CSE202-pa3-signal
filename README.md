# Programming Assignment 3 (Exceptional Control Flow: Process Control and Signals) 
 

## Student Learning Outcomes
1) Create processes using the system call `fork()`
2) Send signals from a process to another using the system call `sigqueue()`
3) Install portable signal handlers using `sigaction()`
4) Write signal handlers that follow the guidelines for writing async signal-safe signal handlers

## Assignment Description
Write a C program, `prog3.c`, to create `NUMCHILDREN` processes (4, 8, or 16) that send a random signal with an integer value to the parent process. The parent process receives the signals and send a `SIGUSR1` with an integer value to each sender process.

In the parent process, you will need to install the same signal handler to catch all catchable signals (the exceptions are: `SIGCHLD`, as we want the default behavior for reaping, and `SIGSTOP` and `SIGKILL` for which the default behavior cannot be changed).

In each child process, you will randomly select a signal to send to the parent process with an integer value equal to `(i*20)` where `i` is the child index. Do not send any of the following signals from the child processes: `SIGUSR1`, `SIGSTOP`, `SIGKILL`, and `SIGCHLD`. After sending the signal, the child process will pause until the signal `SIGUSR1` is received from the parent process, then exits with status 0

Then, in the parent process, you will need to reap all the child processes using `wait()` or `waitpid()`. The status of each child process, when reaped, must be printed.

In the signal handler, if the received signal is `SIGUSR1`, print a message indicating that the child process received a `SIGUSR1` signal and the integer value received with the signal. If the received signal is not `SIGUSR1`, the parent process prints a message about the signal and the integer value received. Then, the parent process sends back a `SIGUSR1` signal to the sending process with an integer value equal to the received value multiplied by 3. The parent process accumulates the values received from the children in a global variable `total` printed at the end before returning from the main method.

A skeleton `prog3.c` file is provided that contains the declaration of an array to hold the signal names and the prototypes of the wrapper functions for all the system calls to be used in this assignment.

Your signal handler function must be named `signal_handler` and you must use `sigaction()` to install the handler (`signal()` is not allowed. Use the wrapper function `Signal()` that uses `sigaction()` available on the slides and in the textbook)

You must write an **async-signal-safe** signal handler. Follow the guidelines for writing async-signal-safe handlers covered in class and available in the textbook. 
You must put comments in your signal handler function describing which guidelines you followed to create an async-signal-safe handler; if you feel one or more rules do not need to be followed, explain your rationale. 

The initial repository contains the following files:
- `prog3.c` where you will define the main method, the signal handler function, and the system call wrapper functions
- `Makefile` to compile and test `prog3.c`. Run `make test`: it compiles `prog3.c` with the macro `NUMCHILDREN` defined at compile time, runs it with `NUMCHILDREN` = 4 and then 16, and saves the output of each run to `output_4` and `output_16`. These files are checked by the script file `checkOutput.pl`. Run `make test` to make sure your code passes all the tests.
- `checkOutput.pl`, a Perl script to compare the file output to the reference output and generate a score out of 40 (20 for each run). The expected output for `NUMCHILDREN=8` is provided below for your reference. Your output must be exactly the same, except for the pid numbers and the signal names.

**Resources for the system calls needed for this assignment:**

[sigaction() man page](https://man7.org/linux/man-pages/man2/sigaction.2.html)

[sigqueue() man page](https://man7.org/linux/man-pages/man3/sigqueue.3.html)

[Signal Safety man page](https://man7.org/linux/man-pages/man7/signal-safety.7.html) 

[System Calls man page](https://man7.org/linux/man-pages/man2/syscalls.2.html)
