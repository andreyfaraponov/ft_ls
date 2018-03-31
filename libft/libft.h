/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarapon <afarapon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 16:20:21 by afarapon          #+#    #+#             */
/*   Updated: 2018/01/24 19:27:50 by afarapon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef H_LIBFT_H
# define H_LIBFT_H
# define FT_PRINTF_LIBFTPRINTF_H
# define ABS(x) x < 0 ? (-(x)) : x
# define M1_ONE(chr) (unsigned char)(((chr << 21) >> 27) | 192)
# define M1_TWO(chr) (unsigned char)(((chr << 26) >> 26) | 128)
# define M2_ONE(chr) (unsigned char)(((chr << 12) >> 24) | 224)
# define M2_TWO(chr) (unsigned char)(((chr << 20) >> 26) | 128)
# define M3_ONE(chr) (unsigned char)(((chr << 11) >> 29) | 240)
# define M3_TWO(chr) (unsigned char)(((chr << 14) >> 26) | 128)
# define BUFF_SIZE 1024
# include <stdarg.h>
# include <limits.h>
# include <inttypes.h>
# include <locale.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>

void				*ft_memset(void *s, int c, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memccpy(void *dst,
	const void *src, int c, size_t n);
void				ft_bzero(void *s, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
size_t				ft_strlen(const char *s);
char				*ft_strdup(const char *str);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strncpy(char *dest, const char *src, size_t n);
char				*ft_strcat(char *dest, const char *src);
char				*ft_strncat(char *dest, const char *src, size_t n);
size_t				ft_strlcat(char *dest, const char *src, size_t n);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strstr(const char *where, const char *what);
char				*ft_strnstr(const char *where, const char *what, size_t n);
int					ft_atoi(char *str);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
int					ft_strncmp(char *s1, char *s2, size_t n);
int					ft_strcmp(char *s1, char *s2);
void				*ft_memalloc(size_t n);
void				ft_memdel(void **ap);
char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, char c);
char				*ft_itoa(int n);
void				ft_putchar(char c);
void				ft_putstr(char const *s);
void				ft_putendl(char const *s);
void				ft_putnbr(int n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstadd(t_list **alst, t_list *n);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));

char				*ft_strrev(char *str);
void				ft_sortints(int *src, size_t n,
	int (*sort)(int el1, int el2));
size_t				ft_strlcpy(char *dest, const char *src, size_t n);
void				ft_foreach(int *tab, size_t length, void (*f)(int));
void				ft_swap(int *a, int *b);
int					ft_isalphanum(const char *str);
int					ft_sqrt(int num);
int					ft_pow(int n, unsigned int q);

/*
**	GET NEXT LINE
*/

int					get_next_line(const int fd, char **line);

typedef struct		s_reader
{
	char			*buf;
	int				fd;
	struct s_reader	*next;
}					t_reader;

/*
**	FT_PRINTF
*/

typedef struct		s_all_flags
{
	char			f_sharp;
	char			f_zero;
	char			f_minus;
	char			f_plus;
	char			f_space;
	int				currency;
	int				dot;
	int				width;
	char			hh;
	char			h;
	char			l;
	char			ll;
	char			j;
	char			z;
	char			large;
}					t_all_flags;

int					ft_printf(const char *zzz, ...);
void				ft_all_flags_init(t_all_flags *flags);
void				ft_get_flags(char **f, t_all_flags *all_flags);
int					ft_get_number(char **f, int sign);
void				ft_get_size(char **f, t_all_flags *all_flags);
int					ft_main_print(char **f, t_all_flags flags, va_list list,
	int *r);
char				*ft_print_nums(char **f,
	t_all_flags all_flags, va_list list);
char				*ft_get_int(t_all_flags all, va_list list);
char				*ft_get_unsigned_any(char **f,
	t_all_flags all, va_list list);
char				*ft_get_unsigned(t_all_flags all, va_list list);
char				*ft_itoa_base(uintmax_t num, char system, t_all_flags all);
char				*ft_get_lint(t_all_flags all, va_list list);
char				*ft_numstr_make(char *src,
	t_all_flags all, int min, char s);
char				ft_get_sign(t_all_flags all, int isneg);
char				*ft_get_hex(t_all_flags all, va_list list, char system);
char				*ft_get_hex_any(char **f, t_all_flags all, va_list list,
	char system);
char				*ft_hex_make(char *src, t_all_flags all, int cmp_result);
char				*ft_get_oct(t_all_flags all, va_list list, char system);
char				*ft_get_oct_any(char **f, t_all_flags all, va_list list,
	char system);
char				*ft_oct_make(char *src, t_all_flags all);
char				*ft_get_oct_sign(t_all_flags all);
char				*ft_get_hex_sign(t_all_flags all);
char				*ft_print_strings(char **f, t_all_flags all_flags,
	va_list list);
char				*ft_make_width_str(char *src, t_all_flags all, char f);
int					ft_print_characters(char **f, t_all_flags all_flags,
	va_list list);
char				*ft_make_width_char(char *src, t_all_flags all);
char				*ft_print_memory(char **f,
	t_all_flags all_flags, va_list list);
int					ft_size_flags_null(t_all_flags *all_flags);
char				*ft_print_percent(char **f, t_all_flags flags);
char				*ft_make_width(char *src, t_all_flags all);
t_all_flags			ft_if_dot(char **src,
	t_all_flags all, char *sign, int isneg);
int					ft_print_u_characters(char **f,
	t_all_flags all_flags, va_list list);
char				*ft_putsign(char *src,
	char sign, t_all_flags all, int isneg);
char				*ft_make_precision(char *src, t_all_flags all);
int					ft_max_bit_size(unsigned int n);
char				*ft_create_ustring(unsigned int *arr, char *src,
	t_all_flags *all);
int					ft_print_null(char chr, t_all_flags all_flags);
int					ft_calcandprint(char **f, va_list list);

#endif
