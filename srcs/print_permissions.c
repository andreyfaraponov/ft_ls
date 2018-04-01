/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_permissions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarapon <afarapon@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/02 00:28:03 by afarapon          #+#    #+#             */
/*   Updated: 2018/04/02 00:30:56 by afarapon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static void			print_file_l_letter(struct stat s)
{
	if (S_ISLNK(s.st_mode))
		ft_printf("%s", "l");
	else if (S_ISDIR(s.st_mode))
		ft_printf("%s", "d");
	else if (S_ISCHR(s.st_mode))
		ft_printf("%s", "c");
	else if (S_ISBLK(s.st_mode))
		ft_printf("%s", "b");
	else if (S_ISFIFO(s.st_mode))
		ft_printf("%s", "p");
	else if (S_ISSOCK(s.st_mode))
		ft_printf("%s", "s");
	else
		ft_printf("%s", "-");
}

static void			print_user_x(STAT s)
{
	mode_t			st_mode;

	st_mode = s.st_mode;
	if (st_mode & S_IRWXU && st_mode & S_ISUID)
	{
		if (st_mode & S_ISUID && st_mode & S_IXUSR)
			ft_printf("s");
		else if (st_mode & S_ISUID && !(st_mode & S_IXUSR))
			ft_printf("S");
		else
			ft_printf("x");
	}
	else
	{
		if (st_mode & S_IXUSR)
			ft_printf("x");
		else if (st_mode & S_ISUID && st_mode & S_IXUSR)
			ft_printf("s");
		else if (st_mode & S_ISUID && !(st_mode & S_IXUSR))
			ft_printf("S");
		else
			ft_printf("-");
	}
}

static void			print_group_x(STAT s)
{
	mode_t			st_mode;

	st_mode = s.st_mode;
	if (st_mode & S_IRWXG && st_mode & S_ISGID)
	{
		if (st_mode & S_ISGID && st_mode & S_IXGRP)
			ft_printf("s");
		else if (st_mode & S_ISGID && !(st_mode & S_IXGRP))
			ft_printf("S");
		else
			ft_printf("x");
	}
	else
	{
		if (st_mode & S_IXGRP)
			ft_printf("x");
		else if (st_mode & S_ISGID && st_mode & S_IXGRP)
			ft_printf("s");
		else if (st_mode & S_ISGID && !(st_mode & S_IXGRP))
			ft_printf("S");
		else
			ft_printf("-");
	}
}

static void			print_other_x(STAT s)
{
	mode_t			st_mode;

	st_mode = s.st_mode;
	if (st_mode & S_IRWXO && st_mode & S_ISVTX)
	{
		if (st_mode & S_ISVTX && st_mode & S_IXOTH)
			ft_printf("t");
		else if (st_mode & S_ISVTX && !(st_mode & S_IXOTH))
			ft_printf("T");
		else
			ft_printf("x");
	}
	else
	{
		if (st_mode & S_IXOTH)
			ft_printf("x");
		else if (st_mode & S_ISVTX && st_mode & S_IXOTH)
			ft_printf("t");
		else if (st_mode & S_ISVTX && !(st_mode & S_IXOTH))
			ft_printf("T");
		else
			ft_printf("-");
	}
}

void				print_permissions(STAT s)
{
	print_file_l_letter(s);
	ft_printf("%s", s.st_mode & S_IRUSR ? "r" : "-");
	ft_printf("%s", s.st_mode & S_IWUSR ? "w" : "-");
	print_user_x(s);
	ft_printf("%s", s.st_mode & S_IRGRP ? "r" : "-");
	ft_printf("%s", s.st_mode & S_IWGRP ? "w" : "-");
	print_group_x(s);
	ft_printf("%s", s.st_mode & S_IROTH ? "r" : "-");
	ft_printf("%s", s.st_mode & S_IWOTH ? "w" : "-");
	print_other_x(s);
}
