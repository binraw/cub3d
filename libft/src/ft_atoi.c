/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:19:54 by rtruvelo          #+#    #+#             */
/*   Updated: 2024/11/15 17:35:17 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	white_space(const char *str)
{
	int		count;
	int		i;

	count = 0;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
	{
		i++;
		count++;
	}
	return (count);
}

int	ft_atoi(const char *str)
{
	long long int	result;
	long long int	resultcpy;
	int				sign;
	int				i;

	result = 0;
	sign = 1;
	i = 0 + white_space(str);
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (str[i] < '0' || str[i] > '9')
		return (-1);
	while (str[i] != '\0' && str[i] >= 48 && str[i] <= 57)
	{
		resultcpy = result;
		result = ((result * 10) + (str[i] - 48) * sign);
		if (result < resultcpy && sign == 1)
			return (-1);
		if (result > resultcpy && sign == -1)
			return (0);
		i++;
	}
	return ((int)result);
}
