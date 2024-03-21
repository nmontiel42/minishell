#include "minishell.h"

void	handle_previous_directory(t_data *shell)
{
	char	dir[500];

	obtain_env(shell, "OLDPWD");
	if (getcwd(dir, sizeof(dir)) == NULL)
	{
		perror("getcwd");
		return ;
	}
	if (chdir(shell->cd) != -1)
	{
		update_oldpwd_again(shell, dir);
		update_pwd(shell);
	}
	else
		perror("cd");
}

void	handle_given_directory(char **str, t_data *shell)
{
	if (handle_directory(shell, str) != -1)
	{
		free(shell->cd);
		shell->cd = NULL;
		free(shell->cd1);
		shell->cd1 = NULL;
	}
}

void	cd_command(t_process *process, t_data *shell)
{
	if (!ft_strncmp(process->command, "cd\0", 3))
	{
		if (!process->argv)
		{
			obtain_env(shell, "HOME");
			handle_given_directory(&shell->cd, shell);
		}
		else if (!ft_strncmp(process->args[0], "-\0", 2))
			handle_previous_directory(shell);
		else
			handle_given_directory(process->args, shell);
	}
}

int	handle_directory(t_data *shell, char **str)
{
	char	dir[500];
	int		flag;

	getcwd(dir, sizeof(dir));
	flag = chdir(str[0]);
	if (flag == 0)
	{
		update_oldpwd_again(shell, dir);
		update_pwd(shell);
		return (0);
	}
	else
	{
		put_error(NOTFILEORDIR, 1);
		return (-1);
	}
}
