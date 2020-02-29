#ifndef FRACTOL
# define FRACTOL
# include "../libmlx/mlx.h"
# include "../libft/includes/libft.h"
# include <stdlib.h>
#include <math.h>


typedef struct	s_mlx
{
	void	*ptr;
	void	*win;
}				t_mlx;

typedef	struct	s_image
{
	void	*img;
	char	*add_image;
	int		bpp;
	int		size_line;
	int		endian;
	int		colors;
	t_coord	size;
	int		valid;
}				t_image;

typedef struct  s_data
{
    t_mlx		mlx;
	t_image		image;
	t_coord		screen;

}               t_data;

int		frame(t_data *data);

#endif