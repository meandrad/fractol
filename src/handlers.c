/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meandrad <meandrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 21:16:29 by meandrad          #+#    #+#             */
/*   Updated: 2025/04/24 21:32:19 by meandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

int	close_handler(t_fractal *fractal)
{
	mlx_destroy_image(fractal->mlx, fractal->img.img_ptr);
	mlx_destroy_window(fractal->mlx, fractal->win_ptr);
	mlx_destroy_display(fractal->mlx);
	free(fractal->mlx);
	exit(EXIT_SUCCESS);
}

int	key_handler(int keysym, t_fractal *fractal)
{
	if (keysym == XK_Escape)
		close_handler(fractal);
	if (keysym == XK_Left)
		fractal->shift_x += (0.5 * fractal->zoom);
	else if (keysym == XK_Right)
		fractal->shift_x -= (0.5 * fractal->zoom);
	else if (keysym == XK_Down)
		fractal->shift_y += (0.5 * fractal->zoom);
	else if (keysym == XK_Up)
		fractal->shift_y -= (0.5 * fractal->zoom);
	else if (keysym == XK_plus)
		fractal->max_interaction += 10;
	else if (keysym == XK_minus)
		fractal->max_interaction -= 10;
	fractal_render(fractal);
	return (0);
}

int	mouse_handler(int button, int x, int y, t_fractal *frac)
{
	double	mouse_re;
	double	mouse_im;
	double	zoom_factor;

	mouse_re = frac->shift_x + (x - WIDTH / 2.0)
		/ (WIDTH / (frac->zoom * 2));
	mouse_im = frac->shift_y - (y - HEIGHT / 2.0)
		/ (HEIGHT / (frac->zoom * 2));
	if (button == Button4)
	{
		zoom_factor = 1.1;
		frac->zoom *= zoom_factor;
	}
	else if (button == Button5)
	{
		zoom_factor = 1.0 / 1.1;
		frac->zoom *= zoom_factor;
	}
	else
		return (0);
	frac->shift_x = mouse_re - (x - WIDTH / 2.0) / (WIDTH / (frac->zoom * 2));
	frac->shift_y = mouse_im + (y - HEIGHT / 2.0) / (HEIGHT / (frac->zoom * 2));
	fractal_render(frac);
	return (0);
}

int	julia_track(int x, int y, t_fractal *fractal)
{
	if (!ft_strncmp(fractal->name, "julia", 5))
	{
		fractal->julia_x = (map(x, -2, +2, WIDTH)
				* fractal->zoom) + fractal->shift_x;
		fractal->julia_y = (map(y, +2, -2, HEIGHT)
				* fractal->zoom) + fractal->shift_y;
		fractal_render(fractal);
	}
	return (0);
}
