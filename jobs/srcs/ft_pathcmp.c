/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pathcmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 17:43:02 by mmarti            #+#    #+#             */
/*   Updated: 2019/12/23 17:43:05 by mmarti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

int			ft_pathcmp(char *p1, char *p2)
{
	while (*p1 && *p1 == *p2)
	{
		p1++;
		p2++;
		if (*p1 == '/' || *p2 == '/')
		{
			while (*p1 == '/')
				p1++;
			while (*p2 == '/')
				p2++;
			continue ;
		}
	}
	return (*p1 - *p2);
}