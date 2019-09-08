/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorulan <kmorulan@student.wethinkcode.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 10:53:12 by kmorulan          #+#    #+#             */
/*   Updated: 2019/09/08 08:58:53 by kmorulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int				ft_ls(char *path, flag_t *flags)
{
	char			*path_name;
	DIR 			*dp;
	struct dirent	*entry;
	pathinfo_t		*pathentry_l;

	dp = NULL;
	if ((validate_path(path, flags, &pathentry_l)) != 0 )
	{
		return (0);
	}
	path_name = ft_strjoin(path, "/");
	ft_putstr("Directory scan of : ");
	ft_putendl(path_name);
	dp = opendir(path);
	errno = 0;
	while ((entry = readdir(dp)) != NULL)
	{
		if (entry->d_name[0] == '.')
			continue;
		ft_putendl(entry->d_name);
	}
	if (entry == NULL && errno == 0)
	{
		ft_putendl("End of directory");
	}
	closedir(dp);
	return (0);
}