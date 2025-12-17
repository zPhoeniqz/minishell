# Information on the allowed functions

Generated with Mistral. Double check using the corresponding man pages if necessary.

---

### **GNU Readline Library**

| Function            | Header File         | Signature                                      | Summary                                                                 | Error Return Value                     |
|---------------------|---------------------|------------------------------------------------|-------------------------------------------------------------------------|----------------------------------------|
| readline            | readline/readline.h | `char *readline(const char *prompt);`          | Reads a line from stdin, with line editing and history support.        | `NULL` (on EOF or error)               |
| rl_clear_history    | readline/readline.h | `void rl_clear_history(void);`                 | Clears the history list.                                               | N/A                                    |
| rl_on_new_line      | readline/readline.h | `void rl_on_new_line(void);`                   | Informs readline that the cursor has moved to a new line.              | N/A                                    |
| rl_replace_line     | readline/readline.h | `void rl_replace_line(const char *text, int clear_undo);` | Replaces the current line with `text`.                                | N/A                                    |
| rl_redisplay        | readline/readline.h | `void rl_redisplay(void);`                     | Redraws the current input line.                                        | N/A                                    |
| add_history         | readline/history.h  | `void add_history(const char *string);`        | Adds a line to the history list.                                       | N/A                                    |

---

### **Standard C Library**

| Function            | Header File       | Signature                                      | Summary                                                                 | Error Return Value                     |
|---------------------|-------------------|------------------------------------------------|-------------------------------------------------------------------------|----------------------------------------|
| printf              | stdio.h           | `int printf(const char *format, ...);`        | Prints formatted output to stdout.                                      | Negative value (on error)              |
| malloc              | stdlib.h          | `void *malloc(size_t size);`                   | Allocates memory on the heap.                                           | `NULL` (on error)                      |
| free                | stdlib.h          | `void free(void *ptr);`                         | Frees previously allocated memory.                                     | N/A                                    |

---

### **POSIX System Calls**

| Function            | Header File       | Signature                                      | Summary                                                                 | Error Return Value                     |
|---------------------|-------------------|------------------------------------------------|-------------------------------------------------------------------------|----------------------------------------|
| write               | unistd.h          | `ssize_t write(int fd, const void *buf, size_t count);` | Writes data to a file descriptor.                                | `-1` (on error, sets `errno`)          |
| access              | unistd.h          | `int access(const char *pathname, int mode);`  | Checks file accessibility.                                             | `-1` (on error, sets `errno`)          |
| open                | fcntl.h           | `int open(const char *pathname, int flags, ...);` | Opens a file or device.                                                | `-1` (on error, sets `errno`)          |
| read                | unistd.h          | `ssize_t read(int fd, void *buf, size_t count);` | Reads data from a file descriptor.                                     | `-1` (on error, sets `errno`)          |
| close               | unistd.h          | `int close(int fd);`                            | Closes a file descriptor.                                              | `-1` (on error, sets `errno`)          |
| fork                | unistd.h          | `pid_t fork(void);`                            | Creates a new process by duplicating the calling process.             | `-1` (on error, sets `errno`)          |
| wait                | sys/wait.h        | `pid_t wait(int *wstatus);`                     | Waits for a child process to terminate.                                | `-1` (on error, sets `errno`)          |
| waitpid             | sys/wait.h        | `pid_t waitpid(pid_t pid, int *wstatus, int options);` | Waits for a specific child process.                            | `-1` (on error, sets `errno`)          |
| wait3               | sys/wait.h        | `pid_t wait3(int *wstatus, int options, struct rusage *rusage);` | Waits for a child process and returns resource usage.          | `-1` (on error, sets `errno`)          |
| wait4               | sys/wait.h        | `pid_t wait4(pid_t pid, int *wstatus, int options, struct rusage *rusage);` | Waits for a specific child process and returns resource usage. | `-1` (on error, sets `errno`)          |
| signal              | signal.h          | `void (*signal(int signum, void (*handler)(int)))(int);` | Sets a signal handler.                                         | `SIG_ERR` (on error)                    |
| sigaction           | signal.h          | `int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);` | Examines and changes signal action.            | `-1` (on error, sets `errno`)          |
| sigemptyset         | signal.h          | `int sigemptyset(sigset_t *set);`              | Initializes a signal set to empty.                                    | `-1` (on error, sets `errno`)          |
| sigaddset           | signal.h          | `int sigaddset(sigset_t *set, int signum);`     | Adds a signal to a signal set.                                         | `-1` (on error, sets `errno`)          |
| kill                | signal.h          | `int kill(pid_t pid, int sig);`                 | Sends a signal to a process or process group.                         | `-1` (on error, sets `errno`)          |
| exit                | stdlib.h          | `void exit(int status);`                        | Terminates the calling process.                                        | N/A                                    |
| getcwd              | unistd.h          | `char *getcwd(char *buf, size_t size);`         | Gets the current working directory.                                   | `NULL` (on error, sets `errno`)        |
| chdir               | unistd.h          | `int chdir(const char *path);`                  | Changes the current working directory.                                | `-1` (on error, sets `errno`)          |
| stat                | sys/stat.h        | `int stat(const char *pathname, struct stat *statbuf);` | Gets file status.                                              | `-1` (on error, sets `errno`)          |
| lstat               | sys/stat.h        | `int lstat(const char *pathname, struct stat *statbuf);` | Gets file status (does not follow symlinks).                   | `-1` (on error, sets `errno`)          |
| fstat               | sys/stat.h        | `int fstat(int fd, struct stat *statbuf);`      | Gets file status for an open file descriptor.                          | `-1` (on error, sets `errno`)          |
| unlink              | unistd.h          | `int unlink(const char *pathname);`             | Deletes a file.                                                        | `-1` (on error, sets `errno`)          |
| execve              | unistd.h          | `int execve(const char *pathname, char *const argv[], char *const envp[]);` | Executes a program.                                           | `-1` (on error, sets `errno`)          |
| dup                 | unistd.h          | `int dup(int oldfd);`                           | Duplicates a file descriptor.                                         | `-1` (on error, sets `errno`)          |
| dup2                | unistd.h          | `int dup2(int oldfd, int newfd);`               | Duplicates a file descriptor to a specified number.                   | `-1` (on error, sets `errno`)          |
| pipe                | unistd.h          | `int pipe(int pipefd[2]);`                     | Creates a pipe.                                                        | `-1` (on error, sets `errno`)          |
| opendir             | dirent.h          | `DIR *opendir(const char *name);`              | Opens a directory stream.                                             | `NULL` (on error, sets `errno`)        |
| readdir             | dirent.h          | `struct dirent *readdir(DIR *dirp);`            | Reads a directory entry.                                               | `NULL` (on error or end of directory) |
| closedir            | dirent.h          | `int closedir(DIR *dirp);`                      | Closes a directory stream.                                            | `-1` (on error, sets `errno`)          |

---

### **Terminal and Environment**

| Function            | Header File       | Signature                                      | Summary                                                                 | Error Return Value                     |
|---------------------|-------------------|------------------------------------------------|-------------------------------------------------------------------------|----------------------------------------|
| strerror            | string.h          | `char *strerror(int errnum);`                  | Returns a string describing an error number.                          | Never fails (may return "Unknown error") |
| perror              | stdio.h           | `void perror(const char *s);`                  | Prints a descriptive error message to stderr.                         | N/A                                    |
| isatty              | unistd.h          | `int isatty(int fd);`                           | Checks if a file descriptor is associated with a terminal.            | `0` (on error or if not a terminal)   |
| ttyname             | unistd.h          | `char *ttyname(int fd);`                        | Returns the name of a terminal.                                       | `NULL` (on error, sets `errno`)        |
| ttyslot             | unistd.h          | `int ttyslot(void);`                            | Returns the slot of the current user's terminal in the utmp file.      | `0` (on error)                         |
| ioctl               | sys/ioctl.h       | `int ioctl(int fd, unsigned long request, ...);` | Controls device parameters.                                          | `-1` (on error, sets `errno`)          |
| getenv              | stdlib.h          | `char *getenv(const char *name);`              | Gets an environment variable.                                         | `NULL` (if variable not found)         |

---

### **Terminal Control and Termcap**

| Function            | Header File       | Signature                                      | Summary                                                                 | Error Return Value                     |
|---------------------|-------------------|------------------------------------------------|-------------------------------------------------------------------------|----------------------------------------|
| tcsetattr           | termios.h         | `int tcsetattr(int fd, int optional_actions, const struct termios *termios_p);` | Sets terminal attributes.                     | `-1` (on error, sets `errno`)          |
| tcgetattr           | termios.h         | `int tcgetattr(int fd, struct termios *termios_p);` | Gets terminal attributes.                                      | `-1` (on error, sets `errno`)          |
| tgetent             | term.h            | `int tgetent(char *bp, const char *name);`      | Reads a termcap entry.                                                 | `-1` or `0` (on error)                 |
| tgetflag            | term.h            | `int tgetflag(char *id);`                       | Gets a boolean termcap capability.                                    | `-1` (on error)                        |
| tgetnum             | term.h            | `int tgetnum(char *id);`                        | Gets a numeric termcap capability.                                    | `-1` (on error)                        |
| tgetstr             | term.h            | `char *tgetstr(char *id, char **area);`         | Gets a string termcap capability.                                     | `NULL` (on error)                      |
| tgoto               | term.h            | `char *tgoto(const char *cap, int col, int row);` | Expands a termcap cursor addressing string.                           | `NULL` (on error)                      |
| tputs               | term.h            | `int tputs(const char *str, int affcnt, int (*putc)(int));` | Applies padding information to a termcap string.              | `-1` (on error)                        |

---
