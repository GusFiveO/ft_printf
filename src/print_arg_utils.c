/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_arg_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alorain <alorain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 18:34:08 by alorain           #+#    #+#             */
/*   Updated: 2021/12/10 22:40:08 by alorain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"

size_t	count_digit_base(int n, int base_len)
{
	int		len;
	long	nb;

	len = 0;
	nb = n;
	if (nb <= 0)
		nb *= -1;
	if (nb == 0)
		len = 1;
	while (nb != 0)
	{
		len++;
		nb = nb / base_len;
	}
	return (len);
}

size_t	count_digit_base_un(unsigned long n, size_t base_len)
{
	size_t	len;

	len = 0;
	if (n <= 0)
		len = 1;
	while (n != 0)
	{
		len++;
		n = n / base_len;
	}
	return (len);
}

int	manage_strlen(t_printf *flag, char *str)
{
	int	str_len;

	str_len = (int)ft_strlen(str);
	if (flag->dot && flag->dot < str_len)
		return (flag->dot);
	return (str_len);
}

int	manage_space(t_printf *flag, int n)
{
	if (flag->space && n >= 0)
	{
		write_buff(" ", 1);
		return (1);
	}
	return (0);
}
