#include <stdio.h>
#include <sys/types.h> 
#include <sys/stat.h>
#include <unistd.h> 
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <time.h>

char signame[32][10];  /* array to hold signal names */
/* function to initialize the array of signal names */
void initialize_signals();

/* Wrapper functions for system calls */
void unix_error(const char *msg);
pid_t Fork();
pid_t Wait(int *status);
pid_t Waitpid(pid_t pid, int *status, int options);
int Sigqueue(pid_t pid, int signum, union sigval value);
int Sigemptyset(sigset_t *set);
int Sigfillset(sigset_t *set);
int Sigaction(int signum, const struct sigaction *new_act, struct sigaction *old_act);
int Sigprocmask(int how, const sigset_t *set, sigset_t *oldset);
ssize_t Write(int d, const void *buffer, size_t nbytes);
typedef void handler_t(int, siginfo_t *, void *);  /* SA_SIGINFO-style handler */
handler_t *Signal(int signum, handler_t *handler);

/* Signal Handler */
void signal_handler(int sig, siginfo_t *value, void *ucontext){
    return;
}

// main function
int main() {
  return 0;
}
void initialize_signals(){
  strcpy(signame[0],  "UNUSED");     // Unused
  strcpy(signame[1],  "SIGHUP");     // Hangup (POSIX)
  strcpy(signame[2],  "SIGINT");     // Interrupt (ANSI)
  strcpy(signame[3],  "SIGQUIT");    // Quit (POSIX)
  strcpy(signame[4],  "SIGILL");     // Illegal instruction (ANSI)
  strcpy(signame[5],  "SIGTRAP");    // Trace trap (POSIX)
  strcpy(signame[6],  "SIGIOT");     // IO trap (4.2 BSD); SIGABRT - Abort (ANSI)
  strcpy(signame[7],  "SIGBUS");     // BUS error
  strcpy(signame[8],  "SIGFPE");     // Floating-point exception (ANSI)
  strcpy(signame[9],  "SIGKILL");    // Kill, unblockable (POSIX)
  strcpy(signame[10], "SIGUSR1");    // User-defined signal 1 (POSIX)
  strcpy(signame[11], "SIGSEGV");    // Segmentation violation (ANSI)
  strcpy(signame[12], "SIGUSR2");    // User-defined signal 2 (POSIX)
  strcpy(signame[13], "SIGPIPE");    // Broken pipe (POSIX)
  strcpy(signame[14], "SIGALRM");    // Alarm clock (POSIX)
  strcpy(signame[15], "SIGTERM");    // Termination (ANSI)
  strcpy(signame[16], "SIGSTKFLT");  // Stack fault
  strcpy(signame[17], "SIGCHLD");    // Child status changed (POSIX); SIGCLD (System V)
  strcpy(signame[18], "SIGCONT");    // Continue (POSIX)
  strcpy(signame[19], "SIGSTOP");    // Stop, unblockable (POSIX)
  strcpy(signame[20], "SIGTSTP");    // Keyboard stop (POSIX)
  strcpy(signame[21], "SIGTTIN");    // Background read from tty (POSIX)
  strcpy(signame[22], "SIGTTOU");    // Background write to tty (POSIX)
  strcpy(signame[23], "SIGURG");     // Urgent condition on socket (4.2 BSD)
  strcpy(signame[24], "SIGXCPU");     // CPU limit exceeded (4.2 BSD)
  strcpy(signame[25], "SIGXFSZ");    // File size limit exceeded (4.2 BSD)
  strcpy(signame[26], "SIGVTALRM");  // Virtual alarm clock (4.2 BSD)
  strcpy(signame[27], "SIGPROF");    // Profiling alarm clock (4.2 BSD)
  strcpy(signame[28], "SIGWINCH");   // Window size change (4.3 BSD, Sun)
  strcpy(signame[29], "SIGIO");      // I/O possible (4.2 BSD); Pollable event (System V)
  strcpy(signame[30], "SIGPWR");     // Power failure restart (System V)
  strcpy(signame[31], "SIGSYS");     // Bad system call
}
