#include "fractol.h"

int draw(t_data *data, t_coord point, int color)
{
    *(int *)(data->image.add_image + (point.y * data->image.size_line) + point.x*sizeof(int)) =
    (color != 0) ? rgb_int(0, (color * 10 > 256) ? 256 : (color * 10), (color * 3 > 256) ? 256 : (color * 3), (color * 5 > 256) ? 256 : (color * 5)) : 0;
    return (0);
}

int computing(t_data *data, t_fcom_coord org_coord, t_coord point)
{
    float complex z;
    float complex z0;
    int i;
    t_fcom_coord coord;
    float module;
    int nb_iter = 200;

    i = 0;
    z = CMPLXF(org_coord.x,  org_coord.y);
    z0 = z;
    coord = org_coord;
    while(i < nb_iter)
    {
        // coord.x = (coord.x*coord.x) - (coord.y*coord.y) + org_coord.x;
        // coord.y = (2*coord.x*coord.y) + org_coord.y  ;
        z =  z * z + z0;
        module = (crealf(z) * crealf(z) + cimagf(z) * cimagf(z));
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
    t_coord point;
    t_fcom_coord coord;
    t_f_coord ratio;
    coord = (t_fcom_coord){.x = 0.0, .y = 0.0};
    point = (t_coord){.y = 0, .x = 0};
    ratio.x = 0.01 * ((float)200 / data->screen.x);
    ratio.y = 0.01 * ((float)200 / data->screen.y);
    //printf("start frame\n");
    while (point.x < data->screen.x)
    {
        coord.x = -1.5 +  (ratio.x * point.x);
        while (point.y < data->screen.y)
        {
            coord.y = -1 + (ratio.y * point.y);
            computing(data, coord, point);
            point.y++;
        }
        point.y = 0;
        point.x++;
    }
    mlx_put_image_to_window(data->mlx.ptr, data->mlx.win, data->image.img, 0, 0);

    return (0);
}