/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorulan <kmorulan@student.wethinkcode.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 10:53:12 by kmorulan          #+#    #+#             */
/*   Updated: 2019/09/06 16:44:08 by kmorulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"
#include <stdio.h>

int				ft_ls(char *path)
{
	char			*path_name;
	DIR 			*dp;
	struct dirent	*entry;
	char			c;

	c = '\\';
	path_name = ft_strjoin(path, &c);
	ft_putstr("Directory scan of : ");
	ft_putendl(path_name);
	if ((dp = opendir(path)) == NULL)
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