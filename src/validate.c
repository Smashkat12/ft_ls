/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 09:39:29 by kmorulan          #+#    #+#             */
/*   Updated: 2019/09/13 18:20:34 by kmorulan         ###   ########.fr       */
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
		return(1);
	}
	return (0);
}

int					validate_path(char *path, t_flag *flags, t_pathinfo **direntry_l )
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
			else if (errno == EACCES) //this value is 13, see above reference,it means Permission denied
			{
				check_dir(path) && flags->R ? ft_putendl(path) : 0;
				ft_putstr("ls: ");
				if (flags->R)
					while (*path && (*path == '/' || *path == '.'))
					{
						path++;
					}
				ft_putstr(path);
				ft_putstr(": ");
				ft_putendl(strerror(errno));
			}
			else //it is some type of file that exist and not a dir so save it for later display
			{
				add_tolist(path, direntry_l , NULL);
			}
		}
		return (-1);
	}
	closedir(dp);
	return (0);
}
