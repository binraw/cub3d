/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 12:55:05 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/11/26 20:15:39 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	if (write(fd, s, ft_strlen(s)) == -1 || write(fd, "\n", 1) == -1)
		perror("crash write in ft_putendl_fd");
}
