/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract_ol.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 15:33:31 by vrichese          #+#    #+#             */
/*   Updated: 2019/07/16 21:04:18 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACT_OL_H
# define FRACT_OL_H

# include "ft_printf.h"
# include "get_next_line.h"
# include "libft.h"
# include <mlx.h>

/*
**	In honor of the great mathematician who discovered the world of fractals
**	i've named my struct by his name(Benoit Mandelbrot)
*/

typedef struct		s_window
{
	unsigned int	width;
	unsigned int	height;
}					t_window;

typedef struct		s_benoit
{
	void			*window;
	void			*pixels;
	void			*connect;
	void			*picture;
	t_window		win;
}					t_benoit;

#endif