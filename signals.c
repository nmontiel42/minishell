#include "minishell.h"

extern int	g_status;

void	signals_handler(int sign)
{
	if (sign == SIGINT)
	{
		g_status = 130;
		rl_on_new_line();
		rl_redisplay();
		write(1, "   \n", 4);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	cat_ctrlc(int sig)
{
	if (sig == SIGINT)
	{
		printf("\033[K\n");
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

void	setup_signal_handlers(void)
{
	signal(SIGINT, signals_handler);
	signal(SIGQUIT, SIG_IGN);
}
