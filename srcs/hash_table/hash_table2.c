/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 18:27:12 by aashara-          #+#    #+#             */
/*   Updated: 2019/07/03 17:47:30 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

t_hash				**make_hash_table(char **path, unsigned short len)
{
	t_hash			**table;
	DIR				*folder;
	struct dirent	*file;
	short			j;

	table = init_table(len);
	j = -1;
	while (path[++j])
	{
		folder = check_open(path[j]);
		while ((file = readdir(folder)))
		{
			if (!ft_strcmp(file->d_name, ".") || !ft_strcmp(file->d_name, ".."))
				continue ;
			write_hash(file->d_name, path[j], table, len);
		}
		check_close(folder);
	}
	return (table);
}

t_hash				**init_table(unsigned short len)
{
	t_hash			**table;
	short			i;

	if (!(table = (t_hash**)malloc(sizeof(t_hash*) *
					(len + 1))))
		print_error("42sh", "malloc() error", NULL, ENOMEM);
	i = -1;
	while (++i <= len)
		table[i] = NULL;
	return (table);
}

t_hash				*init_hash(void)
{
	t_hash			*hash;

	if (!(hash = (t_hash*)malloc(sizeof(t_hash))))
		print_error("42sh", "malloc() error", NULL, ENOMEM);
	hash->name = NULL;
	hash->path = NULL;
	hash->next = NULL;
	return (hash);
}

void				write_hash(char *str, char *path, t_hash **table,
unsigned short len)
{
	unsigned short	index;
	t_hash			*copy;
	char			*copy_path;
	t_hash			*next;

	index = hash_index(hashing(str), len);
	copy = init_hash();
	if (!(copy_path = ft_strnew(ft_strlen(path) + 1)))
		print_error("42sh", "malloc() error", NULL, ENOMEM);
	copy_path = ft_strcpy(copy_path, path);
	copy->name = ft_strdup(str);
	copy->path = ft_strjoin(ft_strcat(copy_path, "/"), str);
	copy->index = index;
	ft_memdel((void**)&copy_path);
	if (!(next = table[index]))
		table[index] = copy;
	else
	{
		while (next->next)
			next = next->next;
		next->next = copy;
	}
}

unsigned short		hashing(char *str)
{
	char			ret_size;
	unsigned short	ret;
	char			per_char;

	ret_size = 16;
	ret = 0x5555;
	per_char = 7;
	while (*str)
	{
		ret ^= *str++;
		ret = ((ret << per_char) | (ret >> (ret_size - per_char)));
	}
	return (ret);
}