/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract_ol.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 15:33:31 by vrichese          #+#    #+#             */
/*   Updated: 2019/09/10 14:47:00 by vrichese         ###   ########.fr       */
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

//typedef struct			_cl_image_format
//{
//	cl_channel_order	image_channel_order;
//	cl_channel_type		image_channel_data_type;
//}						cl_image_format;
//
//typedef struct			_cl_image_desc
//{
//	cl_mem_object_type	image_type;
//	size_t				image_width;
//	size_t				image_height;
//	size_t				image_depth;
//	size_t				image_array_size;
//	size_t				image_row_pitch;
//	size_t				image_slice_pitch;
//	cl_uint				num_mip_levels;
//	cl_uint				num_samples;
//	cl_mem				buffer;
//}						cl_image_desc;

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
	char			*pix_buf;
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
	cl_command_queue	c_q;
	//cl_image_format	*image_format;
	//cl_image_desc	*image_desc;
	cl_mem			image_obj;
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