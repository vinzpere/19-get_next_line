/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpere <vpere@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:16:24 by vpere             #+#    #+#             */
/*   Updated: 2024/06/26 11:26:45 by vpere            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
# if BUFFER_SIZE > 10000000 || BUFFER_SIZE < 1
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 512
# endif

# include <fcntl.h>
# include <stdlib.h>
# include <sys/syslimits.h>
# include <unistd.h>
# define MAX_FD OPEN_MAX

size_t	ft_strlen(char *str);
char	*ft_strchr(char *s, int c);
char	*join(char *s1, char *s2);
char	*extract_line(char *buffer);
char	*rest_line(char *buffer);
char	*new_line(int fd, char *buffer);
char	*get_next_line(int fd);
void	ft_free(char **ptr);

#endif