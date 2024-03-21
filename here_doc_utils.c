#include "minishell.h"

int	create_temp_file(const char *filename)
{
	int	fd;

	fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("Error creating temporary file");
		exit(EXIT_FAILURE);
	}
	return (fd);
}

void	read_lines_until_delimiter(int fd, char *delimiter)
{
	char	*line;
	size_t	delimiter_len;

	delimiter_len = ft_strlen(delimiter);
	while (1)
	{
		write(1, "here_doc> ", 10);
		line = get_next_line(0);
		if (!line)
		{
			perror("Error reading from standard input");
			exit(EXIT_FAILURE);
		}
		if (ft_strncmp(delimiter, line, ft_strlen(line) - 1) == 0)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		free(line);
	}
}

int	open_temp_file_read(const char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening temporary file for heredoc");
		exit(EXIT_FAILURE);
	}
	return (fd);
}

void	write_temp_file_to_pipe(int fd_pipe, int fd_temp)
{
	char	buffer[4096];
	ssize_t	bytes_read;

	bytes_read = read(fd_temp, buffer, sizeof(buffer));
	while (bytes_read > 0)
	{
		write(fd_pipe, buffer, bytes_read);
		bytes_read = read(fd_temp, buffer, sizeof(buffer));
	}
}

void	free_argv(char **argv)
{
	int	i;

	i = 0;
	while (argv[i] != NULL)
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}
