#include "minishell.h"

void	child_process2(t_process *process, int fd_pipe[2],
	char *full_path, char **argv)
{
	redirect_outfile(process);
	close(fd_pipe[1]);
	dup2(fd_pipe[0], STDIN_FILENO);
	close(fd_pipe[0]);
	execve(full_path, argv, process->env);
	perror("Error en execvp");
	exit(EXIT_FAILURE);
}

void	father_process2(int fd_pipe[2], int fd_read, pid_t pid)
{
	close(fd_pipe[0]);
	write_temp_file_to_pipe(fd_pipe[1], fd_read);
	close(fd_pipe[1]);
	close(fd_read);
	waitpid(pid, NULL, 0);
}

char	**create_argv2(char **argv, t_process *process)
{
	t_list	*current;
	int		j;

	argv = malloc((ft_lstsize(process->argv) + 2) * sizeof(char *));
	j = 1;
	argv[0] = ft_strdup(process->command);
	current = process->argv;
	j = 1;
	while (current)
	{
		argv[j] = ft_strdup(current->content);
		current = current->next;
		j++;
	}
	argv[j] = NULL;
	return (argv);
}

void	free_things(t_process *process, char **argv)
{
	free_argv(argv);
	free_commands(process);
}
