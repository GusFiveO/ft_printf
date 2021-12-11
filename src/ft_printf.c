/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alorain <alorain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 11:57:14 by alorain           #+#    #+#             */
/*   Updated: 2021/12/11 13:25:37 by alorain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"
#include "ft_printf.h"

int	ft_printf(const char *str, ...)
{
	va_list		vl;
	size_t		i;
	size_t		printed_char;
	t_printf	flag;

	printed_char = 0;
	i = 0;
	va_start(vl, str);
	while (str[i])
	{
		if (str[i] == '%' && str[i + 1])
		{
			i++;
			i += parse_flags(str + i, &flag);
			print_arg(&flag, vl);
		}
		if (!str[i])
			break ;
		if (str[i] != '%')
			write_buff((char *)&str[i++], 1);
	}
	printed_char = manage_buff(NULL, 0);
	va_end(vl);
	return (printed_char);
}

#include <limits.h>
#include <stdio.h>

int main()
{
/* 	char *s2 = "Mussum Ipsum, cacilds vidis litro abertis. Posuere libero varius. Nullam a nisl ut ante blandit hendrerit. Aenean sit amet nisi. Atirei o pau no gatis, per gatis num morreus.";
	ft_printf("ft_printf : %c-%c-%c-\n", '0', 0, '1');
	printf("___printf : %c-%c-%c-\n", '0', 0, '1');
	int _p = printf("___printf : %s %s %s %s %s\n", " - ", "", "5", "", s2);
	int ft = ft_printf("ft_printf : %s %s %s %s %s\n", " - ", "", "5", "", s2); */
	/* int _p =  *//* printf("p_ :%-13x\n", UINT_MAX); */
	/* int ft = */ /* ft_printf("ft :%-13x\n", UINT_MAX); */
/* 	int _p = printf("p_ :%-12x\n", LONG_MIN);
	int ft = ft_printf("ft :%-12x\n", LONG_MIN); */
	int _p = printf("p_ :%.10d\n", -10);
	int ft = ft_printf("ft :%.10d\n", -10);
	printf("ft = %d\n_p = %d\n", ft, _p);
	return (1);
}
