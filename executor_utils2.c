#include "minishell.h"

extern int	g_status;

void	wait_for_children(void)
{
	while (wait(NULL) > 0)
		;
}

int	create_pipe(int pipe_fd[2])
{
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	return (pipe_fd[0]);
}

void	comprobate_status(t_process *process)
{
	if (check_f_d(process) == 0)
		g_status = 1;
	else
		g_status = 0;
}

void	do_child(t_process *process, int input_fd,
	int output_fd, char *full_path)
{
	help_child(process, input_fd, output_fd);
	child_process(process, full_path);
}

void	do_fork(t_process *process, int input_fd,
	int output_fd, char *full_path)
{
	process->pid = fork();
	if (process->pid == 0)
		do_child(process, input_fd, output_fd, full_path);
	father_process(process, input_fd, output_fd);
}
