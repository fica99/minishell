/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 18:06:10 by aashara-          #+#    #+#             */
/*   Updated: 2019/08/30 22:35:09 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASH_TABLE_H
# define HASH_TABLE_H

# include <dirent.h>
# include <stdlib.h>

# define PREV_CUR_DIR 2

typedef struct		s_hash
{
	char			*path;
	char			*name;
	struct s_hash	*next;
}					t_hash;

t_hash				**init_hash_table(unsigned short *hash_table_size);
unsigned short		get_hash_table_size(char **path);
unsigned short		hash_index(unsigned short key, unsigned short len);
DIR					*check_open(char *path);
void				check_close(DIR *folder);
t_hash				**make_hash_table(char **path, unsigned short len);
t_hash				**init_table(unsigned short len);
t_hash				*init_hash(void);
unsigned short		hashing(char *str);
void				write_hash(char *str, char *path, t_hash **table,
unsigned short len);
void				free_my_hash_table(t_hash **hash_table,
unsigned short *hash_table_size);
void				free_hash_table(t_hash **table, unsigned short len);
#endif
