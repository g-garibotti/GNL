/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 18:33:11 by ggaribot          #+#    #+#             */
/*   Updated: 2024/06/20 15:41:52 by ggaribot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*initialize_stash(char *buffer)
{
	char	*stash;

	if (buffer)
	{
		stash = ft_strdup(buffer);
		if (stash == NULL)
		{
			free(buffer);
			return (NULL);
		}
		free(buffer);
		buffer = NULL;
	}
	else
	{
		stash = ft_strdup("");
		if (stash == NULL)
			return (NULL);
	}
	return (stash);
}

char	*read_and_fill(int fd, char *stash)
{
	char	*tmp;
	char	*new_stash;
	int		bytes_read;

	while (ft_strchr(stash, '\n') == NULL)
	{
		tmp = malloc(BUFFER_SIZE + 1);
		if (tmp == NULL)
			return (free(stash), NULL);
		bytes_read = read(fd, tmp, BUFFER_SIZE);
		if (bytes_read <= 0)
		{
			if (bytes_read == 0 && stash[0] != '\0')
				return (free(tmp), stash);
			return (free(stash), free(tmp), NULL);
		}
		tmp[bytes_read] = '\0';
		new_stash = ft_strjoin(stash, tmp);
		free(stash);
		free(tmp);
		if (new_stash == NULL)
			return (NULL);
		stash = new_stash;
	}
	return (stash);
}

char	*line_update_buffer(char **stash, char **buffer)
{
	char	*line;
	char	*newline_pos;

	newline_pos = ft_strchr(*stash, '\n');
	if (newline_pos != NULL)
	{
		line = ft_substr(*stash, 0, newline_pos - *stash + 1);
		if (line == NULL)
			return (free(*stash), NULL);
		*buffer = ft_strdup(newline_pos + 1);
		if (*buffer == NULL)
			return (free(*stash), free(line), NULL);
	}
	else
	{
		line = ft_strdup(*stash);
		*buffer = NULL;
		if (line == NULL)
			return (free(*stash), NULL);
	}
	free(*stash);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buffer = NULL;
	char		*line;
	char		*stash;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = initialize_stash(buffer);
	if (stash == NULL)
		return (NULL);
	stash = read_and_fill(fd, stash);
	if (stash == NULL)
		return (buffer = NULL, NULL);
	line = line_update_buffer(&stash, &buffer);
	if (line == NULL)
		return (NULL);
	return (line);
}
/*
int	main(void)
{
	int		fd;
	char	*line;

	fd = open("test.txt", O_RDONLY);
	line = get_next_line(fd);
	printf("%s", line);
	free(line);
	line = get_next_line(fd);
	printf("%s", line);
	free(line);
	close(fd);

	fd = open("test.txt", O_RDONLY);
	line = get_next_line(fd);
	printf("%s", line);
	free(line);
	line = get_next_line(fd);
	printf("%s", line);
	free(line);
	close(fd);
	return (0);
}*/
