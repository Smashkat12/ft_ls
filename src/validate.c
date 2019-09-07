/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorulan <kmorulan@student.wethinkcode.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 09:39:29 by kmorulan          #+#    #+#             */
/*   Updated: 2019/09/07 12:05:27 by kmorulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int			validate_path(pathinfo_t **pathinfo_l, char *path, flag_t *flags)
{
	DIR		*dp;
	char	message[3000];

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
				strerror(errno);
			}
			else if (errno == EACCES) //this value is 13, see above reference,it means Permission denied
			{
				if (flags->R && )
				{

				}
			}
		}
		
	}
}