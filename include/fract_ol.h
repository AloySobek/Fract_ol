/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract_ol.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 15:33:31 by vrichese          #+#    #+#             */
/*   Updated: 2019/09/06 21:02:17 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACT_OL_H
# define FRACT_OL_H

# include "ft_printf.h"
# include "get_next_line.h"
# include "libft.h"
# include <mlx.h>
#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/opencl.h>
#endif

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
	int				bits_per_pix;
	int				size_line;
	int				color;
	int				endian;
	int				test;
	int				start_color;
	int				finish_color;
	int				max_iter;
	void			*window;
	char				*pix_buf;
	void			*connect;
	void			*picture;
	double			zoom;
	double			x;
	double			y;
	double			x1;
	double			y1;
	cl_device_id	*devices_id;
	cl_platform_id	*platforms_id;
	cl_uint			devices_count;
	cl_uint			platforms_count;
	cl_int			device;
	cl_int			platform;
	cl_context		context;
	cl_mem			P;
	cl_kernel		kernel;
	cl_program		program;
	cl_command_queue c_q;
	t_window		win;
	cl_int			status;
	size_t			global_size;
	size_t			local_size;
	char			info[1024];
	int				keys[1024];
}					t_benoit;

/*
**	Error_manage macros
*/

# define IMAGE_ERROR				1
# define WINDOW_ERROR				2
# define CONNECT_ERROR				3
# define ARGS_NUMBER_ERROR			4
# define MEMORY_ALLOC_ERROR			5
# define BENOIT_VARIABLE_INIT_ERROR	6
# define BUFFER_ERROR				7


#endif

// void			fill_screen(t_benoit *benoit)
// {
// 	double		total;
// 	double		z_x;
// 	double		z_y;
// 	double		one;
// 	double		two;
// 	double		center_x;
// 	double		center_y;
// 	int			x;
// 	int			y;
// 	int			iter;
// 	int			color;

// 	x = 0;
// 	center_x = benoit->win.width / 2;
// 	center_y = benoit->win.height / 2;
// 	while (x < benoit->win.width)
// 	{
// 		y = 0;
// 		while (y < benoit->win.height)
// 		{
// 			z_x = 0.0;
// 			z_y = 0.0;
// 			iter = 0;
// 			one = (center_x - x) / test + g_x;
// 			two = (center_y - y) / test + g_y;
// 			while (z_x * z_x + z_y * z_y < 4.0 && iter < 50)
// 			{
// 				total = z_x * z_x - z_y * z_y;
// 				z_y = 2 * z_x * z_y - two;
// 				z_x = total - one;
// 				++iter;
// 			}
// 			color = get_color(0x8b008b, 0x8b8b, 1000, iter * 1000);
// 			pixel_put(benoit, x, y, color);
// 			++y;
// 		}
// 		++x;
// 	}
// }
// const char *mandelbrot_set =
// "__kernel void mandelbrot_set(int x, int y, float test, __global float *z_x, __global float *z_y, __global int *iter)\
// {\
// 	int index = get_global_id(0); \
// 	float center_x = x / 2;\
// 	float center_y = y / 2;\
// 	float total;\
// 	float one = (center_x - (index - (index / x * x))) / test;\
// 	float two = (center_y - (index / x)) / test;\
// 	float squarex = 0.0f;\
// 	float squarey = 0.0f;\
// 	while (squarex + squarey < 4.0f && iter[index] < 1000) \
// 	{\
// 		total = squarex - squarey;\
// 		z_y[index] = 2 * z_x[index] * z_y[index] - two;\
// 		z_x[index] = total - one;\
// 		squarex = z_x[index] * z_x[index];\
// 		squarey = z_y[index] * z_y[index];\
// 		iter[index] += 1;\
// 	}\
// }";

// void			fill_screen(t_benoit *benoit)
// {
// 	int color;

// 	ft_bzero(benoit->x, sizeof(float) * benoit->win.height * benoit->win.width);
// 	ft_bzero(benoit->y, sizeof(float) * benoit->win.height * benoit->win.width);
// 	ft_bzero(benoit->iter, sizeof(int) * benoit->win.height * benoit->win.width);
// 	clFlush(benoit->c_q);
// 	clFinish(benoit->c_q);
// 	for (int i = 0; i < benoit->win.height * benoit->win.width; ++i)
// 	{
// 		color = get_color(0x8b008b, 0x8b8b, 500, benoit->iter[i] * 1000);
// 		pixel_put(benoit, (i - (i / benoit->win.width * benoit->win.width)), i / benoit->win.width, color);
// 	}
// }

// void			display_pixels(t_benoit *benoit)
// {
// 	ft_bzero(benoit->pix_buf, benoit->win.width * benoit->win.height * 4);
// 	fill_screen(benoit);
// 	mlx_put_image_to_window(benoit->connect, benoit->window, benoit->picture, 0, 0);
// }

// int				key_press(int key_press, t_benoit *benoit)
// {
// 	if (key_press == 53)
// 	{
// 		mlx_destroy_window(benoit->connect, benoit->window);
// 		exit(1);
// 	}
// 	if (key_press == 126)
// 		g_y -= 3.0f / test;
// 	if (key_press == 125)
// 		g_y += 3.0f / test;
// 	if (key_press == 124)
// 		g_x += 3.0f / test;
// 	if (key_press == 123)
// 		g_x -= 3.0f / test;
// 	display_pixels(benoit);
// 	return (0);
// }

// int				mouse_press(int button, int x, int y, t_benoit *benoit)
// {
// 	if (button == 4)
// 	{
// 		test *= 1.1;
// 		display_pixels(benoit);
// 	}
// 	if (button == 5)
// 	{
// 		test *= 0.9;
// 		display_pixels(benoit);
// 	}
// 	return (0);
// }

// int				mouse_release(int button, int x, int y, t_benoit *benoit)
// {
// 	return (0);
// }

// int				mouse_move(int x, int y, t_benoit *benoit)
// {
// 	return (0);
// }

// int				expose(t_benoit *benoit)
// {
// 	return (0);
// }

// int				close_window(t_benoit *benoit)
// {
// 	return (0);
// }

// void			error_handler(int code_error)
// {
// 	if (code_error == IMAGE_ERROR)
// 		ft_printf("The image object has not been created, emeregency exit...\n");
// 	else if (code_error == WINDOW_ERROR)
// 		ft_printf("The window has not been create, emeregency exit...\n");
// 	else if (code_error == CONNECT_ERROR)
// 		ft_printf("Connect has not been established, emeregncy exti...\n");
// 	else if (code_error == ARGS_NUMBER_ERROR)
// 		ft_printf("Numbers of args is wrong, try again\n");
// 	else if (code_error == MEMORY_ALLOC_ERROR)
// 		ft_printf("Memory has not been allocated, emeregency exit...\n");
// 	else if (code_error == BENOIT_VARIABLE_INIT_ERROR)
// 		ft_printf("Main varibale has not been initialized, emeregency exit...\n");
// 	else if (code_error == BUFFER_ERROR)
// 		ft_printf("Pixel buffer has not been created, emergency exit...\n");
// 	exit(1);
// }

// void			bind_handlers(t_benoit *benoit)
// {
// 	mlx_hook(benoit->window,  2, 0, key_press,		benoit);
// 	mlx_hook(benoit->window,  4, 0, mouse_press,	benoit);
// 	mlx_hook(benoit->window,  5, 0, mouse_release,	benoit);
// 	mlx_hook(benoit->window,  6, 0, mouse_move,		benoit);
// 	mlx_hook(benoit->window, 12, 0, expose,			benoit);
// 	mlx_hook(benoit->window, 17, 0, close_window,	benoit);
// }

// t_benoit		*benoit_init(int argc, char **argv)
// {
// 	t_benoit	*benoit;

// 	if (!(benoit = (t_benoit *)malloc(sizeof(t_benoit))))
// 		error_handler(MEMORY_ALLOC_ERROR);
// 	benoit->win.width = 1920;
// 	benoit->win.height = 1080;
// 	if (argc == 3)
// 	{
// 		benoit->win.width = ft_atoi(argv[1]);
// 		benoit->win.height = ft_atoi(argv[2]);
// 	}
// 	return (benoit);
// }

// int				main(int argc, char **argv)
// {
// 	t_benoit			*benoit;
// 	char 				info[LOG_SIZE];
// 	cl_int				platform;
// 	cl_int				device;


// 	cl_platform_id		*platforms_id;
// 	cl_device_id		*devices_id;
// 	cl_context			context;
// 	cl_uint				platforms_count;
// 	cl_uint				devices_count;
// 	cl_int				status;

// 	if (argc > 3)
// 		error_handler(ARGS_NUMBER_ERROR);
// 	if (!(benoit = benoit_init(argc, argv)))
// 		error_handler(BENOIT_VARIABLE_INIT_ERROR);
// 	if (!(benoit->connect = mlx_init()))
// 		error_handler(CONNECT_ERROR);
// 	if (!(benoit->window = mlx_new_window(benoit->connect, benoit->win.width, benoit->win.height, "Hello")))
// 		error_handler(WINDOW_ERROR);
// 	if (!(benoit->picture = mlx_new_image(benoit->connect, benoit->win.width, benoit->win.height)))
// 		error_handler(IMAGE_ERROR);
// 	if (!(benoit->pix_buf = mlx_get_data_addr(benoit->picture, &benoit->bits_per_pix, &benoit->size_line, &benoit->endian)))
// 		error_handler(BUFFER_ERROR);
// 	bind_handlers(benoit);

// 	benoit->x = (float *)malloc(sizeof(float) * benoit->win.height * benoit->win.width);
// 	benoit->y = (float *)malloc(sizeof(float) * benoit->win.height * benoit->win.width);
// 	benoit->iter = (int *)malloc(sizeof(int) * benoit->win.height * benoit->win.width);

// 	ft_bzero(benoit->x, sizeof(float) * benoit->win.height * benoit->win.width);
// 	ft_bzero(benoit->y, sizeof(float) * benoit->win.height * benoit->win.width);
// 	ft_bzero(benoit->iter, sizeof(int) * benoit->win.height * benoit->win.width);

// 	platforms_id = NULL;
// 	devices_id = NULL;
// 	platforms_count = 0;
// 	devices_count = 0;

// 	clGetPlatformIDs(0, NULL, &platforms_count);
// 	platforms_id = (cl_platform_id *)malloc(sizeof(cl_platform_id) * platforms_count);
// 	clGetPlatformIDs(platforms_count, platforms_id, NULL);
// 	platform = 0;
// 	while (ft_strcmp(info, "Apple") && platform < platforms_count)
// 		clGetPlatformInfo(platforms_id[platform++], CL_PLATFORM_NAME, LOG_SIZE, info, NULL);
// 	platform--;
// 	clGetDeviceIDs(platforms_id[platform], CL_DEVICE_TYPE_GPU, 0, NULL, &devices_count);
// 	devices_id = (cl_device_id *)malloc(sizeof(cl_device_id) * devices_count);
// 	clGetDeviceIDs(platforms_id[platform], CL_DEVICE_TYPE_GPU, devices_count, devices_id, NULL);
// 	device = 0;
// 	while (!ft_strstr(info, "AMD") && device < devices_count)
// 		clGetDeviceInfo(devices_id[device++], CL_DEVICE_NAME, LOG_SIZE, info, NULL);
// 	device--;

// 	context = clCreateContext(NULL, devices_count, devices_id, NULL, NULL, &status);
// 	if (status)
// 	{
// 		ft_printf("buy buy %d", status);
// 		exit(1);
// 	}

// 	benoit->c_q = clCreateCommandQueue(context, devices_id[device], 0, &status);
// 	if (status)
// 	{
// 		ft_printf("buy buy %d", status);
// 		exit(1);
// 	}

// 	cl_mem X = clCreateBuffer(context, CL_MEM_READ_WRITE, sizeof(float) * benoit->win.height * benoit->win.width, NULL, &status);
// 	if (status)
// 	{
// 		ft_printf("buy buy %d", status);
// 		exit(1);
// 	}
// 	cl_mem Y = clCreateBuffer(context, CL_MEM_READ_WRITE, sizeof(float) * benoit->win.height * benoit->win.width, NULL, &status);
// 	if (status)
// 	{
// 		ft_printf("buy buy %d", status);
// 		exit(1);
// 	}
// 	cl_mem I = clCreateBuffer(context, CL_MEM_READ_WRITE, sizeof(int) * benoit->win.height * benoit->win.width, NULL, &status);
// 	if (status)
// 	{
// 		ft_printf("buy buy %d", status);
// 		exit(1);
// 	}

// 	status = clEnqueueWriteBuffer(benoit->c_q, X, CL_TRUE, 0, sizeof(float) * benoit->win.height * benoit->win.width, benoit->x, 0, NULL, NULL);
// 	if (status)
// 	{
// 		ft_printf("buy buy %d", status);
// 		exit(1);
// 	}
// 	status = clEnqueueWriteBuffer(benoit->c_q, Y, CL_TRUE, 0, sizeof(float) * benoit->win.height * benoit->win.width, benoit->y, 0, NULL, NULL);
// 	if (status)
// 	{
// 		ft_printf("buy buy %d", status);
// 		exit(1);
// 	}
// 	status = clEnqueueWriteBuffer(benoit->c_q, I, CL_TRUE, 0, sizeof(int) * benoit->win.height * benoit->win.width, benoit->iter, 0, NULL, NULL);
// 	if (status)
// 	{
// 		ft_printf("buy buy %d", status);
// 		exit(1);
// 	}

// 	cl_program program = clCreateProgramWithSource(context, 1, (const char **)&mandelbrot_set, NULL, &status);
// 	if (status)
// 	{
// 		ft_printf("buy buy %d", status);
// 		exit(1);
// 	}
// 	status = clBuildProgram(program, 1, devices_id, NULL, NULL, NULL);
// 	if (status)
// 	{
// 		ft_printf("buy buy %d", status);
// 		exit(1);
// 	}
// 	cl_kernel kernel = clCreateKernel(program, "mandelbrot_set", &status);
// 	if (status)
// 	{
// 		ft_printf("buy buy %d", status);
// 		exit(1);
// 	}
// 	status = clSetKernelArg(kernel, 0, sizeof(int), (void *)&benoit->win.width);
// 	if (status)
// 	{
// 		ft_printf("buy buy %d", status);
// 		exit(1);
// 	}
// 	status = clSetKernelArg(kernel, 1, sizeof(int), (void *)&benoit->win.height);
// 	if (status)
// 	{
// 		ft_printf("buy buy %d", status);
// 		exit(1);
// 	}
// 	status = clSetKernelArg(kernel, 2, sizeof(float), (void *)&test);
// 	if (status)
// 	{
// 		ft_printf("buy buy %d", status);
// 		exit(1);
// 	}
// 	status = clSetKernelArg(kernel, 3, sizeof(cl_mem), (void *)&X);
// 	if (status)
// 	{
// 		ft_printf("buy buy %d", status);
// 		exit(1);
// 	}
// 	status = clSetKernelArg(kernel, 4, sizeof(cl_mem), (void *)&Y);
// 	if (status)
// 	{
// 		ft_printf("buy buy %d", status);
// 		exit(1);
// 	}
// 	status = clSetKernelArg(kernel, 5, sizeof(cl_mem), (void *)&I);
// 	if (status)
// 	{
// 		ft_printf("buy buy %d", status);
// 		exit(1);
// 	}
// 	size_t global_size = benoit->win.height * benoit->win.width;
// 	size_t local_size = 64;
// 	status = clEnqueueNDRangeKernel(benoit->c_q, kernel, 1, NULL, &global_size, &local_size, 0, NULL, NULL);
// 	if (status)
// 	{
// 		ft_printf("buy buy %d", status);
// 		exit(1);
// 	}
// 	status = clEnqueueReadBuffer(benoit->c_q, I, CL_TRUE, 0, sizeof(int) * benoit->win.height * benoit->win.width, benoit->iter, 0, NULL, NULL);
// 	if (status)
// 	{
// 		ft_printf("buy buy %d", status);
// 		exit(1);
// 	}
// 	status = clFlush(benoit->c_q);
// 	if (status)
// 	{
// 		ft_printf("buy buy %d", status);
// 		exit(1);
// 	}
// 	status = clFinish(benoit->c_q);
// 	if (status)
// 	{
// 		ft_printf("buy buy %d", status);
// 		exit(1);
// 	}
// 	//for (int i = 0; i < benoit->win.height * benoit->win.width; ++i)
// 	//	printf("%d", benoit->iter[i]);

// 	int color;
// 	ft_bzero(benoit->pix_buf, benoit->win.width * benoit->win.height * 4);
// 	for (int i = 0; i < benoit->win.height * benoit->win.width; ++i)
// 	{
// 		color = get_color(0x8b008b, 0x8b8b, 500, benoit->iter[i] * 1000);
// 		pixel_put(benoit, (i - (i / benoit->win.width * benoit->win.width)), i / benoit->win.width, color);
// 	}
// 	mlx_put_image_to_window(benoit->connect, benoit->window, benoit->picture, 0, 0);
// 	//clReleaseKernel(kernel);
// 	//clReleaseProgram(program);
// 	//clReleaseMemObject(X);
// 	//clReleaseMemObject(Y);
// 	//clReleaseMemObject(I);
// 	//clReleaseCommandQueue(benoit->c_q);
// 	//clReleaseContext(context);
// 	//free(benoit->x);
// 	//free(benoit->y);
// 	//free(benoit->iter);
// 	//free(platforms_id);
// 	//free(devices_id);
// 	mlx_loop(benoit->connect);
// 	return (0);