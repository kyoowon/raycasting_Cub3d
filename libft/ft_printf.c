/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyuwonlee <kyuwonlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 01:39:02 by kyulee            #+#    #+#             */
/*   Updated: 2021/05/17 18:57:11 by kyuwonlee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** what is cspdiuxX%
** %c : character
** %s : string
** %p : pointer address
** %d : signed decimal integer
** %i : signed decimal integer
** %u : unsigned decimal integer
** %x : unsigned Hex integer (lowercase)
** %X : unsigned Hex integer (uppercase)
** %% : print % character
*/

void		ft_print_specifier(va_list ap, t_option *tp)
{
	if (tp->type == 'c')
		tp->len = ft_print_char(va_arg(ap, int), tp);
	else if (tp->type == 's')
		tp->len = ft_print_str(va_arg(ap, char *), tp);
	else if (tp->type == 'p')
		tp->len = ft_unsigned_nbr(va_arg(ap, unsigned long long), tp);
	else if (tp->type == 'd' || tp->type == 'i')
		tp->len = ft_signed_nbr(va_arg(ap, int), tp);
	else if (tp->type == 'x' || tp->type == 'X')
		tp->len = ft_unsigned_nbr(va_arg(ap, unsigned int), tp);
	else if (tp->type == 'u' || tp->type == 'o')
		tp->len = ft_unsigned_nbr(va_arg(ap, unsigned int), tp);
	else if (tp->type == '%')
		tp->len = ft_print_char('%', tp);
}

void		ft_width_precision(va_list ap, t_option *tp, char *fmt)
{
	if (*fmt == '*')
	{
		if (tp->prec == -1)
		{
			tp->width = va_arg(ap, int);
			if (tp->width < 0)
			{
				tp->width *= -1;
				tp->left = 1;
			}
		}
		else
			tp->prec = va_arg(ap, int);
	}
	else if (ft_isdigit(*fmt))
	{
		if (tp->prec == -1)
			tp->width = tp->width * 10 + *fmt - '0';
		else
			tp->prec = tp->prec * 10 + *fmt - '0';
	}
}

char		*ft_parsing_format(va_list ap, t_option *tp, char *fmt)
{
	while (*fmt != '\0' && !(ft_strchr("cspdiuoxX%", *fmt)))
	{
		if (*fmt == '-')
			tp->left = 1;
		else if (*fmt == '0' && tp->width == 0 && tp->prec == -1)
			tp->zero = 1;
		else if (*fmt == '.')
			tp->prec = 0;
		else if (*fmt == '+')
			tp->plus = 1;
		else if (*fmt == '#')
			tp->hexa = 1;
		else if (*fmt == ' ')
			tp->space = 1;
		else if (*fmt == '*' || ft_isdigit(*fmt))
			ft_width_precision(ap, tp, fmt);
		fmt++;
	}
	tp->type = *fmt;
	ft_print_specifier(ap, tp);
	return (fmt);
}

int			ft_printf(const char *format, ...)
{
	va_list		ap;
	t_option	*tp;
	int			printed_len;

	printed_len = 0;
	va_start(ap, format);
	while (*format != '\0')
	{
		if (*format != '%')
			printed_len += ft_putchar(*format);
		else if (*format == '%' && *(++format) != '\0')
		{
			if (!(tp = (t_option *)malloc(sizeof(t_option))))
				return (-1);
			ft_init(tp);
			format = ft_parsing_format(ap, tp, (char *)format);
			printed_len += tp->len;
			free(tp);
		}
		if (*format != '\0')
			format++;
	}
	va_end(ap);
	return (printed_len);
}
