/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomecker <tomecker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 16:55:43 by tecker            #+#    #+#             */
/*   Updated: 2024/12/26 15:02:15 by tomecker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*find_new_rest(char *c)
{
	int		len;
	char	*new;

	len = ft_strchr(c, '\n') - c;
	new = ft_substr(c, len + 1, ft_strlen(c));
	free(c);
	if (new == NULL)
		return (NULL);
	if (new[0] == '\0')
		return (free(new), NULL);
	return (new);
}

char	*search_for_nl(char *c)
{
	int		len;
	char	*new;

	len = ft_strchr(c, '\n') - c;
	new = ft_substr(c, 0, len + 1);
	if (new == NULL)
		return (NULL);
	if (new[0] == '\0')
		return (free(new), NULL);
	return (new);
}

char	*read_from_file(int fd, char *rest)
{
	char	*buffer;
	int		bytesread;
	char	*tmp;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (buffer == NULL)
		return (free(rest), NULL);
	bytesread = 1;
	while (!ft_strchr(rest, '\n') && bytesread != 0)
	{
		bytesread = read(fd, buffer, BUFFER_SIZE);
		if (bytesread == -1)
		{
			free (rest);
			return (free(buffer), NULL);
		}
		buffer[bytesread] = '\0';
		tmp = rest;
		rest = ft_strjoin(rest, buffer);
		free(tmp);
		if (rest == NULL)
			return (free(buffer), NULL);
	}
	free (buffer);
	return (rest);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*rest[FD_OPEN];

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= FD_OPEN)
		return (NULL);
	if (rest[fd] == NULL)
		rest[fd] = ft_strdup("");
	if (rest[fd] == NULL)
		return (NULL);
	rest[fd] = read_from_file(fd, rest[fd]);
	if (rest[fd] == NULL)
		return (NULL);
	line = search_for_nl(rest[fd]);
	if (!line)
	{
		if (rest[fd] != NULL)
		{
			free(rest[fd]);
			rest[fd] = NULL;
		}
		return (NULL);
	}
	rest[fd] = find_new_rest(rest[fd]);
	return (line);
}

// #include <stdio.h>
// int main(void)
// {
//     int fd[3];
//     char *str;
//     fd[0] = open("test1.txt", O_RDONLY);
//     fd[1] = open("test2.txt", O_RDONLY);
//     fd[2] = open("test3.txt", O_RDONLY);
// 	for (int i = 0; i < 3; i++)
// 	{
// 		str = get_next_line(fd[0]);
// 		printf("output fd[0]:	%s", str);
//         free (str);
// 		str = get_next_line(fd[1]);
// 		printf("output fd[1]:	%s", str);
//         free (str);
// 		str = get_next_line(fd[2]);
// 		printf("output fd[2]:	%s\n", str);
//         free (str);
// 	}
//     close (fd[0]);
//     close (fd[1]);
//     close (fd[2]);
//     return (0);
// }
