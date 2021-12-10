/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alorain <alorain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 14:37:20 by alorain           #+#    #+#             */
/*   Updated: 2021/12/10 20:02:50 by alorain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_UTILS_H
# define FT_PRINTF_UTILS_H

#include <stdio.h>
# include <unistd.h>
# include "ft_printf.h"

void	ft_putchar(char c);
void	ft_putstr(char *str, int len);
void	ft_putnbr(int n);
size_t	is_in(char c, char *str);	
void	ft_putnbr_base(unsigned long n, char *base);

	/* parser.c */

size_t	parse_flags(const char *str, t_printf *flag);

	/* buffer.c */
	
# define BUFFER_SIZE 1028
size_t	manage_buff(char *str, size_t n);
void	write_buff(char *str, size_t n);

	/* print_arg.c */

void	manage_char(t_printf *flag, char c);
void	print_arg(t_printf *flag, va_list vl);
void	manage_string(t_printf *flag, char *str);
void	manage_hexa(t_printf *flag, unsigned int nbr, char *base);
void	manage_integer(t_printf *flag, int n);

	/* print_arg_utils.c */

size_t	count_digit_base(int n, int base_len);
int		manage_space_un(t_printf *flag, unsigned int n);
int		manage_space(t_printf *flag, int n);
int		manage_strlen(t_printf *flag, char *str);
size_t	count_digit_base_un(unsigned long n, size_t base_len);
void	ft_putnbr_zero_int(int n);

	/* print_arg_utils2.c */

int		manage_diez(t_printf *flag, unsigned long n);
int		manage_diez_maj(t_printf *flag, unsigned int n);
void	manage_pointer(t_printf *flag, unsigned long p);
void	manage_uinteger(t_printf *flag, unsigned int un);
void	print_char(char c, int n);

	/*utils.c*/

int		reg_len(t_printf *flag, char *str);
void	reg_dot(t_printf *flag, int nb_digits);

#endif