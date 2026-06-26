*This project has been created as part of the 42 curriculum by melshata, halbit.*

# Minishell - LeakLeakers

## Description

Minishell is a custom Unix shell built in C, modeled after Bash. It handles command execution, pipelines, redirections, environment variables, and signal management — all from scratch.

The project covers two main areas:
- **Parsing**: tokenizing user input, handling quotes, expanding variables (`$VAR`, `$?`), and building an internal command representation.
- **Execution**: running executables via `execve`, implementing all required builtins, managing pipes between commands, handling heredocs, and redirecting I/O.

### Features

| Feature | Details |
|---|---|
| Prompt & History | Interactive prompt with readline history |
| Command Search | Resolves executables via `PATH` or absolute/relative paths |
| Quotes | Single quotes prevent all expansion; double quotes allow `$` expansion |
| Redirections | `<`, `>`, `>>`, `<<` (heredoc) |
| Pipes | `\|` chains commands, connecting stdout to stdin |
| Environment Variables | `$VAR` and `$?` expansion |
| Signals | `ctrl-C` (new prompt), `ctrl-D` (exit), `ctrl-\` (ignored) |
| Builtins | `echo -n`, `cd`, `pwd`, `export`, `unset`, `env`, `exit` |

## Instructions

### Requirements

- CC compiler
- GNU Make
- readline library (`libreadline-dev` on Debian/Ubuntu)

### Build

```bash
make
```

This compiles libft first, then links everything into the `minishell` binary.

```bash
make clean    # remove object files
make fclean   # remove objects + binary
make re       # full rebuild
```

### Run

```bash
./minishell
```

## Resources

### References

- [Bash Reference Manual](https://www.gnu.org/software/bash/manual/bash.html) — authoritative guide on shell behavior used as the standard for this project
- [GNU readline documentation](https://tiswww.case.edu/php/chet/readline/rltop.html) — API reference for the readline library
- `man 2 fork`, `man 2 execve`, `man 2 pipe`, `man 2 dup2` — core POSIX system calls
- `man 7 signal` — signal handling reference
- [Write a Shell in C — Stephen Brennan](https://brennan.io/2015/01/16/write-a-shell-in-c/) — practical walkthrough of shell fundamentals

### AI Usage

Claude Code (claude-sonnet-4-6) was used during this project for the following tasks:

- **Debugging**: analyzing segfaults and memory errors when execution or parsing produced unexpected behavior
- **Explaining system calls**: clarifying the exact semantics of `dup2`, `waitpid`, `sigaction`, and heredoc fd management
- **Code review**: checking edge cases in variable expansion (`$?`, unset variables, variables inside double quotes)
