/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloko <lloko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 17:41:16 by lloko             #+#    #+#             */
/*   Updated: 2021/11/24 21:06:04 by lloko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	stop_if_end(char *text)
{
	int	i;

	i = 0;
	if (!text)
		return (0);
	while (text[i])
	{
		if (text[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*writeline_without_n(char *text)
{
	char	*line;
	int		i;

	i = 0;
	if (!text)
		return (NULL);
	while (text[i] && text[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	ft_strlcpy(line, text, i + 2);
	if (line[0] == '\0')
	{
		free (line);
		return (NULL);
	}
	return (line);
}

char	*writeline_after_n(char *text)
{
	char	*remainder;
	int		i;

	i = 0;
	if (!text)
		return (NULL);
	while (text[i] && text[i] != '\n')
		i++;
	if (text[i] == '\0')
	{
		free (text);
		return (NULL);
	}
	remainder = (char *)malloc(sizeof(char) * (ft_strlen(text) - i + 1));
	if (!remainder)
	{
		free (text);
		return (NULL);
	}
	ft_strlcpy(remainder, text + i + 1, ft_strlen(text) - i + 1);
	free (text);
	return (remainder);
}

char	*copyinbuf(int fd, char *text, char *buf)
{
	int		copy;
	char	*temp;

	copy = 1;
	while (copy != 0 && !stop_if_end(text))
	{
		copy = read(fd, buf, BUFFER_SIZE);
		if (copy < 0)
			return (NULL);
		buf[copy] = '\0';
		if (!text)
			text = ft_strdup("");
		if (!text)
			return (NULL);
		temp = text;
		text = ft_strjoin(temp, buf);
		if (!text)
			return (NULL);
		free (temp);
	}
	return (text);
}

char	*get_next_line(int fd)
{
	char			*new_line;
	char			*buf;
	static char		*text;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
	{
		free (buf);
		return (NULL);
	}
	text = copyinbuf(fd, text, buf);
	free (buf);
	if (!text)
		return (NULL);
	new_line = writeline_without_n(text);
	text = writeline_after_n(text);
	return (new_line);
}

/* #include <stdio.h>
int main()
{
	int fd;
	char *line;
	
	fd = open("byron.txt", O_RDONLY);
	line = get_next_line(fd);
	printf("%s\n", line);
}*/