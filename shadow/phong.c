/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshidakazushi <yoshidakazushi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 23:32:07 by yoshidakazu       #+#    #+#             */
/*   Updated: 2024/09/15 17:36:13 by yoshidakazu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shadow.h"
#include "../includes/ray_cross.h"

int color_calc(t_object *nearest_obj, double brightness)
{
    int color_r = (int)(fmin(nearest_obj->rgb->r * brightness , 1.0) * 255);
    int color_g = (int)(fmin(nearest_obj->rgb->g * brightness , 1.0) * 255);
    int color_b = (int)(fmin(nearest_obj->rgb->b * brightness , 1.0) * 255);

    int color = (color_r << 16) | (color_g << 8) | color_b;
    return color;
}
t_rgb check_color_is_valid(t_rgb a)
{
    if(a.r > 1)
        a.r = 1;
    else if(a.r < 0)
        a.r = 0;
    if(a.g > 1)
        a.g = 1;
    else if(a.g < 0)
        a.g = 0;
    if(a.b > 1)
        a.b = 1;
    else if(a.b < 0)
        a.b = 0;
    return a;
}
t_rgb color_mul(t_rgb a, t_rgb b)
{
    a.r *= b.r;
    a.g *= b.g;
    a.b *= b.b;
    return check_color_is_valid(a);
}

t_rgb color_mul_scalar(t_rgb a, double b)
{
    a.r *= b;
    a.g *= b;
    a.b *= b;
    return check_color_is_valid(a);
}

// TODO　centerを使わないやり方にリファクタする
int phong_calc(t_rt *rt, t_vec3 dir_vec, t_object *nearest_obj)
{
	// t_vec3  dsc = vec3_mul(*rt->scene->camera->nr_vec, (double)rt->width / (2 * tan((float)rt->scene->camera->view_degree / 2)));
    // t_vec3 dir_vec = vec3_norm(vec3_add(screen_vec, dsc));
    t_vec3 intersection = vec3_add(*rt->scene->camera->view_point, vec3_mul(dir_vec, calc_distance(nearest_obj, dir_vec, rt->scene->camera->view_point)));
    t_vec3 normal;
    t_rgb diff;
    t_rgb spec;
    t_rgb amb;
    //正規化による方向ベクトルの算出
    if(nearest_obj->type == SPHERE)
        normal = vec3_norm(vec3_sub(intersection, *nearest_obj->center));
    if(nearest_obj->type == PLANE)
        normal = *nearest_obj->normal_vec;
    if(nearest_obj->type == CYLINDER)
        normal = *nearest_obj->normal_vec;
    t_vec3 light_vec = vec3_norm(vec3_sub(*rt->scene->light->light_point,intersection));
    t_vec3 view_vec = vec3_norm(vec3_sub(intersection, *rt->scene->camera->view_point));
    
    double amb = rt->scene->ambi_light->ratio * rt->scene->light->factor->ka;
    double diff_deg = vec3_dot(normal, light_vec);
    if(diff_deg < 0)
        diff_deg = 0;
    double diff = color_mul_scalar(color_mul(rt->scene->light->factor->kd,color_mul_scalar(*rt->scene->light->rgb,rt->scene->light->bright_ratio)),diff_deg);

    double spec = pow(vec3_dot(view_vec, vec3_reflect(vec3_mul(light_vec, -1), normal)), rt->scene->light->factor->shininess) * rt->scene->light->bright_ratio * rt->scene->light->factor->ks;
    
    if(vec3_dot(view_vec, vec3_reflect(vec3_mul(light_vec, -1), normal)) < 0)
        spec = 0;
    if(is_shadow(rt->scene, nearest_obj, dir_vec))
    {
        diff = 0;
        spec = 0;
    }
    return color_calc(nearest_obj, amb + diff + spec);
}
