/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorulan <kmorulan@student.wethinkcode.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 10:53:12 by kmorulan          #+#    #+#             */
/*   Updated: 2019/09/10 10:58:37 by kmorulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int				ft_ls(char *path, t_flag *flags)
{
	//char			*path_name;
	DIR 			*dp;
	struct dirent	*entry;
	t_pathinfo		*direntry_l;
	int				total;

	dp = NULL;
	direntry_l = NULL;
	if ((validate_path(path, flags, &direntry_l)) != 0 )
	{
		return (0);
	}
	/*path_name = ft_strjoin(path, "/");
	ft_putstr("Directory scan of : ");
	ft_putendl(path_name);*/
	dp = opendir(path);
	errno = 0;
	while ((entry = readdir(dp)) != NULL)
	{
		if (entry->d_name[0] == '.')
			continue;
		ft_putendl(entry->d_name);
	}
	total = creat_dirent_list(&direntry_l, path, flags);
	sort_list(&direntry_l, flags);
	ft_putchar('\n');
	ft_putstr("Total :");
	ft_putnbr(total);
	ft_putchar('\n');
	/*if (entry == NULL && errno == 0)
	{
		ft_putendl("End of directory");
	}*/
	closedir(dp);
	return (0);
}