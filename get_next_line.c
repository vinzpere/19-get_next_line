/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpere <vpere@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:16:15 by vpere             #+#    #+#             */
/*   Updated: 2024/06/26 11:18:41 by vpere            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	static char	*nextline;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= 2147483647)
		return (ft_free(&nextline), NULL);
	nextline = new_line(fd, nextline);
	if (!nextline)
		return (nextline = NULL, NULL);
	line = extract_line(nextline);
	if (!line)
		return (ft_free(&nextline), NULL);
	nextline = rest_line(nextline);
	if (!nextline)
		nextline = NULL;
	if (!ft_strchr(line, '\n'))
		ft_free(&nextline);
	return (line);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char	*str;
// 	int		fd;
// 	int		i;

// 	i = 1;
// 	fd = open("file.txt", O_RDONLY);
// 	// while ((str = get_next_line(fd)) != NULL)
// 	// {
// 	// 	printf("[%d]> %s", i, str);
// 	// 	free(str);
// 	// 	i++;
// 	// }
// 	while (i < 10)
// 	{
// 		str = get_next_line(fd);
// 		system("leaks a.out");
// 		printf("[%d]> %s", i, str);
// 		free(str);
// 		i++;
// 	}
// 	close(fd);
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