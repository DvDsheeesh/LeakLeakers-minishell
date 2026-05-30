#include <stdio.h>     // For printf
#include <unistd.h>    // For fork, execve
#include <sys/wait.h>  // For wait
#include <stdlib.h>
// #include <sys/types.h> // For pid_t

// int main()
// {
// 	char *args[] = {"/bin/ls", "-l", "../../M0", NULL};
// 	char *env[] = {NULL};
// 	int	a = 9;

	// printf("\ncccccccccc %d cccccccccc\n", getpid());

	// pid_t pid = fork();
	// pid = fork();

	// if (pid == 0)
	// {
	// 	printf("\naaaaaaaaaa %d aaaaaaaaaa %d\n", getpid(), pid);
	// }
	// else
	// {
	// 	printf("\nbbbbbbbbbb %d bbbbbbbbbb %d\n", getpid(), pid);
	// 	// usleep(500);
	// 	// printf("\nbbbbbbbbbb %d 2222222222 %d\n", getpid(), pid);
	// 	// execve(args[0], args, env);
	// }
	// printf("\narrived:  %d  %d\n", getpid(), pid);
	// wait(NULL);
	// // printf("\ndddddddddd %d dddddddddd %d\n", wait(0));
	// printf("\ncccccccccc %d cccccccccc %d\n", getpid(), pid);
// }

// int main()
// {
// 	char *args[] = {"/bin/ls", "-l", "../../M0", NULL};
// 	char *env[] = {NULL};
// 	int	a = 9;
	// pid_t pid = fork();
	// if (pid == 0) {
	// 	// Inside Child Process
	// 	printf("aaaaaaaaaa %d aaaaaaaaaa", execve(args[0], args, env));
	// } else {
	// 	// Inside Parent Process
	// 	wait(NULL); // Wait for child to finish
	// 	printf("Child process complete.\n");
	// }
// }

// int main()
// {
// 	char *args[] = {"/bin/ls", "-l", "../../M0", NULL};
// 	char *env[] = {NULL};
// 	int	a = 9;

// 	char *var = malloc(20);
// 	// var[-1] = '\0';
// 	int len = read(0, var, 19);
// 	var[len - 1] = '\0';
// 	// printf("your BEUTIFUL input is : %sstfu %d", var ,len);
// 	// char path[] = {};
// 	char *command[] = {var, NULL};
// 	printf("test: %s,,, ", var);
// 	execve(command[0], command, env);
// }

// int main()
// {
// 	int	a = 9;

// 	printf("test: %lu\n", sizeof(a));
// }







int main()
{
	char *args[] = {"/bin/ls", "-l", "../../M0", NULL};
	char *env[] = {NULL};
	int	a = 9, fd[2], rr;
	pipe(fd);

	char *var = malloc(20);
	char *var2 = malloc(20);
	// var[-1] = '\0';
	int len = read(0, var, 19);
	var[len - 1] = '\0';
	char *path[] = {"/usr/bin/which", var, NULL};

	pid_t pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		execve(path[0], path, env);
	}
	else
	{
		close(fd[1]);
		rr = read(fd[0], var2, 20);
		var2[rr - 1] = '\0';
		printf("%d,,,%s\n", rr, var2);
	}
	char *command[] = {var2, "../", NULL};
	execve(command[0], command, env);
}

