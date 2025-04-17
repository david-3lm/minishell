/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atouc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-migu <cde-migu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:24:04 by cde-migu          #+#    #+#             */
/*   Updated: 2025/04/17 18:28:53 by cde-migu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_isspace(char c)
{
	if (c == ' ' || c == '\n' || c == '\t')
		return (1);
	else if (c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

unsigned char ft_atouc(const char *str)
{
	unsigned char result;
	int sign;

	sign = 1;
	result = 0;
	while (ft_isspace(*str))
		str++;
    if (*str == '-')
	{
        sign = -1;
        str++;
    }
	else if (*str == '+')
        str++;
	if (!ft_isdigit(*nptr))
		return (0);
    while (*str >= '0' && *str <= '9')
	{
        result = result * 10 + (*str - '0');
        str++;
    }
    if (sign == -1)
		result = (unsigned char)(256 - result);
    return (result);
}
