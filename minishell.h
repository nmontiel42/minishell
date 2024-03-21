#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>
# include <unistd.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <sys/ioctl.h>

# define RESET		"\x1B[0m"
# define RED		"\x1B[31m"
# define GREEN		"\x1B[32m"
# define YELLOW		"\x1B[33m"
# define BLUE		"\x1B[34m"
# define MAGENTA	"\x1B[35m"
# define CYAN		"\x1B[36m"
# define WHITE		"\x1B[37m"

# define Q			'\''
# define DQ			'\"'

typedef struct s_env
{
	char			*name;
	char			*value;
	int				index;
	struct s_env	*next;
}				t_env;

typedef struct s_data
{
	char	**envp;
	char	*cd;
	char	*cd1;
	char	**echo;
	char	*line;	
	char	cwd[500];
	int		f_pipe;
	t_env	*env;
	int		i;
	size_t	env_count;
	t_env	*export;
	t_env	*temp_export;
}				t_data;

typedef struct s_process
{
	struct s_process	*next_process;
	char				*command;
	t_list				*argv;
	char				**args;
	pid_t				pid;
	char				*infile;
	int					in_fd;
	char				*outfile;
	int					outf;
	int					appendf;
	char				*outfile_append;
	t_list				*here_doc;
	int					heredoc_active;
	int					stderr;
	int					completed;
	int					stopped;
	int					status;
	char				**env;
	char				*path_env;
	char				*here_doc_line;
	t_list				*output_files;
	char				*temp;
}				t_process;

enum	e_error
{
	DEQUOTE = 1, //g_exit_status = 1?
	NOTFILEORDIR = 2, //g_exit_status = 1
	NOTPERMISSION = 3, //g_exit_status = 1
	NOTCOMMAND = 4, //g_exit_status = 127
	DUPERROR = 5, //g_exit_status = 1 Por si falla dup2??
	FORKERROR = 6, //g_exit_status = 1 Por si falla fork
	PIPEERROR = 7, //g_exit_status = 1 Por si falla pipe
	UNEXPECTEDTOKEN = 8, //g_exit_status = 258
	MEMPROBLEM = 9, //g_exit_status = ? Por si falla malloc
	ISDIR = 10, //g_exit_status = 126
	NOTDIR = 11, //g_exit_status = 1
	OPENERROR = 12, //g_exit_status = 1? Por si falla open (fd < 0)
	ARGS = 13, //g_exit_status = 1
	CLOSEERROR = 14, //g_exit_status = 1
	SINTAXERROR = 15, //g_exit_status = 2
	TOMANYARG = 16, //para la salida, g_status = 1
	NOTVALID = 17, //g_exit_status = 1
	NUMARG = 18, //para la salida, g_Status == 255
	REDIRECTOUT = 19 //redireccion outfile, g_status = 1
};

//builtins.c
void	env_command(t_data *shell);
void	pwd_command(t_data *shell, t_process *process);
void	echo_command(t_process *process, int exists);
void	unset_command(t_data *shell, char *name);
void	export_command(t_process *process, t_data *shell);

//cd_utils.c
void	update_pwd(t_data *shell);
void	update_oldpwd(t_data *shell);
void	update_oldpwd_again(t_data *shell, char *pwd);
void	obtain_env(t_data *shell, char *env_var);

//cd.c
void	handle_previous_directory(t_data *shell);
void	handle_given_directory(char **str, t_data *shell);
void	cd_command(t_process *process, t_data *shell);
int		handle_directory(t_data *shell, char **str);

//enviroment.c
t_env	*copy_env_to_list(char **envp, t_data *shell);
t_env	*create_env_node(char *name, char *value, int index);
void	add_env_node(t_env **head, t_env **current, t_env *new_node);
void	copy_env_to_data(t_data *data, char **envp);

//error.c
void	put_error(int error_type, int error_code);
void	put_error2(int error_type, int error_code);

//executor_utils.c
void	free_string_array(char **array);
int		find_path(t_process *process, t_data *shell);
void	execute_builtin(t_process *process, t_data *shell);
bool	is_builtin(t_process *process, t_data *shell);

//executor_utils2.c
void	wait_for_children(void);
int		create_pipe(int pipe_fd[2]);
void	comprobate_status(t_process *process);
void	do_child(t_process *process, int input_fd,
			int output_fd, char *full_path);
void	do_fork(t_process *process, int input_fd,
			int output_fd, char *full_path);

//executor.c
int		execute_single_process(t_process *process, t_data *shell,
			int input_fd, int output_fd);
void	execute_multiple_commands(t_process *process, t_data *shell);
int		main_executor(t_data *shell, t_process *process);

//executor2.c
void	help_child(t_process *process, int input_fd, int output_fd);
void	father_process(t_process *process, int input_fd, int output_fd);
void	child_process(t_process *process, char *full_path);
int		execute_command(t_process *process, t_data *shell,
			int input_fd, int output_fd);

//expander_utils.c
int		get_len_word(char *str, int i);
char	*set_key(char *str, int i);
t_env	**init_tmp_env(t_env **tmp);

//expander_utils2.c
int		check_memory(t_env **tmp_env, t_list **tmp_list);
void	expander(t_env *env, t_list **line_splited);
char	*join_expand2(char *str, int i, char *end_str);
char	*join_expand3(char *str, int i, char *end_str);

//expander.c
char	*get_expanded_value(t_env *env, char *key);
char	*get_status(char *str);
char	*join_expand_value(char *value, char *end_str, char *tmp);
char	*expand_value(char *str, int i, t_env *env, char *end_str);
char	*join_expand(char *str, int start, char *end_str, int i);

//expander2.c
int		search_end_str(char *str, int i);
int		search_end_str2(char *str, int i);
char	*expand_quoted(char *str, t_env *env);
char	*join_expand_quoted(char *end_str, char *tmp);
char	*expand(char *str, t_env *env);

//expander3.c
char	*expand_single_quote(char *str, int *i, char *end_str);
char	*expand_double_quote(char *str, int *i, t_env *env, char *end_str);
char	*expand_dollar(char *str, int *i, t_env *env, char *end_str);
char	*expand_else(char *str, int *i, char *end_str);

//export_utils.c
void	only_export(t_data *shell);
void	create_variable(char *variable, t_data *shell);
bool	check_args(char *arg, char *cmd);
int		check_if_exists(char *name, char *value, t_data *shell);
t_env	*new_node(char *name, char *value);

//free.c
void	free_temp(char **temp);
void	free_echo(char **str);
void	free_list_p(t_list **tmp);
void	free_list(t_list **list);
void	free_env_list(t_env *env);

//free2.c
void	free_expander(t_env **tmp_env, t_list **tmp_list);
void	ft_free_char(char *str);
void	free_process(t_process *process);
void	free_list_dp(t_list **list);
void	free_list_process(t_list *list);

//here_doc_utils.c
int		create_temp_file(const char *filename);
void	read_lines_until_delimiter(int fd, char *delimiter);
int		open_temp_file_read(const char *filename);
void	write_temp_file_to_pipe(int fd_pipe, int fd_temp);
void	free_argv(char **argv);

//here_doc_utils2.c
void	child_process2(t_process *process, int fd_pipe[2],
			char *full_path, char **argv);
void	father_process2(int fd_pipe[2], int fd_read, pid_t pid);
char	**create_argv2(char **argv, t_process *process);
void	free_things(t_process *process, char **argv);

//here_doc.c
int		handle_heredoc(t_process *process, t_data *shell);

//lexer_pipes_utils.c
int		get_pipe_nbr(char *line, int i);
int		get_pipe_index(char *line, int i);

//lexer_pipes.c
int		split_pipe_2(int i, char *tmp_word, t_list **pipes_splited);
int		split_pipe_3(char *tmp_word, int i, t_list **pipes_splited);
void	split_pipe(t_list *list, int i, t_list **pipes_splited);
void	handle_pipes(t_list **list, int i, t_list **pipes_splited);
void	split_pipes(t_list **list, t_list **pipes_splited);

//lexer_redir_utils.c
int		get_redir_index(char *line, int i);
int		insert_redirs(char redir, t_list **list, char *tmp_word, int i);
void	set_redir(t_list **list, char redir, char *tmp_word, int i);
int		get_redirection_nbr(char *line, int i);
void	insert_redirs2(char redir, t_list **list);

//lexer_redir.c
int		split_redirs_3(char *tmp_word, int i, t_list **redir_splited);
int		split_redirs_2(int i, char *tmp_word, t_list **redir_splited);
void	split_redirection(t_list *list, int i, t_list **redir_splited);
void	handle_redirections(t_list **list, int i, t_list **redir_splited);
void	split_redirections(t_list **list, t_list **redir_splited);

//lexer_utils.c
void	insert_node(t_list **list, char *content);
int		get_end_index(char *line, int i);
char	*get_tmp_split(int target_index, char *tmp_word, int i);
int		search_end_quoted_string(char q, char *line, int i);
void	add_node(t_list **list, char *tmp_word, char *tmp_split);

//lexer.c
void	init_list(t_list **list);
void	create_line_splited(char *line, t_list **list);
void	ft_free_list(t_list **list);
void	lexer(t_data *shell, t_list **redir_splited);

//main_utils.c
void	executor(t_process *process, t_data *shell, t_list **redir_splited);
void	check_quotes_and_executor(t_process *process, t_data *shell,
			t_list **redir_splited);
void	ctrl_d(t_data *shell);
void	is_space(t_data *shell);
void	extra_cases(t_data *shell);

//main.c
void	ft_header(void);
void	initialize_minishell(t_data **shell, char **env);
void	start_minishell(t_data *shell);
int		main(int argc, char **argv, char **env);

//parser_utils.c
void	init_process(t_process *process);
int		ft_lstsize(t_list *lst);
int		check_mem(char **str);
char	**list_to_array(t_list *list);
int		check_redir(char *tmp_word);

//parser_utils2.c
void	check_pipe(char *tmp_word);
void	check_infile(char *tmp_word, t_process *tmp_process);
int		check_access_outfile(char *tmp_word);
void	check_outfile(char *tmp_word, t_process *tmp_process);
void	check_outfile_append(char *tmp_word, t_process *tmp_process);

//parser_utils3.c
void	add_heredoc(t_list **here_doc, char *word);
void	parse_final(t_process **process, t_list **tmp);
void	handle_command_pipe_redir(t_process **tmp_process, t_list **tmp);
void	check_redirs(char *tmp_word, char *tmp_word_next,
			t_process *tmp_process);
int		check_parser_pipe(t_list **tmp, t_process **tmp_process);

//parser.c
void	handle_redirection(t_list **tmp, t_process *tmp_process);
void	handle_pipe(t_process **tmp_process, t_list *tmp);
void	handle_command(t_process **tmp_process, t_list *tmp);
int		is_redir(char *tmp_word);
void	parse(t_process *process, t_list **words_splited);

//quote_cleaner_utils.c
char	*add_quot_substr(int start, int i, char *str, char *end_str);
char	*add_substr(int start, int i, char *str, char *end_str);

//quote_cleaner.c
char	*handle_quoted_string(char *str, int *i, char *end_str);
char	*handle_unquoted_string(char *str, int *i, char *end_str);
void	update_list_content(t_list **list, char *end_str);
void	clean_str_quot(char *str, t_list **list);
void	quot_cleaner(t_list **list);

//quotes.c
char	set_in_quot(char *line, int i);
int		check_quotes(char *line, int q, int i);
int		check_closed_quotes(char *line, int q, int i, char in_quot);

//redirections.c
void	redirect_infile(t_process *process);
void	redirect_outfile(t_process *process);

//signals.c
void	signals_handler(int sign);
void	cat_ctrlc(int sig);
void	rl_replace_line(const char *text, int clear_undo);
void	setup_signal_handlers(void);

//utils.c
void	env_add_back(t_env **root, t_env *new);
void	print_split(char **line_splited);
int		ft_strcmp(char *s1, char *s2);
int		ft_strends(const char *str, const char *end);
void	free_commands(t_process *process);

//utils2.c
int		check_f_d(t_process *process);
char	*ft_strndup(const char *str, size_t n);
char	*obtain_env_name(char *fullenv);
char	*obtain_env_value(char *fullenv);
void	free_unset(t_env *del);

//utils3.c
void	free_elements(char *temp, char *full_path);
t_list	*list_next(t_list **tmp_list);
void	exit_command(t_process *process, t_data *shell);

//utils4.c
void	no_path(t_process *process, int input_fd, int output_fd);

#endif