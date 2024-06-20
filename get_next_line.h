/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 17:00:15 by ggaribot          #+#    #+#             */
/*   Updated: 2024/06/18 19:37:38 by ggaribot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <stdint.h>
# include <stdbool.h>
# include <unistd.h>
# include <stdarg.h>
# include <limits.h>
# include <stdio.h>
# include <fcntl.h>

# define FIRST_ASCII_CHAR	0
# define LAST_ASCII_CHAR	127
# define FIRST_PRINTABLE_CHAR	32
# define LAST_PRINTABLE_CHAR	126
# define DIFF_LOWER_UPPER		32
# define SPACE 32
# define FIRST_WHITESPACE 9
# define LAST_WHITESPACE 13

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

char	*get_next_line(int fd);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s);
char	*ft_substr(const char *s, unsigned int start, size_t len);
char	*ft_strchr(const char *s, int c);
int		ft_strlen(const char *s);

#endif