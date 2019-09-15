/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 21:34:27 by ggrimes           #+#    #+#             */
/*   Updated: 2019/09/14 19:39:34 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

t_token		*ready_token(t_string *str, t_lexer_params prm)
{
	t_token *token;

	if (!(token = new_token()))
		return (NULL);
	if (!(token->lexeme = ft_strdup(prm.str)))
		return (NULL);
	token->type = prm.type;
	token->start_index = str->index;
	str->index = prm.index;
	token->fin_index = prm.index;
	return (token);
}

int			define_class(int type, t_matrix *m_class)
{
	if (type < 0 && type >= m_class->cols)
		return (-2);
	return (m_class->data[0][type]);
}