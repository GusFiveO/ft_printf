/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alorain <alorain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 18:07:24 by alorain           #+#    #+#             */
/*   Updated: 2021/12/10 21:02:48 by alorain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"

void	reg_dot(t_printf *flag, int nb_digits)
{
	if (flag->dot < nb_digits)
		flag->dot = nb_digits;
}

int	reg_len(t_printf *flag, char *str)
{
	int str_len;

	str_len = ft_strlen(str);
	if (flag->dot < str_len && flag->dot != -1)
		return (flag->dot);
	return (str_len);
}
