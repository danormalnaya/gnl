/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloko <lloko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 00:13:10 by lloko             #+#    #+#             */
/*   Updated: 2021/11/21 01:04:20 by lloko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// прочитать и записать в буфер
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

size_t	ft_strlen(const char *s)
{
	size_t	a;

	a = 0;
	while (s[a] != '\0')
	{
		a++;
	}
	return (a);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*answ;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	answ = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!answ)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
		answ[j++] = s1[i++];
	i = 0;
	while (s2[i])
		answ[j++] = s2[i++];
	answ[j] = '\0';
	return (answ);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			return ((char *)s + i);
		i++;
	}
	if (*s == '\0' && c == '\0')
		return ((char *)s);
	return (NULL);
}

static char	readstr(int fd, char *str)
{
	char	*line;
	int		flag;
	int		check;
	int		BUFFER_SIZE;

	line = (char *)malloc(BUFFER_SIZE + 1);
	if (!line)
		return (0);
	flag = 1;
	check = 0;
	while (check == 0 && flag)
	{
		flag = read(fd, line, BUFFER_SIZE);
		if (flag == -1)
		{
			free (line);
			return (0);
		}
		if (ft_strchr(str, '\n') != 0)
			check = 1;
		line[flag] = '\0';
		str = ft_strjoin(str, line);
	}
	return (str);
}

int	main(void)
{
	char	popytka;

	popytka = readstr(1, "text.txt");
	printf("%d", popytka);
}
//

/* char	*get_next_line(int fd)
{
	static char	*buf;
	char		ostatok;
} */