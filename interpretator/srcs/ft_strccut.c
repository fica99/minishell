/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strccut.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 17:45:21 by mmarti            #+#    #+#             */
/*   Updated: 2019/12/21 17:45:23 by mmarti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

char	*ft_stricut(char *str, int i)
{
	if (!str)
		return (0);
	if (i > (int)ft_strlen(str) - 1)
		return (str);
	str += i;
	while (*++str)
		*(str - 1) = *str;
	*(str - 1) = 0;
	return (str);
}

char	*ft_strccut(char *str, char c)
{
	char *tmp;

	if (!str)
		return (0);
	while ((tmp = ft_strchr(str, c)))
		ft_stricut(str, tmp - str);
	return (str);
}