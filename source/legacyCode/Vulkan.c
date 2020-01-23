/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vulkan.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 18:16:20 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/03 18:39:11 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "/usr/local/include/vulkan/vulkan.h"
#include "../include/fract_ol.h"

int				key_press(int key_press, benoit_t *benoit)
{
	if (key_press == 53)
		mlx_destroy_window(benoit->connect, benoit->window);
	if (key_press == 126)
		benoit->keys[126] = 1;
	if (key_press == 125)
		benoit->keys[125] = 1;
	if (key_press == 123)
		benoit->keys[123] = 1;
	if (key_press == 124)
		benoit->keys[124] = 1;
	if (key_press == 69)
		benoit->max_iter += 10;
	if (key_press == 78)
		benoit->max_iter -= 10;
	if (key_press == 24)
		benoit->test++;
	if (key_press == 27)
		benoit->test--;
	if (key_press == 83)
	{
		benoit->start_color = 0x20b2aa;
		benoit->finish_color = 0xadff2f;
	}
	if (key_press == 84 && (benoit->start_color = 0xd2691e))
		benoit->finish_color = 0xdcdcdc;
	if (key_press == 85 && (benoit->start_color = 0x8b8b))
		benoit->finish_color = 0x8b008b;
	if (key_press == 86 && (benoit->start_color = 0x8b8b00))
		benoit->finish_color = 0xff7256;
	if (key_press == 87 && (benoit->start_color = 0x8b864e))
		benoit->finish_color = 0xff3030;
	do_something(benoit);
	return (0);
}

int				key_release(int key_press, benoit_t *benoit)
{
	if (key_press == 126)
		benoit->keys[126] = 0;
	if (key_press == 125)
		benoit->keys[125] = 0;
	if (key_press == 123)
		benoit->keys[123] = 0;
	if (key_press == 124)
		benoit->keys[124] = 0;
	do_something(benoit);
	return (0);
}

int				mouse_press(int button, int x, int y, benoit_t *benoit)
{
	if (button == 4)
	{
		benoit->zoom *= 1.1;
		if (benoit->max_iter < 1000)
			benoit->max_iter += 7;
		benoit->y -= benoit->y1;
		benoit->x -= benoit->x1;
	}
	if (button == 3)
	{
		benoit->keys[3] = 1;
	}
	if (button == 5)
	{
		benoit->zoom *= 0.9;
		if (benoit->max_iter > 30)
			benoit->max_iter -= 3;
		benoit->y += benoit->y1;
		benoit->x += benoit->x1;
	}
	do_something(benoit);
	return (0);
}

int				mouse_release(int button, int x, int y, benoit_t *benoit)
{
	if (button == 3)
		benoit->keys[3] = 0;
	return (0);
}

int				mouse_move(int x, int y, benoit_t *benoit)
{
	double test1;
	double test2;
	double one;
	double hello1;
	double hello2;

	one = benoit->win.width / 2;
	test1 = x - one;
	one = benoit->win.height / 2;
	test2 = y - one;
	benoit->x1 = test1 / (double)benoit->win.width * 2 / benoit->zoom * 50.0f;
	benoit->y1 = test2 / (double)benoit->win.height * 2 / benoit->zoom * 50.0f;
	if (benoit->keys[3])
	{
		hello1 = (x - benoit->hello1) / benoit->zoom;
		hello2 = (y - benoit->hello2) / benoit->zoom;
		benoit->x += hello1;
		benoit->y += hello2;
		benoit->hello1 = x;
		benoit->hello2 = y;
		display_pixels(benoit);
	}
	return (0);
}

int				expose(benoit_t *benoit)
{
	display_pixels(benoit);
	return (0);
}

int				close_window(benoit_t *benoit)
{
	return (0);
}

void			do_something(benoit_t *benoit)
{
	if (benoit->keys[126])
		benoit->y += 10.0f / benoit->zoom;
	if (benoit->keys[125])
		benoit->y -= 10.0f / benoit->zoom;
	if (benoit->keys[123])
		benoit->x += 10.0f / benoit->zoom;
	if (benoit->keys[124])
		benoit->x -= 10.0f / benoit->zoom;
}

void			bind_handlers(benoit_t *benoit)
{
	mlx_hook(benoit->window,  2, 0, key_press,		benoit);
	mlx_hook(benoit->window,  3, 0, key_release,    benoit);
	mlx_hook(benoit->window,  4, 0, mouse_press,	benoit);
	mlx_hook(benoit->window,  5, 0, mouse_release,	benoit);
	mlx_hook(benoit->window,  6, 0, mouse_move,		benoit);
	mlx_hook(benoit->window, 12, 0, expose,			benoit);
	mlx_hook(benoit->window, 17, 0, close_window,	benoit);
}

void			frErrorHandler(int code_error)
{
	if (code_error == IMAGE_ERROR)
		ft_printf("The image object has not been created, emeregency exit...\n");
	else if (code_error == WINDOW_ERROR)
		ft_printf("The window has not been create, emeregency exit...\n");
	else if (code_error == CONNECT_ERROR)
		ft_printf("Connect has not been established, emeregncy exti...\n");
	else if (code_error == ARGS_NUMBER_ERROR)
		ft_printf("Numbers of args is wrong, try again\n");
	else if (code_error == MEMORY_ALLOC_ERROR)
		ft_printf("Memory has not been allocated, emeregency exit...\n");
	else if (code_error == BENOIT_VARIABLE_INIT_ERROR)
		ft_printf("Main varibale has not been initialized, emeregency exit...\n");
	else if (code_error == BUFFER_ERROR)
		ft_printf("Pixel buffer has not been created, emergency exit...\n");
	exit(1);
}

void		frVulkanInit(benoit_t *benoit)
{

}

void		frBenoitInit(int argc, char **argv, benoit_t **benoit)
{
	if (!(*benoit = (benoit_t *)malloc(sizeof(benoit_t))))
		error_handler(MEMORY_ALLOC_ERROR);
	(*benoit)->start_color = 0x8b8b;
	(*benoit)->finish_color = 0x8b008b;
	(*benoit)->win.width = 2560;
	(*benoit)->win.height = 1440;
	(*benoit)->max_iter = 30;
	(*benoit)->x = 0.0f;
	(*benoit)->y = 0.0f;
	(*benoit)->zoom = 300.0f;
	(*benoit)->test = 2;
	(*benoit)->hello1 = (*benoit)->win.width / 2;
	(*benoit)->hello2 = (*benoit)->win.height / 2;
	ft_bzero((*benoit)->keys, 1024);
	if (argc == 3)
	{
		(*benoit)->win.width = ft_atoi(argv[1]);
		(*benoit)->win.height = ft_atoi(argv[2]);
	}
}

int main(int argc, char **argv)
{
	benoit_t	*benoit;

	frBenoitInit(argc, argv, &benoit);
	if (argc > 3)
		frErrorHandler(ARGS_NUMBER_ERROR);
	if (!(benoit->connect = mlx_init()))
		frErrorHandler(CONNECT_ERROR);
	if (!(benoit->window = mlx_new_window(benoit->connect, benoit->win.width, benoit->win.height, "Hello")))
		frErrorHandler(WINDOW_ERROR);
	if (!(benoit->picture = mlx_new_image(benoit->connect, benoit->win.width, benoit->win.height)))
		frErrorHandler(IMAGE_ERROR);
	if (!(benoit->pix_buf = mlx_get_data_addr(benoit->picture, &benoit->bits_per_pix, &benoit->size_line, &benoit->endian)))
		frErrorHandler(BUFFER_ERROR);
	bind_handlers(benoit);
	mlx_loop(benoit->connect);
	return (0);
}