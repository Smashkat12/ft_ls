/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_entry_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorulan <kmorulan@student.wethinkcode.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 09:44:48 by kmorulan          #+#    #+#             */
/*   Updated: 2019/09/09 18:03:21 by kmorulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"


int		creat_dirent_list(t_pathinfo **direntry_l, char *path, t_flag *flags)
{
	DIR				*dir;
	struct dirent	*entry;
	int				total;

	total = 0;
	dir = opendir(path);
	while ((entry = readdir(dir)) != NULL)
	{
		if (entry->d_name[0] != '.' || flags->a)
			total += add_tolist(path, direntry_l, entry);
	}
	closedir(dir);
	return (total);
}
char	*correct_path(char *d_or_f_name, char *d_name)
{
	char	*temp;
	char	*temp2;

	if (!d_name) //if no directory name -> NULL
	{
		if (d_or_f_name[0] == '~' || d_or_f_name[0] == '/' || d_or_f_name[0] == '.') // the ~ is for user home directory and / is for root dir and . is current dir
			return (ft_strdup(d_or_f_name));
		return (ft_strjoin("./", d_or_f_name));
	}
	temp = ft_strjoin(d_or_f_name, "/");
	temp2 = ft_strjoin(temp, d_name);
	free(temp);
	return (temp2);
}

static void		perror_free(t_pathinfo **temp)
{
	ft_putstr("ls: ");
	perror((*temp)->fullpath);
	free((*temp)->pathname);
	free((*temp)->fullpath);
	free(*temp);
}

int			add_tolist(char *d_or_f_name, t_pathinfo **direntry_l, struct dirent *entry)
{
	t_pathinfo	*temp;

	if (!(temp = malloc(sizeof(t_pathinfo))))
		return (-1);
	if (check_dir(d_or_f_name))
	{
		temp->is_dir = 1;
		temp->pathname = ft_strdup(entry->d_name);
		temp->fullpath = correct_path(d_or_f_name, entry->d_name);
	}
	else
	{
		temp->is_dir = 0;
		temp->pathname = ft_strdup(d_or_f_name);
		temp->fullpath = correct_path(d_or_f_name, NULL);
	}
	if (lstat(temp->fullpath, &(temp->statinfo)) == -1) //used lstat over stat to differentiate files vs symbolic links
	{
		perror_free(&temp);
		return (0);
	}
	temp->next = *direntry_l;
	*direntry_l = temp;
	return (temp->statinfo.st_blocks); //The actual number of blocks allocated for the file in 512-byte units or 0 for symbolic links
}