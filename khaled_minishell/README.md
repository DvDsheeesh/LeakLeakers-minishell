# Minishell

*This project has been created as part of the 42 curriculum by bahmad and kal-haj-.*

## Description
**minishell** is a 42 school project that aims to teach students different core concepts of building a UNIX shell. The architecture of our shell handles everything from parsing user input to executing complex system commands. The workflow is broadly divided into two main phases: **Parsing** and **Execution**.

The **Parsing** phase includes:
* **Tokenization:** Reading the input and dividing it into meaningful tokens based on bash grammar.
* **Syntax Checking:** Validating the input for unclosed quotes or invalid grammar before execution.
* **Expansion:** Replacing environment variable names (e.g., `$USER`, `$?`) with their corresponding values.

The **Execution** phase includes:
* **Process Management:** Using core system calls (`pipe`, `fork`, `waitpid`) to handle complex command pipelines.
* **I/O Redirections:** Managing file descriptors (`dup2`, `close`) to fully support standard redirections (`>`, `<`, `>>`) and heredocs (`<<`).
* **Command Execution:** Securely executing external binaries using `execve` while accurately resolving paths via the `PATH` environment variable.
* **Bash Replication:** Strictly replicating bash behavior, including precise exit statuses and specific error messages (e.g., differentiating between "Is a directory" and "No such file or directory").
* **Built-ins:** Custom implementations of core commands (`cd`, `echo`, `env`, `export`, `pwd`, `unset`, `exit`).
* **Signal Handling:** Precise management of signals like `SIGINT` (Ctrl+C) and `SIGQUIT` (Ctrl+\) to match standard interactive bash reactions.

## Instructions

### Compilation
Compile the project by using the `make` command at the root of the repository. This will generate the executable named `minishell`:
```bash
make
```
### Execution
Run the program by executing the generated binary. It will display its prompt, and you can execute commands just as you would in bash:
```bash
./minishell
```

## Resources & References

### Parsing
For the parsing phase, the following resources were highly beneficial:
* **[Bash Reference Manual](https://www.gnu.org/software/bash/manual/bash.html):** The primary source of truth.
* **[What is Tokenization](https://www.geeksforgeeks.org/nlp/what-is-tokenization/):** GeeksforGeeks article.
* **[The Bash Parser](https://mywiki.wooledge.org/BashParser):** Wooledge Wiki.
* **[Command-line Processing](https://www.linux.org/threads/bash-03-%E2%80%93-command-line-processing.38676/):** Linux.org thread.
* **42 Slack Channels:** Invaluable for seeing how other students handled different parsing edge cases.

### Execution
For the execution phase, the following resources were critical:
* **Linux Man Pages:** Core documentation for understanding system calls (`waitpid`, `pipe`, `dup2`, `execve`, `stat`, etc.).
* **[Write a Shell in C](https://brennan.io/2015/01/16/write-a-shell-in-c/):** An excellent tutorial by Stephen Brennan for understanding the fundamental loop and process execution.
* **42 Slack Channels:** Heavily relied upon for discovering rigorous test cases, edge cases, and testing scripts shared by peers.

### AI Usage

* **Parsing:** AI was strictly not used during the development of the parsing phase.
* **Execution:** AI was utilized exclusively as an interactive learning resource and testing assistant to:
  1. Understand the nuanced characteristics and exact behaviors of bash (e.g., specific exit statuses and file/directory handling rules).
  2. Explain the theoretical mechanisms of complex system calls and process synchronization in C.
  3. Generate complex test cases and command combinations to ensure all required edge cases and pipeline behaviors were properly handled and tested.
