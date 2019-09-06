/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorulan <kmorulan@student.wethinkcode.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 10:53:12 by kmorulan          #+#    #+#             */
/*   Updated: 2019/09/06 13:21:08 by kmorulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int			ft_ls(char *path)
{
	char			*path_name;
	DIR 			*dp;
	struct dirent	*entry;
	char			c;

	c = '\\';
	path_name = ft_strjoin(path, &c);
	ft_putstr("Directory scan of : ");
	ft_putendl(path_name);
	dp = opendir(path);
	errno = 0;
	while (1)
	{
		entry = readdir(dp);
		if (entry == NULL &&  errno != 0)
		{
			perror("readdir");
			return (errno);
		}
		if (entry == NULL && errno == 0)
		{
			ft_putendl("End of directory");
			return (0);
		}
		ft_putendl(entry->d_name);
	}
	closedir(dp);
}