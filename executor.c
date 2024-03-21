#include "minishell.h"

extern int	g_status;

int	execute_single_process(t_process *process, t_data *shell,
	int input_fd, int output_fd)
{
	if (process->command == NULL || process->command[0] == '\0')
	{
		if (process->next_process != NULL)
			free_commands(process);
		return (EXIT_SUCCESS);
	}
	if (g_status == 258)
		return (EXIT_FAILURE);
	if (execute_command(process, shell, input_fd, output_fd))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static void	more_commands(t_process *process, t_data *shell,
	int input_fd, int output_fd)
{
	if (execute_single_process(process, shell, input_fd, output_fd))
	{
		if (check_f_d(process) == 0)
			g_status = 1;
		else
			g_status = 0;
	}
	if (process)
		free_commands(process);
}

void	execute_multiple_commands(t_process *process, t_data *shell)
{
	int	input_fd;
	int	pipe_fd[2];

	input_fd = STDIN_FILENO;
	while (process)
	{
		if ((process->next_process && process->outfile == NULL))
		{
			create_pipe(pipe_fd);
			execute_single_process(process, shell, input_fd, pipe_fd[1]);
			close(pipe_fd[1]);
			input_fd = pipe_fd[0];
			free_commands(process);
			comprobate_status(process);
			process = process->next_process;
		}
		else
		{
			more_commands(process, shell, input_fd, STDOUT_FILENO);
			process = process->next_process;
		}
	}
	wait_for_children();
}

int	main_executor(t_data *shell, t_process *process)
{
	signal(SIGINT, cat_ctrlc);
	if (!process)
		return (EXIT_FAILURE);
	if (!is_builtin(process, shell))
	{
		if (!process->command || (process->command && process->here_doc))
		{
			if (!process->here_doc)
				return (EXIT_FAILURE);
			else
			{
				handle_heredoc(process, shell);
				return (EXIT_SUCCESS);
			}
		}
		if (process->command)
		{
			if (ft_strncmp(process->command, "clear", 5) == 0)
				printf("\033[H\033[J");
		}
		execute_multiple_commands(process, shell);
	}
	return (EXIT_SUCCESS);
}
