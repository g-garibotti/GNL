/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 15:29:45 by ggaribot          #+#    #+#             */
/*   Updated: 2024/06/20 15:35:17 by ggaribot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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

char	*extract_line_and_update_buffer(char **stash, char **buffer)
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
	static char	*buffer[MAX_FD] = {NULL};
	char		*line;
	char		*stash;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = initialize_stash(buffer[fd]);
	if (stash == NULL)
		return (NULL);
	stash = read_and_fill(fd, stash);
	if (stash == NULL)
		return (buffer[fd] = NULL, NULL);
	line = extract_line_and_update_buffer(&stash, &buffer[fd]);
	if (line == NULL)
		return (NULL);
	return (line);
}
