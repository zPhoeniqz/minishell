*This project has been created as part of the 42 curriculum by  pbindl, whuth.*

# minishell

## Description

minishell is a lightweight Unix shell implementation written in C. The goal is to understand how a shell works at a fundamental level. From reading user input to parsing commands, expanding variables, handling redirections, and executing processes.

The shell supports:
- Command execution via `PATH` resolution and absolute/relative paths
- Pipelines (`|`) connecting multiple commands
- Input and output redirections (`<`, `>`, `>>`, `<<`)
- Environment variable expansion (`$VAR`, `$?`)
- Single and double quote handling
- The following builtins: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`
- Signal handling (`Ctrl+C`, `Ctrl+D`, `Ctrl+\`)

## Instructions

### Requirements

- GCC or Clang
- GNU Make
- readline library (`libreadline-dev` on Debian/Ubuntu)

### Compilation

```bash
make
```

This produces the `minishell` binary in the project root.

### Running

```bash
./minishell
```

The shell will display a prompt with the current working directory. Type commands as you would in any Unix shell. Exit with `exit` or `Ctrl+D`.

## Resources

### Shell & Unix References

- [Bash Reference Manual](https://www.gnu.org/software/bash/manual/bash.html) — authoritative reference for shell behaviour and edge cases
- [The Linux Programming Interface](https://man7.org/tlpi/) — Michael Kerrisk; comprehensive reference for Linux system calls

### AI Usage

AI was used for testing the project.

All code was written, understood, and validated by the authors. AI was not used to generate submitted code directly.
