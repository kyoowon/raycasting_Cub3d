/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyuwonlee <kyuwonlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 00:29:51 by kyulee            #+#    #+#             */
/*   Updated: 2021/05/17 17:52:31 by kyuwonlee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdio.h>
# include "libft.h"

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

int				ft_nbr_len(long long nbr, t_option *tp);
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
** printf.c
*/

void			ft_print_specifier(va_list ap, t_option *tp);
void			ft_width_precision(va_list ap, t_option *tp, char *fmt);
char			*ft_parsing_format(va_list ap, t_option *tp, char *format);
int				ft_printf(const char *format, ...);

void			ft_strexit(char *str);


#endif
