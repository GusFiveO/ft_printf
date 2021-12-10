/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_arg_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alorain <alorain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 18:37:09 by alorain           #+#    #+#             */
/*   Updated: 2021/12/10 21:53:55 by alorain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"

int	manage_diez(t_printf *flag, unsigned long n)
{
	if (flag->diez && n > 0)
	{
		write_buff("0x", 2);
		ft_putnbr_base(n, "0123456789abcdef");
		return (2);
	}
	else if (n == 0)
	{
		write_buff("0", 1);
		return (0);
	}
	else if (!flag->diez)
		ft_putnbr_base(n, "0123456789abcdef");
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
	else if (n == 0)
	{
		write_buff("0", 1);
		return (0);
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

/* void	manage_pointer(t_printf *flag, unsigned long p)
{
	size_t	nb_digits;
	
	nb_digits = 0;
	nb_digits = count_digit_base_un(p, 16);
	if (flag->minus && flag->count)
	{
		write_buff("0x", 2);
		ft_putnbr_base(p, "0123456789abcdef");
		print_char(' ', flag->count - nb_digits - 2);
	}
	else if (flag->count)
	{
		print_char(' ', flag->count - nb_digits - 2);
		write_buff("0x", 2);
		ft_putnbr_base(p, "0123456789abcdef");
	}
	else
	{
		write_buff("0x", 2);
		ft_putnbr_base(p, "0123456789abcdef");
	}
} */