/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpere <vpere@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:57:37 by vpere             #+#    #+#             */
/*   Updated: 2024/06/25 20:57:18 by vpere            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_free(char **ptr)
{
	free(*ptr);
	*ptr = NULL;
}

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

char	*ft_strchr(char *s, int c)
{
	char	*buffer;
	int		i;

	i = 0;
	buffer = (char *)s;
	while (buffer[i])
	{
		if (buffer[i] == (char)c)
			return (&buffer[i]);
		i++;
	}
	if (buffer[i] == (char)c)
		return (&buffer[i]);
	return (0);
}

char	*join(char *s1, char *s2)
{
	size_t	len1;
	size_t	len2;
	char	*s3;
	size_t	i;
	size_t	j;

	if (!s2)
		return (ft_free(&s1), ft_free(&s2), NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	s3 = malloc(len1 + len2 + 1);
	i = 0;
	j = 0;
	if (!s3)
		return (ft_free(&s1), ft_free(&s2), NULL);
	while (i < len1)
	{
		s3[i] = s1[i];
		i++;
	}
	while (j < len2)
		s3[i++] = s2[j++];
	s3[i] = '\0';
	return (ft_free(&s1), s3);
}
