/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 15:34:33 by vrichese          #+#    #+#             */
/*   Updated: 2019/07/16 21:01:32 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"

t_benoit		*benoit_mandelbrot_init(int argc, char **argv)
{
	t_benoit	*benoit_mandelbrot;

	if (!(benoit_mandelbrot = (t_benoit *)malloc(sizeof(t_benoit))));
		error_handler(MEMORY_ALLOC_ERROR);
	benoit_mandelbrot->win.width = 1920;
	benoit_mandelbrot->win.height = 1080;
}

int				main(int argc, char **argv)
{
	t_benoit	*benoit_mandelbrot;

	if (argc != 2)
		error_handler(ARGS_NUMBER_ERROR);
	if (!(benoit_mandelbrot = benoit_mandelbrot_init(argc, argv)))
		error_handler(BENOIT_MANDELBROT_VARIABLE_INIT_ERROR);
	if (!(benoit_mandelbrot->connect = mlx_init()))
		error_handler(CONNECT_ERROR);
	if (!(benoit_mandelbrot->window = mlx_create_window(benoit_mandelbrot->connect, benoit_mandelbrot->win.width, benoit_mandelbrot->win.height, argv[1])))
		error_handler(WINDOW_ERROR);
	if (!(benoit_mandelbrot->image = mlx_new_image(benoit_mandelbrot->connect, benoit_mandelbrot->win.width, benoit_mandelbrot->win.height)))
		error_handler(IMAGE_ERROR);
	ft_printf("It is first steps in fractal geometric\n");
	return (0);
}
