/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-l <dlopez-l@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 19:09:24 by dlopez-l          #+#    #+#             */
/*   Updated: 2024/11/03 09:20:10 by dlopez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <unistd.h>
# include "libft.h"
# define ERROR	-1

int		ft_printf(char const *format, ...);
int		ft_print_string(char *str);
int		ft_print_nbr_dec(int nbr);
int		ft_print_unsigned(unsigned int nbr);
int		ft_print_hex(size_t arg, int caps);
int		ft_print_ptr(size_t ptr);

#endif