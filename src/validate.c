/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorulan <kmorulan@student.wethinkcode.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 09:39:29 by kmorulan          #+#    #+#             */
/*   Updated: 2019/09/08 09:01:04 by kmorulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int				check_dir(char *path)
{
	struct stat	temp;

	if (stat(path, &temp) != 0)
	{
		return (0);
	}
	else if ((temp.st_mode & 0170000) == 0040000) // same as S_ISDIR(temp.st_mode)
	{
		return(1);
	}
	return (0);
}

int				validate_path(char *path, flag_t *flags, pathinfo_t **pathentry_l)
{
	DIR			*dp;

	errno = 0;
	if (!(dp = opendir(path)))
	{
		if ((!dp) && errno != 0)
		{	
			if (errno == ENOENT)  // this value is 2. see list of error https://www-numi.fnal.gov/offline_software/srt_public_context/WebDocs/Errors/unix_system_errors.html
			//ENOENT means no such file or directory
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
			else //it is some type of file that exist and not a dir so save it for late display
			{
				addf_tolist(path, pathentry_l);
			}
			
		}
		return (-1);
	}
	closedir(dp);
	return (0);
}