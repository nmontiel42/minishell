#include "minishell.h"

static void	multiple_errors(t_process *process)
{
	if (ft_strncmp(process->command, "./", 2) == 0)
	{
		put_error(NOTFILEORDIR, 127);
		return ;
	}
	else
	{
		put_error(NOTCOMMAND, 127);
		return ;
	}
}

static void	do_child_process(t_process *process, int input_fd,
	int output_fd, char *full_path)
{
	process->pid = fork();
	if (process->pid == 0)
	{
		help_child(process, input_fd, output_fd);
		child_process(process, full_path);
	}
	father_process(process, input_fd, output_fd);
	free(full_path);
}

static void	check_stat(t_process *process, struct stat path_stat)
{
	if (!S_ISDIR(path_stat.st_mode)
		&& access(process->command, W_OK) == -1
		&& access(process->command, X_OK) == -1
		&& access(process->command, R_OK) == -1)
	{
		put_error(NOTPERMISSION, 126);
		return ;
	}
}

void	no_path(t_process *process, int input_fd, int output_fd)
{
	char		*full_path;
	struct stat	path_stat;

	full_path = NULL;
	if (access(process->command, F_OK) == 0)
	{
		stat(process->command, &path_stat);
		if (S_ISDIR(path_stat.st_mode)
			&& (ft_strncmp(process->command, "./", 2) == 0
				|| ft_strncmp(process->command, "/", 1) == 0))
		{
			put_error(ISDIR, 126);
			return ;
		}
		check_stat(process, path_stat);
	}
	if (access(process->command, F_OK | X_OK) == 0
		&& !S_ISDIR(path_stat.st_mode))
		full_path = ft_strdup(process->command);
	else
		multiple_errors(process);
	do_child_process(process, input_fd, output_fd, full_path);
}
