/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_add_fun.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 19:53:41 by ggrimes           #+#    #+#             */
/*   Updated: 2019/12/07 17:07:11 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "calc.h"

static int	calc_add_sub_next(int result, t_calc_tkns *s_tokens,
	size_t *index, t_calc_err *error)
{
	t_calc_tkntype	oper;

	while (1)
	{
		oper = s_tokens->tokens[*index].type;
		if (oper == CALC_PLUS || oper == CALC_MINUS)
			(*index)++;
		if (oper == CALC_PLUS)
			result += calc_mul_div_mod(s_tokens, index, error);
		else if (oper == CALC_MINUS)
			result += -1 * calc_mul_div_mod(s_tokens, index, error);
		else
			break ;
		if (error->status)
			return (0);
	}
	return (result);
}

t_calc_tkn	*calc_get_add_tkn(char *str, size_t pos)
{
	t_calc_tkn		*token;
	t_calc_tkntype	type;

	if (!str)
		return (NULL);
	type = (*str == '+') ? CALC_PLUS : CALC_MINUS;
	if (!(token = calc_newtkn(NULL, type)))
		return (NULL);
	token->start_pos = pos;
	token->end_pos = pos + 1;
	return (token);
}

int			calc_add_sub(t_calc_tkns *s_tokens, size_t *index,
	t_calc_err *error)
{
	int		result;

	if (!s_tokens || !calc_check_index(s_tokens, *index))
		return (calc_error(error, CALC_ERR_NULL_OR_IND));
	result = calc_mul_div_mod(s_tokens, index, error);
	if (error->status)
		return (0);
	result = calc_add_sub_next(result, s_tokens, index, error);
	return (result);
}
