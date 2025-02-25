/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:55:00 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/10/17 19:43:22 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_reboot_start(void)
{
	char	*reboot;

	reboot = malloc(sizeof(char));
	if (reboot == 0)
	{
		return (NULL);
	}
	reboot[0] = '\0';
	return (reboot);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*pointer;
	size_t	i;

	if (start > ft_strlen(s))
		return (ft_reboot_start());
	else if ((ft_strlen(s) - start) < len)
		len = ft_strlen(s) - start;
	pointer = ft_calloc((len + 1), sizeof(char));
	if (!pointer)
		return (NULL);
	if (pointer == 0)
		return (NULL);
	i = 0;
	while (s[start] != '\0' && i < len)
	{
		pointer[i] = s[start];
		i++;
		start++;
	}
	pointer[i] = '\0';
	return (pointer);
}
