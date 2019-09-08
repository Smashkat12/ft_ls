/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_entry_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorulan <kmorulan@student.wethinkcode.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 09:44:48 by kmorulan          #+#    #+#             */
/*   Updated: 2019/09/08 10:14:40 by kmorulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int			addf_tolist(char *filename, pathinfo_t **pathentry_l)
{
	pathinfo_t	*temp;

	if (!(temp = malloc(sizeof(pathinfo_t))))
	{
		return (-1);
	}
	temp->pathname = ft_strdup(filename);
	temp->fullpath = ft_strdup(filename);
	if (lstat(temp->fullpath, &(temp->statinfo)) == -1) //used lstat over stat to differentiate files vs symbolic links
	{
		ft_putstr("ls: ");
		perror(temp->fullpath);
		free(temp->pathname);
		free(temp->fullpath);
		free(temp);
		return (0);
	}
	temp->IS_DIR = 0;
	temp->next = *pathentry_l;
	*pathentry_l = temp;
	return (temp->statinfo->st_blocks); //The actual number of blocks allocated for the file in 512-byte units or 0 for symbolic links
}