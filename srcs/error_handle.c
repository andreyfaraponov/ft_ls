/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarapon <afarapon@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 23:55:43 by afarapon          #+#    #+#             */
/*   Updated: 2018/04/01 01:01:10 by afarapon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void			print_errors(char *errors)
{
	if (ft_strlen(errors))
		ft_putstr_fd(errors, 2);
	free(errors);
}

void			make_error(char *e_name, t_localinfo *l)
{
	char		*tmp;

	tmp = l->errors;
	l->errors = ft_strjoin(l->errors, "ft_ls: cannot access '");
	free(tmp);
	tmp = l->errors;
	l->errors = ft_strjoin(l->errors, e_name);
	free(tmp);
	tmp = l->errors;
	l->errors = ft_strjoin(l->errors, "': No such file or firectory\n");
	free(tmp);
}

int				make_permission_error(char *e_name)
{
	ft_putstr_fd("ft_ls: cannot open directory '", 2);
	ft_putstr_fd(e_name, 2);
	ft_putstr_fd("': Permission denied\n", 2);
	return (1);
}

int				make_link_error(char *name)
{
	ft_putstr_fd("ft_ls: cannot read symbolic link '", 2);
	ft_putstr_fd(name, 2);
	ft_putstr_fd("': Permission denied\n", 2);
	return (1);
}
