/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alorain <alorain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 18:31:56 by alorain           #+#    #+#             */
/*   Updated: 2021/12/10 16:22:00 by alorain          ###   ########.fr       */
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

int	manage_plus(t_printf *flag, int n)
{
	if (flag->plus && n >= 0)
	{
		write_buff("+", 1);
		return (1);
	}
	return (0);
}

void	manage_zero_negint(t_printf *flag, int n, int espace)
{
	int	nb_digits;
	int plus;

	plus = 0;
	nb_digits = count_digit_base(n, 10);
	if (n < 0)
	{
		write_buff("-", 1);
		print_char('0', flag->count - espace - plus - nb_digits);	
		ft_putnbr_zero_int(n * -1);
	}
	else 
	{
		if (flag->plus)
			plus = 1;
		print_char('0', flag->count - espace - plus - nb_digits);	
		manage_plus(flag, n);
		ft_putnbr_base(n, "0123456789");
	}
}

void	manage_dot_negint(t_printf *flag, int n, int espace)
{
	int	nb_digits;
	int plus;

	plus = 0;
	nb_digits = count_digit_base(n, 10);
	if (n < 0)
	{
		write_buff("-", 1);
		print_char('0', flag->dot - espace - plus - nb_digits + 1);	
		ft_putnbr_zero_int(n * -1);
	}
	else 
	{
		if (flag->plus)
			plus = 1;
		print_char('0', flag->dot - espace - plus - nb_digits);	
		manage_plus(flag, n);
		ft_putnbr_base(n, "0123456789");
	}
}

void	manage_int_else(t_printf *flag, int n, int espace)
{
	int	nb_digits;
	int	plus;

	nb_digits = count_digit_base(n, 10);
	plus = 0;
	if (flag->count)
	{
		if (flag->plus)
			plus = 1;
		print_char(' ', flag->count - espace - plus - nb_digits);
	}
	manage_plus(flag, n);
	ft_putnbr(n);
}

void	manage_integer(t_printf *flag, int n)
{	
	int espace;
	int	nb_digits;
	int	plus;

	nb_digits = count_digit_base(n, 10);
	espace = manage_space(flag, n);
	plus = 0;
	if (flag->minus && flag->count && !flag->dot)
	{
		ft_putnbr(n);
		print_char(' ', flag->count - espace - plus - nb_digits);
	}
	else if (flag->dot)
		manage_dot_negint(flag, n, espace);
	else if (flag->zero)
		manage_zero_negint(flag, n, espace);
	else
		manage_int_else(flag, n, espace);
}

void	manage_hexa(t_printf *flag, unsigned long nbr)
{
	int	diez;
	int	nb_digits;

	diez = 0;
	nb_digits = count_digit_base_un(nbr, 16);
	if (flag->diez && flag->count && !flag->minus)
	{
		print_char(' ', flag->count - diez - nb_digits);
		diez = manage_diez(flag, nbr);
	}
	else if (flag->minus)
	{
		diez = manage_diez(flag, nbr);
		print_char(' ', flag->count - diez - nb_digits);
	}
	else if (flag->zero || flag->dot)
	{
		if (flag->zero)
			print_char('0', flag->count - diez - nb_digits);
		if (flag->dot)
			print_char('0', flag->dot - diez - nb_digits);
		diez = manage_diez(flag, nbr);
	}
	else
	{
		print_char(' ', flag->count - nb_digits);
		manage_diez(flag, nbr);
	}
}

void	manage_hexa_maj(t_printf *flag, unsigned int nbr)
{
	int	diez;
	int	nb_digits;

	diez = 0;
	nb_digits = count_digit_base_un(nbr, 16);
	if (flag->diez && flag->count && !flag->minus && !flag->zero && !flag->dot)
	{
		print_char(' ', flag->count - diez - nb_digits);
		diez = manage_diez_maj(flag, nbr);
	}
	else if (flag->minus)
	{
		diez = manage_diez_maj(flag, nbr);
		print_char(' ', flag->count - diez - nb_digits);
	}
	else if (flag->zero || flag->dot)
	{
		if (flag->zero)
			print_char('0', flag->count - diez - nb_digits);
		else if (flag->dot)
			print_char('0', flag->dot - nb_digits);
		manage_diez_maj(flag, nbr);
	}
	else
	{
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