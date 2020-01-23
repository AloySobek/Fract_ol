/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 15:34:33 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/08 18:22:32 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fract_ol.h"

const char *mandelbrot_set =
"																																\
__kernel void mandelbrot_set(int s_c, int f_c, int x, int y, int max_iter, double zoom, double q, double w, int test1, __global int *image)	\
{																																\
	int		index = get_global_id(0);																							\
	double	midX = x / 2;																										\
	double	midY = y / 2;																										\
	double	currentX = 0.0;																										\
	double	currentY = 0.0;																										\
	double	X0 = (midX - (index - (index / x * x))) / zoom + q;																	\
	double	Y0 = (midY - (index / x)) / zoom + w;																				\
	double	squareX = 0.0;																										\
	double	squareY = 0.0;																										\
	double	difSquare = 0.0;																									\
	double	z_x = 0.0;																											\
	double	z_y = 0.0;																											\
	int iter;																													\
	for (iter = 0; squareX + squareY < 4.0 && iter < max_iter; ++iter)															\
	{																															\
		difSquare = squareX - squareY;																							\
		z_y = mad(z_x, z_y + z_y, 0) - Y0;																						\
		z_x = difSquare - X0;																									\
		if (currentX == z_x && currentY == z_y)																					\
		{																														\
			iter = max_iter;																									\
			break;																												\
		}																														\
		currentX = z_x;																											\
		currentY = z_y;																											\
		squareX = mad(z_x, z_x, 0);																								\
		squareY = mad(z_y, z_y, 0);																								\
	}																															\
	int r = ((s_c >> 16) & 0xff) + (((f_c >> 16) & 0xff) - ((s_c >> 16) & 0xff)) * iter / max_iter;								\
	int g = ((s_c >> 8) & 0xff) + (((f_c >> 8) & 0xff) - ((s_c >> 8) & 0xff)) * iter / max_iter;								\
	int b = (s_c & 0xff) + ((f_c & 0xff) - (s_c & 0xff)) * iter / max_iter;														\
	image[index] = (r << 16) | (g << 8) | b;																					\
}";

void			display_pixels(t_benoit *benoit)
{
	clEnqueueReadBuffer(benoit->c_q, benoit->P, CL_TRUE, 0 , sizeof(int) * benoit->win.width * benoit->win.height, (int *)benoit->pix_buf, 0, NULL, NULL);
	clEnqueueNDRangeKernel(benoit->c_q, benoit->kernel, 1, NULL, &benoit->global_size, &benoit->local_size, 0, NULL, NULL);
	clSetKernelArg(benoit->kernel, 0, sizeof(int), (void *)&benoit->start_color);
	clSetKernelArg(benoit->kernel, 1, sizeof(int), (void *)&benoit->finish_color);
	clSetKernelArg(benoit->kernel, 2, sizeof(int), (void *)&benoit->win.width);
	clSetKernelArg(benoit->kernel, 3, sizeof(int), (void *)&benoit->win.height);
	clSetKernelArg(benoit->kernel, 4, sizeof(int), (void *)&benoit->max_iter);
	clSetKernelArg(benoit->kernel, 5, sizeof(double), (void *)&benoit->zoom);
	clSetKernelArg(benoit->kernel, 6, sizeof(double), (void *)&benoit->x);
	clSetKernelArg(benoit->kernel, 7, sizeof(double), (void *)&benoit->y);
	clSetKernelArg(benoit->kernel, 8, sizeof(int), (void *)&benoit->test);
	clSetKernelArg(benoit->kernel, 9, sizeof(cl_mem), (void *)&benoit->P);
	clFlush(benoit->c_q);
	clFinish(benoit->c_q);
	mlx_put_image_to_window(benoit->connect, benoit->window, benoit->picture, 0, 0);
}

void			do_something(t_benoit *benoit)
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

int				key_press(int key_press, t_benoit *benoit)
{
	if (key_press == 53)
	{
		clReleaseKernel(benoit->kernel);
		clReleaseProgram(benoit->program);
		clReleaseMemObject(benoit->P);
		clReleaseCommandQueue(benoit->c_q);
		clReleaseContext(benoit->context);
		free(benoit->platforms_id);
		free(benoit->devices_id);
		mlx_destroy_window(benoit->connect, benoit->window);
		exit(1);
	}
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
	display_pixels(benoit);
	do_something(benoit);
	return (0);
}

int				key_release(int key_press, t_benoit *benoit)
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

int				mouse_press(int button, int x, int y, t_benoit *benoit)
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
	display_pixels(benoit);
	do_something(benoit);
	return (0);
}

int				mouse_release(int button, int x, int y, t_benoit *benoit)
{
	if (button == 3)
		benoit->keys[3] = 0;
	return (0);
}

int				mouse_move(int x, int y, t_benoit *benoit)
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

int				expose(t_benoit *benoit)
{
	display_pixels(benoit);
	return (0);
}

int				close_window(t_benoit *benoit)
{
	return (0);
}

void			error_handler(int code_error)
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

void			bind_handlers(t_benoit *benoit)
{
	mlx_hook(benoit->window,  2, 0, key_press,		benoit);
	mlx_hook(benoit->window,  3, 0, key_release,    benoit);
	mlx_hook(benoit->window,  4, 0, mouse_press,	benoit);
	mlx_hook(benoit->window,  5, 0, mouse_release,	benoit);
	mlx_hook(benoit->window,  6, 0, mouse_move,		benoit);
	mlx_hook(benoit->window, 12, 0, expose,			benoit);
	mlx_hook(benoit->window, 17, 0, close_window,	benoit);
}

t_benoit		*benoit_init(int argc, char **argv)
{
	t_benoit	*benoit;

	if (!(benoit = (t_benoit *)malloc(sizeof(t_benoit))))
		error_handler(MEMORY_ALLOC_ERROR);
	benoit->start_color = 0x8b8b;
	benoit->finish_color = 0x8b008b;
	benoit->win.width = 1920;
	benoit->win.height = 1080;
	benoit->max_iter = 30;
	benoit->x = 0.0f;
	benoit->y = 0.0f;
	benoit->zoom = 300.0f;
	benoit->platforms_id = NULL;
	benoit->devices_id = NULL;
	benoit->platforms_count = 0;
	benoit->devices_count = 0;
	benoit->test = 2;
	benoit->hello1 = benoit->win.width / 2;
	benoit->hello2 = benoit->win.height / 2;

	ft_bzero(benoit->keys, 1024);
	//benoit->image_format = (cl_image_format *)malloc(sizeof(cl_image_format));
	//benoit->image_desc = (cl_image_desc *)malloc(sizeof(cl_image_desc));
	//benoit->image_format->image_channel_data_type = CL_SIGNED_INT32;
	//benoit->image_format->image_channel_order = CL_RGBA;
	//benoit->image_desc->image_type = CL_MEM_OBJECT_IMAGE2D;
	//benoit->image_desc->image_width = benoit->win.width;
	//benoit->image_desc->image_height = benoit->win.height;
	//benoit->image_desc->image_depth = 1;
	//benoit->image_desc->image_array_size = 1;
	//benoit->image_desc->image_row_pitch = 0;
	//benoit->image_desc->image_slice_pitch = 0;
	//benoit->image_desc->num_mip_levels = 0;
	//benoit->image_desc->num_samples = 0;
	//benoit->image_desc->buffer = NULL;
	clGetPlatformIDs(0, NULL, &benoit->platforms_count);
	benoit->platforms_id = (cl_platform_id *)malloc(sizeof(cl_platform_id) * benoit->platforms_count);
	clGetPlatformIDs(benoit->platforms_count, benoit->platforms_id, NULL);
	benoit->platform = 0;
	while (ft_strcmp(benoit->info, "Apple") && benoit->platform < benoit->platforms_count)
		clGetPlatformInfo(benoit->platforms_id[benoit->platform++], CL_PLATFORM_NAME, 1024, benoit->info, NULL);
	benoit->platform--;
	clGetDeviceIDs(benoit->platforms_id[benoit->platform], CL_DEVICE_TYPE_GPU, 0, NULL, &benoit->devices_count);
	benoit->devices_id = (cl_device_id *)malloc(sizeof(cl_device_id) * benoit->devices_count);
	clGetDeviceIDs(benoit->platforms_id[benoit->platform], CL_DEVICE_TYPE_GPU, benoit->devices_count, benoit->devices_id, NULL);
	benoit->device = 0;
	while (!ft_strstr(benoit->info, "AMD") && benoit->device < benoit->devices_count)
		clGetDeviceInfo(benoit->devices_id[benoit->device++], CL_DEVICE_NAME, 1024, benoit->info, NULL);
	benoit->device--;

	if (argc == 3)
	{
		benoit->win.width = ft_atoi(argv[1]);
		benoit->win.height = ft_atoi(argv[2]);
	}
	benoit->context = clCreateContext(NULL, benoit->devices_count, benoit->devices_id, NULL, NULL, &benoit->status);
	benoit->c_q = clCreateCommandQueue(benoit->context, benoit->devices_id[benoit->device], 0, &benoit->status);
	benoit->P = clCreateBuffer(benoit->context, CL_MEM_WRITE_ONLY, sizeof(int) * benoit->win.height * benoit->win.width, NULL, &benoit->status);
	//benoit->image_obj = clCreateImage(benoit->connect, CL_MEM_WRITE_ONLY, benoit->image_format, benoit->image_desc, NULL, &benoit->status);
	benoit->program = clCreateProgramWithSource(benoit->context, 1, (const char **)&mandelbrot_set, NULL, &benoit->status);
	benoit->status = clBuildProgram(benoit->program, 1, benoit->devices_id, NULL, NULL, NULL);
	if (benoit->status != CL_SUCCESS)
	{
		char *buff_erro;
		cl_int errcode;
		size_t build_log_len;
		errcode = clGetProgramBuildInfo(benoit->program, benoit->devices_id[0], CL_PROGRAM_BUILD_LOG, 0, NULL, &build_log_len);
		if (errcode)
            printf("clGetProgramBuildInfo failed at line %d\n", __LINE__); exit(-1);
    	buff_erro = malloc(build_log_len);
    	if (!buff_erro)
		    printf("malloc failed at line %d\n", __LINE__); exit(-2);
    	errcode = clGetProgramBuildInfo(benoit->program, benoit->devices_id[0], CL_PROGRAM_BUILD_LOG, build_log_len, buff_erro, NULL);
    	if (errcode)
        	printf("clGetProgramBuildInfo failed at line %d\n", __LINE__); exit(-3);
    	fprintf(stderr,"Build log: \n%s\n", buff_erro);
    	free(buff_erro);
    	fprintf(stderr,"clBuildProgram failed\n");
    	exit(EXIT_FAILURE);
	}
	benoit->kernel = clCreateKernel(benoit->program, "mandelbrot_set", &benoit->status);
	benoit->global_size = benoit->win.height * benoit->win.width;
	benoit->local_size = 256;
	return (benoit);
}

int				main(int argc, char **argv)
{
	t_benoit			*benoit;

	if (argc > 3)
		error_handler(ARGS_NUMBER_ERROR);
	if (!(benoit = benoit_init(argc, argv)))
		error_handler(BENOIT_VARIABLE_INIT_ERROR);
	if (!(benoit->connect = mlx_init()))
		error_handler(CONNECT_ERROR);
	if (!(benoit->window = mlx_new_window(benoit->connect, benoit->win.width, benoit->win.height, "Hello")))
		error_handler(WINDOW_ERROR);
	if (!(benoit->picture = mlx_new_image(benoit->connect, benoit->win.width, benoit->win.height)))
		error_handler(IMAGE_ERROR);
	if (!(benoit->pix_buf = mlx_get_data_addr(benoit->picture, &benoit->bits_per_pix, &benoit->size_line, &benoit->endian)))
		error_handler(BUFFER_ERROR);
	//ft_printf("%d %d\n", benoit->bits_per_pix, benoit->size_line);
	//exit(1);
	bind_handlers(benoit);
	mlx_loop(benoit->connect);
	return (0);
}

// "__kernel\
// void histogram_kernel(__global const uint *data, \
// 	__local uchar *shaderArray,\
// 		__global uint *binResultR,\
// 			__global uint *binResultG,\
// 				__global uint *binResultB)\
// {\
// 	size_t localId = get_local_id(0);\
// 	size_t globalId = get_global_id(0);\
// 	size_t groupID = get_group_id(0);\
// 	size_t groupSize = get_local_size(0);\
// 	__local uchar *sharedArrayR = sharedArray;\
// 	__local uchar *sharedArrayG = sharedArray + \
// 									groupSize * BIN_SIZE;\
// 	__local uchar *sharedArrayB = sharedArray + \
// 									2 * groupSize * BIN_SIZE; \
// 	for (int i = 0; i < BIN_SIZE, ++i)\
// 	{\
// 		sharedArrayR[localId * BIN_SIZE + i] = 0;\
// 		sharedArrayG[localId * BIN_SIZE + i] = 0;\
// 		sharedArrayB[localId * BIN_SIZE + i] = 0;\
// 	}\
// 	for (int i = 0; i < BIN_SIZE; ++i)\
// 	{\
// 		uint value = data[globalId * BIN_SIZE + i];\
// 		uint valueR = vlud & 0xFF;\
// 		uint valueG = (value & 0xFF00) >> 8;\
// 		unit valueB = (value & 0xFF0000) >> 16;\
// 		sharedArrayR[localId * BIN_SIZE + valueR]++;\
// 		sharedArrayG[localId * BIN_SIZE + valueG]++;\
// 		sharedArrayB[localId * BIN_SIZE + valueB]++;\
// 	}\
// 	barrier(CLK_LOCAL_MEM_FENCE);\
// 	for (int i = 0; i < BIN_SIZE / groupSize; ++i)\
// 	{\
// 		uint binCountR = 0;\
// 		uint binCountG = 0;\
// 		uint binCountB = 0;\
// 		for (int j = 0; j < groupsSize; ++j)\
// 		{\
// 			binCountR += sharedArrayR[j * BIN_SIZE + i * groupSize + localId];\
// 			binCountG += sharedArrayG[j * BIN_SIZE + i * groupSize + localId];\
// 			bincountB += sharedArrayB[j * BIN_SIZE + i * groupSize + localId];\
// 		}\
// 		binResultR[groupId * BIN_SIZE + i * groupSize + localId] = binCountR;\
// 		binResultG[groupId * BIN_SIZE + i * groupSize + localId] = binCountG;\
// const char *histogram_kernel =
// 		binResultB[groupId * BIN_SIZE + i * groupSize + localId] = binCountB;\
// 	}\
// }";
