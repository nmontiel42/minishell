/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmontiel <montielarce9@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 11:22:25 by nmontiel          #+#    #+#             */
/*   Updated: 2023/11/23 14:59:28 by nmontiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <fcntl.h>
//#include <stdio.h>

static char	*get_clean_line(char *acum_str)
{
	int		i;
	int		j;
	char	*ret_str;

	i = 0;
	while (acum_str[i] != '\0' && acum_str[i] != '\n')
		i++;
	if (acum_str[i] == '\0')
	{
		free(acum_str);
		return (NULL);
	}
	ret_str = ft_calloc_gnl((ft_strlen(acum_str) - i + 1), sizeof(char));
	i++;
	j = 0;
	while (acum_str[i] != '\0')
		ret_str[j++] = acum_str[i++];
	free(acum_str);
	if (ret_str[0] == '\0')
	{
		free(ret_str);
		return (NULL);
	}
	return (ret_str);
}

static char	*get_actual_line(char *acum_str)
{
	char	*ret_str;
	int		i;

	i = 0;
	if (acum_str[i] == '\0')
		return (NULL);
	while (acum_str[i] != '\0' && acum_str[i] != '\n')
		i++;
	ret_str = ft_calloc_gnl((i + 2), sizeof(char));
	i = 0;
	while (acum_str[i] != '\0' && acum_str[i] != '\n')
	{
		ret_str[i] = acum_str[i];
		i++;
	}
	if (acum_str[i] != '\0' && acum_str[i] == '\n')
		ret_str[i++] = '\n';
	return (ret_str);
}

static char	*get_joint(char *acum_str, char *buff)
{
	char	*r;

	r = ft_strjoin_gn(acum_str, buff);
	free(acum_str);
	return (r);
}

static char	*get_a_lot(int fd, char *acum_str)
{
	char	*tmp;
	int		read_char;

	if (!acum_str)
		acum_str = ft_calloc(1, sizeof(char));
	tmp = ft_calloc_gnl((BUFFER_SIZE + 1), sizeof(char));
	read_char = 1;
	while (read_char > 0)
	{
		read_char = read(fd, tmp, BUFFER_SIZE);
		if (read_char < 0)
		{
			free(tmp);
			return (NULL);
		}
		tmp[read_char] = '\0';
		acum_str = get_joint(acum_str, tmp);
		if (ft_strchr_mod(tmp, '\n'))
			break ;
	}
	free(tmp);
	return (acum_str);
}

char	*get_next_line(int fd)
{
	static char	*acum_str;
	char		*actual_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (read(fd, 0, 0) < 0)
	{
		if (acum_str != NULL)
		{
			free(acum_str);
			acum_str = NULL;
		}
		return (NULL);
	}
	acum_str = get_a_lot(fd, acum_str);
	actual_line = get_actual_line(acum_str);
	acum_str = get_clean_line(acum_str);
	return (actual_line);
}

/*
int	main(void)
{
	int		fd;
	int		i;
	char	*line;

	fd = open("loverofmine.txt", O_RDONLY);
	for (i = 0; i < 100; i++)
	{
		line = get_next_line(fd);
		printf("%s", line);
	}
	return (0);
}
*/