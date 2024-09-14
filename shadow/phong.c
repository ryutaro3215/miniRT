/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshidakazushi <yoshidakazushi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 23:32:07 by yoshidakazu       #+#    #+#             */
/*   Updated: 2024/09/14 17:30:33 by yoshidakazu      ###   ########.fr       */
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


// TODO　centerを使わないやり方にリファクタする
int phong_calc(t_rt *rt, t_vec3 dir_vec, t_object *nearest_obj)
{
	// t_vec3  dsc = vec3_mul(*rt->scene->camera->nr_vec, (double)rt->width / (2 * tan((float)rt->scene->camera->view_degree / 2)));
    // t_vec3 dir_vec = vec3_norm(vec3_add(screen_vec, dsc));
    t_vec3 intersection = vec3_add(*rt->scene->camera->view_point, vec3_mul(dir_vec, calc_distance(nearest_obj, dir_vec, rt->scene->camera->view_point)));
    t_vec3 normal;
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

    double diff = vec3_dot(normal, light_vec) * rt->scene->light->bright_ratio * rt->scene->light->factor->kd;
    if(vec3_dot(normal, light_vec) <= 0)
        diff = 0;

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
