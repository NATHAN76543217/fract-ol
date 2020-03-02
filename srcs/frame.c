#include "fractol.h"

int draw(t_data *data, t_coord point, int color)
{
    int val;

    // val = rgb_int(0, (color * 2 > 256) ? 256 : (color * 2), (color * 3 > 256) ? 256 : (color * 3), (color * 4 > 256) ? 256 : (color * 4));
    val = rgb_int(0, 200, color * 10,color *5);
    *(int *)(data->image.add_image + (point.y * data->image.size_line) + point.x*sizeof(int)) = (color != 0) ? val : 0; 
    return (0);
}

int computing(t_data *data, t_f_complex z0, t_coord point)
{
    t_f_complex z;
    t_f_complex c;
    
    int i;

    float module;
    int nb_iter = 150;
    float tmp;

    i = 0;
    z = z0;
    c.re = 0.5;
    c.im = 0.9;
    while(i < nb_iter)
    {
        tmp = z.re;
        // z.re = z.re * z.re - z.im * z.im + c.re;
        // z.im = 2 * z.im * z.re + c.im;
       z = add_comp(mult_comp(z, z), c);
        module = (z.re * z.re + z.im * z.im);
        if (module >= 4)
        {
            draw(data, point, i);
            i = nb_iter;
        }
        i++;
    }
    if (i == nb_iter)
        draw(data, point, 0);
    return (0);
}

int frame(t_data *data)
{
    t_coord     point;
    t_f_complex coord;
    t_f_coord   ratio;

    coord = (t_f_complex){.re = 0.0, .im = 0.0};
    point = (t_coord){.y = 0, .x = 0};
    ratio.x = 0.02 * ((float)200 / data->screen.x);
    ratio.y = 0.02 * ((float)200 / data->screen.y);
    while (point.x < data->screen.x)
    {
        coord.re = -1.5 +  (ratio.x * point.x);
        while (point.y < data->screen.y)
        {
            coord.im = -1 + (ratio.y * point.y);
            computing(data, coord, point);
            point.y++;
        }
        point.y = 0;
        point.x++;
    }
    mlx_put_image_to_window(data->mlx.ptr, data->mlx.win, data->image.img, 0, 0);

    return (0);
}