/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 09:39:29 by kmorulan          #+#    #+#             */
/*   Updated: 2019/09/14 09:37:43 by kmorulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int					check_dir(char *path)
{
	struct stat		temp;

	if (stat(path, &temp) != 0)
	{
		return (0);
	}
	else if ((temp.st_mode & 0170000) == 0040000)
	{
		return (1);
	}
	return (0);
}

static void			print_access_error(char *path, t_flag *flags)
{
	check_dir(path) && flags->cap_r ? ft_putendl(path) : 0;
	ft_putstr("ls: ");
	if (flags->cap_r)
		while (*path && (*path == '/' || *path == '.'))
		{
			path++;
		}
	ft_putstr(path);
	ft_putstr(": ");
	ft_putendl(strerror(errno));
}

int					validate_path(char *path, t_flag *flags, \
t_pathinfo **direntry_l)
{
	DIR				*dp;

	errno = 0;
	if (!(dp = opendir(path)))
	{
		if ((!dp) && errno != 0)
		{
			if (errno == ENOENT)
			{
				ft_putstr("ls: ");
				ft_putstr(path);
				ft_putstr(": ");
				ft_putendl(strerror(errno));
			}
			else if (errno == EACCES)
				print_access_error(path, flags);
			else
				add_tolist(path, direntry_l, NULL);
		}
		return (-1);
	}
	closedir(dp);
	return (0);
}
