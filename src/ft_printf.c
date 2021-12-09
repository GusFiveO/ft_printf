/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alorain <alorain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 11:57:14 by alorain           #+#    #+#             */
/*   Updated: 2021/12/09 18:45:37 by alorain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"
#include "ft_printf.h"
#include <stdio.h>

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
			/* printf("str[i] in:%c i:%ld\n", str[i], i); */
			print_arg(&flag, vl);
		}
		if (!str[i])
			break ;
		if (str[i] != '%')
		{
			/* printf("str[i]  :%c i :%ld\n", str[i], i); */
			write_buff((char*)&str[i], 1);
			i++;
		}
	}
	printed_char = manage_buff(NULL, 0);
	va_end(vl);
	return (printed_char);
}

/* int main()
{ */
/* 	char	*str = "yololo";
	char *s2 = "Mussum Ipsum, cacilds vidis litro abertis. Posuere libero varius. Nullam a nisl ut ante blandit hendrerit. Aenean sit amet nisi. Atirei o pau no gatis, per gatis num morreus.";
	ft_printf("ft_printf : %c-%c-%c-\n", '0', 0, '1');
	printf("___printf : %c-%c-%c-\n", '0', 0, '1');
	int _p = printf("___printf : %s %s %s %s %s\n", " - ", "", "5", "", s2);
	int ft = ft_printf("ft_printf : %s %s %s %s %s\n", " - ", "", "5", "", s2); */
/* 	int _p = printf("p_ :%4d\n", -14);
	int ft = ft_printf("ft :%4d\n", -14);
	printf("ft = %d\n_p = %d\n", ft, _p);
	return (1);
}  */