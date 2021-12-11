/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_arg2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alorain <alorain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 11:14:17 by alorain           #+#    #+#             */
/*   Updated: 2021/12/11 12:58:34 by alorain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"

void	manage_char(t_printf *flag, char c)
{
	if (flag->count)
	{
		if (flag->minus)
		{
			write_buff(&c, 1);
			print_char(' ', flag->count - 1);
		}
		else
		{
			print_char(' ', flag->count - 1);
			write_buff(&c, 1);
		}
	}
	else
		write_buff(&c, 1);
}

static int	str_null(t_printf *flag, char *str)
{
	if (str)
		return (0);
	if (flag->count == 0 && flag->dot == 0)
		return (1);
	if (flag->count == 0 || flag->dot == -1)
	{
		if (flag->count && !flag->minus)
			print_char(' ', flag->count - 6);
		write_buff("(null)", 6);
		if (flag->count && flag->minus)
			print_char(' ', flag->count - 6);
		return (1);
	}
	if (flag->dot >= 6)
	{
		print_char(' ', flag->count - 6);
		write_buff("(null)", 6);
	}
	else
		print_char(' ', flag->count);
	return (1);
}

void	manage_string(t_printf *flag, char *str)
{
	int	str_len;

	str_len = 0;
	if (str_null(flag, str))
		return ;
	str_len = reg_len(flag, str);
	if (!flag->minus)
		print_char(' ', flag->count - str_len);
	ft_putstr(str, str_len);
	if (flag->minus)
		print_char(' ', flag->count - str_len);
}

void	print_char(char c, int n)
{
	int	i;

	i = 0;
	if (n <= 0)
		return ;
	while (i < n)
	{
		write_buff(&c, 1);
		i++;
	}
}
