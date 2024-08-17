/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshidakazushi <yoshidakazushi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 23:32:07 by yoshidakazu       #+#    #+#             */
/*   Updated: 2024/08/17 18:36:22 by yoshidakazu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shadow.h"

// TODO　centerを使わないやり方にリファクタする
int phong_calc(t_scene *scene, t_vec3 screen_vec, t_object *nearest_obj)
{
    //ここの係数関係どうすれば、、？
    double ka=1.0;
    double kd=0.8;
    double ks=0.8;
    int shininess = 10;
    double t = calc_distance(nearest_obj, screen_vec, scene->camera);
    t_vec3 dir_vec = vec3_norm(vec3_sub(screen_vec, *scene->camera->view_point));
    t_vec3 intersection = vec3_add(*scene->camera->view_point, vec3_mul(dir_vec, t));
    //正規化による方向ベクトルの算出
    t_vec3 normal = vec3_norm(vec3_sub(intersection, *nearest_obj->center));
    t_vec3 light_vec = vec3_norm(vec3_sub(*scene->light->light_point, intersection));
    t_vec3 view_vec = vec3_norm(vec3_sub(*scene->camera->view_point, intersection));
    t_vec3 reflect_vec = vec3_reflect(vec3_mul(light_vec, -1), normal);

    double amb = scene->ambi_light->ratio * ka ;

    double diff = vec3_dot(normal, light_vec) * scene->light->bright_ratio * kd;
    if(vec3_dot(normal, light_vec)<0)
        diff = 0;

    double spec = pow(fmax(vec3_dot(view_vec, reflect_vec), 0.0), shininess) * scene->light->bright_ratio * ks;
    if(vec3_dot(view_vec, reflect_vec)<0)
        spec = 0;
    // if(is_shadow(scene, t, dir_vec))
    // {
    //     diff = 0;
    //     spec = 0;
    // }
    double brightness = amb + diff + spec; 
    int color_r = (int)(fmin(nearest_obj->rgb->r * brightness , 1.0) * 255);
    int color_g = (int)(fmin(nearest_obj->rgb->g * brightness , 1.0) * 255);
    int color_b = (int)(fmin(nearest_obj->rgb->b * brightness , 1.0) * 255);

    int color = (color_r << 16) | (color_g << 8) | color_b;
    return color;
}