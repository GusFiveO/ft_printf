/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alorain <alorain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 18:31:56 by alorain           #+#    #+#             */
/*   Updated: 2021/12/09 18:18:56 by alorain          ###   ########.fr       */
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
			print_char(' ', flag->count -1);
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

void	manage_integer(t_printf *flag, int n)
{	
	int espace;
	int	nb_digits;

	nb_digits = count_digit_base(n, 10);
	espace = manage_space(flag, n);
	if (flag->minus && flag->count && !flag->dot)
	{
		ft_putnbr(n);
		print_char(' ', flag->count - espace - nb_digits);
	}
	else if (flag->dot)
	{
		print_char('0', flag->dot - nb_digits);
		ft_putnbr(n);
	}
	else
	{
		if (flag->count)
			print_char(' ', flag->count - espace - nb_digits);
		ft_putnbr(n);
	}
}

void	manage_hexa(t_printf *flag, unsigned int nbr)
{
	int	diez;
	int	nb_digits;

	diez = 0;
	nb_digits = count_digit_base(nbr, 16);
	if (flag->diez && flag->count && !flag->minus)
	{
		print_char(' ', flag->count - diez - nb_digits);
		diez = manage_diez(flag, nbr);
	}
	else if (flag->diez && flag->count && flag->minus)
	{
		diez = manage_diez(flag, nbr);
		print_char(' ', flag->count - diez - nb_digits);
	}
	else if (flag->diez && flag->count && flag->zero)
	{
		diez = manage_diez(flag, nbr);
		print_char('0', flag->count - diez - nb_digits);
	}
	else
	{
		if (flag->count)
			print_char(' ', flag->count - nb_digits);
		manage_diez(flag, nbr);
	}
}

void	manage_hexa_maj(t_printf *flag, unsigned int nbr)
{
	int	diez;
	int	nb_digits;

	diez = 0;
	nb_digits = count_digit_base(nbr, 16);
	if (flag->diez && flag->count && !flag->minus)
	{
		print_char(' ', flag->count - diez - nb_digits);
		diez = manage_diez_maj(flag, nbr);
	}
	else if (flag->diez && flag->count && flag->minus)
	{
		diez = manage_diez_maj(flag, nbr);
		print_char(' ', flag->count - diez - nb_digits);
	}
	else if (flag->diez && flag->count && flag->zero)
	{
		diez = manage_diez_maj(flag, nbr);
		print_char('0', flag->count - diez - nb_digits);
	}
	else
	{
		if (flag->count)
			print_char(' ', flag->count - nb_digits);
		manage_diez_maj(flag, nbr);
	}
}

void	manage_null_string(t_printf *flag)
{
	if (flag->minus && flag->count)
	{
		write_buff("(null)", 6);
		print_char(' ', flag->count - 6);
	}
	else if (flag->count)
	{
		print_char(' ', flag->count - 6);
		write_buff("(null)", 6);
	}
	else
		write_buff("(null)", 6);

}

void	manage_string(t_printf *flag, char *str)
{
	size_t	str_len;

/* 	printf("str :%s\n", str);
	printf("str_len :%ld\n", str_len); */
	str_len = 0;
	if (!str)
		return (manage_null_string(flag));
	if (flag->dot == -1)
		return ;
	str_len = manage_strlen(flag, str);
	if (flag->minus && flag->count)
	{
		write_buff(str, str_len);
		print_char(' ', flag->count - str_len);
	}
	else if (flag->count)
	{
		print_char(' ', flag->count - str_len);
		write_buff(str, str_len);
	}
	else
		write_buff(str, str_len);
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
		manage_hexa(flag, va_arg(vl, unsigned int));
	if (flag->type == 'X')
		manage_hexa_maj(flag, va_arg(vl, unsigned int));
	if (flag->type == 's')
		manage_string(flag, va_arg(vl, char*));
	if (flag->type == 'u')
		manage_uinteger(flag, va_arg(vl, unsigned int));
	if (flag->type == 'p')
		manage_pointer(flag, va_arg(vl, unsigned long));
	if (flag->type == '%')
		write_buff("%", 1);
}