/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meandrad <meandrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 20:16:45 by meandrad          #+#    #+#             */
/*   Updated: 2025/04/25 01:35:28 by meandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

void	malloc_error(void)
{
	exit(EXIT_FAILURE);
}

void	data_init(t_fractal *fractal)
{
	fractal->escape_value = 4;
	fractal->max_interaction = 42;
	fractal->shift_x = 0.0;
	fractal->shift_y = 0.0;
	fractal->zoom = 1.0;
	fractal->x_min = -2.0;
	fractal->x_max = 1.0;
	fractal->y_min = -1.5;
	fractal->y_max = 1.5;
}

static void	events_init(t_fractal *fractal)
{
	mlx_hook(fractal->win_ptr, DestroyNotify,
		StructureNotifyMask, close_handler, fractal);
	mlx_key_hook(fractal->win_ptr, key_handler, fractal);
	mlx_mouse_hook(fractal->win_ptr, mouse_handler, fractal);
}

void	fractal_init(t_fractal *fractal)
{
	fractal->mlx = mlx_init();
	if (fractal->mlx == NULL)
		malloc_error();
	fractal->win_ptr = mlx_new_window(fractal->mlx, WIDTH,
			HEIGHT, fractal->name);
	if (fractal->win_ptr == NULL)
	{
		mlx_destroy_display(fractal->mlx);
		free(fractal->mlx);
		malloc_error();
	}
	fractal->img.img_ptr = mlx_new_image(fractal->mlx, WIDTH, HEIGHT);
	if (fractal->img.img_ptr == NULL)
	{
		mlx_destroy_window(fractal->mlx, fractal->win_ptr);
		mlx_destroy_display(fractal->mlx);
		free(fractal->mlx);
		malloc_error();
	}
	fractal->img.pixels_ptr = mlx_get_data_addr(fractal->img.img_ptr,
			&fractal->img.bits_per_pixel, &fractal->img.line_length,
			&fractal->img.endian);
	data_init(fractal);
	events_init(fractal);
}
