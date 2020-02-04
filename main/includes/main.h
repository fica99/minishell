/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 16:45:35 by aashara-          #+#    #+#             */
/*   Updated: 2020/02/04 20:33:30 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <stdlib.h>
# include "variables.h"
# include "exec_hash_tables.h"
# include "ft_readline.h"
# include "lex.h"
# include "parser.h"
# include "interpretator.h"

/*
**			main.c
*/
void		ft_system(char **line);
#endif
