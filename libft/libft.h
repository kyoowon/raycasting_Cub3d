/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyuwonlee <kyuwonlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 19:34:33 by kyulee            #+#    #+#             */
/*   Updated: 2021/05/26 18:23:27 by kyuwonlee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdarg.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

# ifndef OPEN_MAX
#  define OPEN_MAX 256
# endif

typedef struct	s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

typedef struct	s_option
{
	char		type;
	int			width;
	int			prec;
	int			zero;
	int			left;
	int			sign;
	int			baseset;
	int			len;
	int			plus;
	int			space;
	int			hexa;

}				t_option;

/*
** part 1 function
*/

int				ft_atoi(const char *nptr);
void			ft_bzero(void *str, size_t num);
void			*ft_calloc(size_t nmenb, size_t size);
int				ft_isalnum(int c);
int				ft_isalpha(int c);
int				ft_isascii(int c);
int				ft_isdigit(int c);
int				ft_isprint(int c);
void			*ft_memccpy(void *dest, const void *src, int c, size_t num);
void			*ft_memchr(const void *str, int c, size_t num);
int				ft_memcmp(const void *s1, const void *s2, size_t num);
void			*ft_memcpy(void *dest, const void *src, size_t num);
void			*ft_memmove(void *dest, const void *src, size_t num);
void			*ft_memset(void *str, int value, size_t num);
char			*ft_strchr(const char *str, int c);
char			*ft_strdup(const char *str);
size_t			ft_strlcat(char *dest, const char *src, size_t size);
size_t			ft_strlcpy(char *dest, const char *src, size_t size);
int				ft_strlen(const char *str);
int				ft_strncmp(const char *s1, const char *s2, size_t num);
char			*ft_strnstr(const char *str, const char *to_find, size_t len);
char			*ft_strrchr(const char *str, int c);
int				ft_tolower(int c);
int				ft_toupper(int c);
int				ft_isset(char c, char *set);

/*
** part 2 function
*/

char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strjoin_one(char *s1, char *s2);
char			*ft_strjoin_two(char *s1, char *s2);
char			*ft_strtrim(char const *s1, char const *set);
char			**ft_split(char const *s, char c);
size_t			ft_nbr_len(int nbr);
char			*ft_itoa(int nbr);
char			*ft_strmapi(char const *str, char (*f)(unsigned int, char));
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
int				ft_strcmp(const char *s1, const char *s2);

/*
** bouns function - linked list
*/

t_list			*ft_lstnew(void *content);
void			ft_lstadd_front(t_list **lst, t_list *new);
int				ft_lstsize(t_list *lst);
int				ft_lstlongestsize(t_list *lst);
t_list			*ft_lstlast(t_list *lst);
void			ft_lstadd_back(t_list **lst, t_list *new);
void			ft_lstdelone(t_list *lst, void (*del)(void*));
void			ft_lstclear(t_list **lst, void (*del)(void*));
void			ft_lstiter(t_list *lst, void (*f)(void*));
t_list			*ft_lstmap(t_list *lst, void *(*f)(void*), void (*del)(void*));

/*
** get_next_line
*/

int				get_next_line(int fd, char **line);
char			*ft_gnl_strjoin(char const *s1, char const *s2);
int				return_lines(char **backup, char **line, char *point);
void			backup_free(char **backup, char *tmp);

/*
** ft_print_nbr_util.c
*/

char			*ft_trans_baseset(t_option *tp);
void			ft_front_sign(char **result, t_option *tp);
void			ft_rear_sign(char **result, t_option *tp);
void			ft_fronthexa_set(char **result, t_option *tp);
void			ft_rearhexa_set(char **result, t_option *tp);

/*
** ft_print_nbr.c
*/

int				ft_printf_nbr_len(long long nbr, t_option *tp);
char			*ft_nbr_itoa(char **ret, unsigned long long nbr, t_option *tp);
int				ft_check_prec(int nbr_len, t_option *tp);
int				ft_signed_nbr(long long nbr, t_option *tp);
int				ft_unsigned_nbr(unsigned long long nbr, t_option *tp);

/*
** ft_print_str.c
*/

int				ft_print_char(int c, t_option *tp);
char			*ft_str_prec(char **result, char *str, t_option *tp);
int				ft_print_str(char *str, t_option *tp);
char			*ft_put_width_str(char **nbrp, t_option *tp, int nbr_len);

/*
** ft_print_util.c
*/

int				ft_putchar(char c);
int				ft_putstr(char *str);
char			ft_issetzero(t_option *tp);
void			ft_init(t_option *tp);
int				ft_frontflag_len(t_option *tp);

/*
** ft_printf.c
*/

void			ft_print_specifier(va_list ap, t_option *tp);
void			ft_width_precision(va_list ap, t_option *tp, char *fmt);
char			*ft_parsing_format(va_list ap, t_option *tp, char *format);
int				ft_printf(const char *format, ...);

/*
** cub3d.c
*/

void			ft_strexit(char *str);
int				ft_isformat(char *str, char *format);
int				ft_alldigit(char *str);
void			ft_frees(char **str);
void			ft_frees_nbr(int **nbr);

#endif
