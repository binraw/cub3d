/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtruvelo <rtruvelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 15:23:31 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/10/14 07:54:59 by rtruvelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <stddef.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>
# ifndef BUFFER_SIZE

#  define BUFFER_SIZE 1000

# endif

char		*get_next_line(int fd);
char		*ft_strchr_get( char *string, int searchedChar);
char		*ft_strdup_get( char *source);
char		*ft_strjoin_get(char	*s1, char	*s2);
size_t		ft_strlen_get( char *str);
#endif