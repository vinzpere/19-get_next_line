/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpere <vpere@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:16:15 by vpere             #+#    #+#             */
/*   Updated: 2024/06/26 11:37:56 by vpere            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*extract_line(char *buffer)
{
	size_t	i;
	char	*line;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (ft_free(&line), NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*rest_line(char *buffer)
{
	size_t	i;
	size_t	j;
	char	*rest;

	i = 0;
	j = 0;
	if (!buffer)
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	if (!buffer[i])
		return (ft_free(&buffer), NULL);
	rest = malloc(ft_strlen(buffer) - i + 1);
	if (!rest)
		return (ft_free(&rest), ft_free(&buffer), NULL);
	while (buffer[i])
		rest[j++] = buffer[i++];
	rest[j] = '\0';
	return (ft_free(&buffer), rest);
}

char	*new_line(int fd, char *buffer)
{
	char	*temp;
	ssize_t	bytes_read;

	temp = malloc(BUFFER_SIZE + 1);
	if (!temp)
		return (free(buffer), NULL);
	while (!buffer || !ft_strchr(buffer, '\n'))
	{
		bytes_read = read(fd, temp, BUFFER_SIZE);
		if (bytes_read == -1)
			return (ft_free(&temp), ft_free(&buffer), NULL);
		temp[bytes_read] = '\0';
		if (bytes_read == 0)
			break ;
		buffer = join(buffer, temp);
		if (!buffer)
			return (NULL);
	}
	ft_free(&temp);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*nextline[MAX_FD];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= 2147483647)
		return (ft_free(&nextline[fd]), NULL);
	nextline[fd] = new_line(fd, nextline[fd]);
	if (!nextline[fd])
		return (nextline[fd] = NULL, NULL);
	line = extract_line(nextline[fd]);
	if (!line)
		return (ft_free(&nextline[fd]), NULL);
	nextline[fd] = rest_line(nextline[fd]);
	if (!nextline[fd])
		nextline[fd] = NULL;
	if (!ft_strchr(line, '\n'))
		ft_free(&nextline[fd]);
	return (line);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char	*str1;
// 	char	*str2;
// 	int		fd1;
// 	int		fd2;
// 	int		i;

// 	i = 1;
// 	fd1 = open("file.txt", O_RDONLY);
// 	fd2 = open("deuxieme.txt", O_RDONLY);
// 	// while ((str = get_next_line(fd)) != NULL)
// 	// {
// 	// 	printf("[%d]> %s", i, str);
// 	// 	free(str);
// 	// 	i++;
// 	// }
// 	while (i < 10)
// 	{
// 		str1 = get_next_line(fd1);
// 		str2 = get_next_line(fd2);
// 		// system("leaks a.out");
// 		printf("[%d]> %s", i, str1);
// 		printf("[%d]> %s", i, str2);
// 		free(str1);
// 		free(str2);
// 		i++;
// 	}
// 	close(fd1);
// 	close(fd2);
// 	return (0);
// }

// int main()
// {
// 	int fd = open("nl", O_RDONLY);
// 	char *str;

// 	while ((str = get_next_line(fd)) != NULL)
// 	{
// 		printf("%s", str);
// 	}
// }