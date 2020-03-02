#include "fractol.h"

int		init_window(t_data *data)
{
	data->screen.x = 900;
	data->screen.y = 700;
		if (!(data->mlx.ptr = mlx_init()))
			return (EXIT_FAILURE);
		if ((data->mlx.win = mlx_new_window(data->mlx.ptr, data->screen.x,
				data->screen.y, "Dgascon && Nlecaill")) == NULL)
			return (EXIT_FAILURE);
		if (!(data->image.img = mlx_new_image(data->mlx.ptr, data->screen.x,
				data->screen.y)))
			return (EXIT_FAILURE);
		if (!(data->image.add_image = mlx_get_data_addr(data->image.img,
				&data->image.bpp, &data->image.size_line, &data->image.endian)))
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int main(int ac, char **av)
{
	t_data data;

	data = (t_data){};
	init_window(&data);

	frame(&data);
	mlx_loop_hook(data.mlx.ptr, frame, &data);
	mlx_loop(data.mlx.ptr);
    return (0);
}