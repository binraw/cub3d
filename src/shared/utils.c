/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fberthou <fberthou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 10:40:16 by fberthou          #+#    #+#             */
/*   Updated: 2024/11/19 10:41:37 by fberthou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

size_t	skip_spaces(char *buffer)
{
	size_t	i;

	i = 0;
	while (buffer[i] && (buffer[i] == ' ' || buffer[i] == '\t'))
		i++;
	return (i);
}
