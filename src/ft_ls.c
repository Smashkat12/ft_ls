/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorulan <kmorulan@student.wethinkcode.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 10:53:12 by kmorulan          #+#    #+#             */
/*   Updated: 2019/09/07 09:28:42 by kmorulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"
#include <stdio.h>

int				ft_ls(char *path, flag_t *flags)
{
	char			*path_name;
	DIR 			*dp;
	struct dirent	*entry;
	pathinfo_t		*pathinfo_l;


	if (validate_path(&pathinfo_l, path, flags))
	path_name = ft_strjoin(path, "/");
	ft_putstr("Directory scan of : ");
	ft_putendl(path_name);
	if (!(dp = opendir(path)) == NULL)
	{
		ft_putstr("Cannot open directory: ");
		ft_putendl(path_name);
		return (errno);
	}
	errno = 0;
	while ((entry = readdir(dp)) != NULL)
	{
		if (entry->d_name[0] == '.')
			continue;
		ft_putendl(entry->d_name);
	}
	if (entry == NULL &&  errno != 0)
	{
		perror("readdir Failed");
		closedir(dp);
		return (errno);
	}
	else if (entry == NULL && errno == 0)
	{
		ft_putendl("End of directory");
	}
	closedir(dp);
	return (0);
}