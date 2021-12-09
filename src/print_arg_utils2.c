/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_arg_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alorain <alorain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 18:37:09 by alorain           #+#    #+#             */
/*   Updated: 2021/12/09 15:50:50 by alorain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"

int	manage_diez(t_printf *flag, unsigned int n)
{
	if (flag->diez && n > 0)
	{
		write_buff("0x", 2);
		ft_putnbr_base((unsigned long)n, "0123456789abcdef");
		return (2);
	}
	else if (!flag->diez)
		ft_putnbr_base((unsigned long)n, "0123456789abcdef");
	return (0);
}

int	manage_diez_maj(t_printf *flag, unsigned int n)
{
	if (flag->diez && n > 0)
	{
		write_buff("0X", 2);
		ft_putnbr_base((unsigned long)n, "0123456789ABCDEF");
		return (2);
	}
	else if (!flag->diez)
		ft_putnbr_base((unsigned long)n, "0123456789ABCDEF");
	return (0);
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

void	manage_uinteger(t_printf *flag, unsigned int un)
{
	int	nb_digits;

	nb_digits = count_digit_base_un((unsigned long)un, 10);
	if (flag->minus && flag->count&& !flag->dot)
	{
		ft_putnbr_base(un, "0123456789");
		print_char(' ', flag->count - nb_digits);
	}
	else if (flag->dot)
	{
		print_char('0', flag->dot - nb_digits);
		ft_putnbr_base(un, "0123456789");
	}
	else
	{
		if (flag->count)
			print_char(' ', flag->count - nb_digits);
		ft_putnbr_base(un, "0123456789");
	}
}

void	manage_pointer(t_printf *flag, unsigned long p)
{
	size_t	nb_digits;
	
	nb_digits = 0;
	if (p)
		nb_digits = count_digit_base_un(p, 16);
	if (flag->minus && flag->count)
	{
		if (!p)
		{	
			write_buff("(nil)", 5);
			print_char(' ', flag->count - nb_digits - 5);
		}
		else
		{
			write_buff("0x", 2);
			ft_putnbr_base(p, "0123456789abcdef");
			print_char(' ', flag->count - nb_digits - 2);
		}
	}
	else if (flag->count)
	{
		if (p)
		{
			print_char(' ', flag->count - nb_digits - 2);
			write_buff("0x", 2);
			ft_putnbr_base(p, "0123456789abcdef");
		}
		else
		{
			print_char(' ', flag->count - nb_digits - 5);
			write_buff("(nil)", 5);
		}
	}
	else
	{
		if (p)
		{
			write_buff("0x", 2);
			ft_putnbr_base(p, "0123456789abcdef");
		}
		else
			write_buff("(nil)", 5);
	}
}