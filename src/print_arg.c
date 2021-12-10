/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alorain <alorain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 18:31:56 by alorain           #+#    #+#             */
/*   Updated: 2021/12/10 22:40:09 by alorain          ###   ########.fr       */
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

int	str_null(t_printf *flag, char *str)
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
	if (flag->dot >= 6 )
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
	int str_len;

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

void	manage_uinteger(t_printf *flag, unsigned int nbr)
{
	int nb_digits;

	nb_digits = count_digit_base_un(nbr, 10);
	reg_dot(flag, nb_digits);
	if (!flag->zero && !flag->minus)
		print_char(' ', flag->count - flag->dot);
	if (flag->plus && nbr > 0)
		write_buff("+", 1);
	else if (flag->zero && !flag->minus)
		print_char('0', flag->count - flag->dot);
	print_char('0', flag->dot - nb_digits);
	ft_putnbr_base(nbr, "0123456789");
	if (flag->minus)
		print_char(' ', flag->count - flag->dot);
}

void	manage_integer(t_printf *flag, int nbr)
{
	int nb_digits;
	int prefix;

	prefix = 0;
	if ((flag->plus && nbr > 0) || (flag->count && nbr < 0))
		prefix ++;
	nb_digits = count_digit_base(nbr, 10);
	reg_dot(flag, nb_digits);
	if (!flag->zero && !flag->minus)
		print_char(' ', flag->count - flag->dot - prefix);
	if (nbr < 0)
		write_buff("-", 1);
	if (flag->plus && nbr > 0)
		write_buff("+", 1);
	else if (flag->zero && !flag->minus)
		print_char('0', flag->count - flag->dot - prefix);
	print_char('0', flag->dot - nb_digits);
	ft_putnbr(nbr);
	if (flag->minus)
		print_char(' ', flag->count - flag->dot - prefix);
}

void	manage_hexa(t_printf *flag, unsigned int nbr, char *base)
{
	int nb_digits;
	int	prefix;

	prefix = 0;
	if (nbr && flag->diez)
		prefix = 2;
	nb_digits = count_digit_base_un(nbr, 16);
	reg_dot(flag, nb_digits);
	if (!flag->zero && !flag->minus)
		print_char(' ', flag->count - flag->dot - prefix);
	if (nbr && flag->diez && flag->type == 'X')
		write_buff("0X", 2);
	if (nbr && flag->diez && flag->type == 'x')
		write_buff("0x", 2);
	else if (flag->zero && !flag->minus)
		print_char('0', flag->count - flag->dot - prefix);
	print_char('0', flag->dot - nb_digits);
	ft_putnbr_base(nbr, base);
	if (flag->minus)
		print_char(' ', flag->count - flag->dot - prefix);
}

void	manage_pointer(t_printf *flag, unsigned long p)
{
	int	nb_digits;

	nb_digits = count_digit_base_un(p, 16);
	reg_dot(flag, nb_digits);
	if (!flag->zero && !flag->minus)
	{
		print_char(' ', flag->count - flag->dot - 2);
		write_buff("0x", 2);
	}
	else if (flag->zero && !flag->minus)
	{
		write_buff("0x", 2);
		print_char('0', flag->count - flag->dot - 2);
	}
	else
		write_buff("0x", 2);
	print_char('0', flag->dot - nb_digits);
	ft_putnbr_base(p, "0123456789abcdef");
	if (flag->minus)
		print_char(' ', flag->count - flag->dot - 2);
}

void print_struct(t_printf *flags)
{    
    printf("flags->minus = %d;\n\
    flags->zero = %d;\n\
    flags->space = %d;\n\
    flags->dot = %d;\n\
    flags->diez = %d;\n\
    flags->plus = %d;\n\
    flags->count = %d;\n\
    flags->type = %c;\n", flags->minus, flags->zero, flags->space, flags->dot, flags->diez, flags->plus, flags->count, flags->type);
}

void	print_arg(t_printf *flag, va_list vl)
{
	/* print_struct(flag); */
	if (flag->type == 'c')
		manage_char(flag, (char)(va_arg(vl, int)));
	if (flag->type == 'i' || flag->type == 'd')
		manage_integer(flag, va_arg(vl, int));
	if (flag->type == 'x')
		manage_hexa(flag, va_arg(vl, unsigned int), "0123456789abcdef");
	if (flag->type == 'X')
		manage_hexa(flag, va_arg(vl, unsigned int), "0123456789ABCDEF");
	if (flag->type == 's')
		manage_string(flag, va_arg(vl, char*));
	if (flag->type == 'u')
		manage_uinteger(flag, va_arg(vl, unsigned int));
	if (flag->type == 'p')
		manage_pointer(flag, va_arg(vl, unsigned long));
	if (flag->type == '%')
		write_buff("%", 1);
}