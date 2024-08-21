/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshidakazushi <yoshidakazushi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 23:32:07 by yoshidakazu       #+#    #+#             */
/*   Updated: 2024/08/21 17:35:19 by yoshidakazu      ###   ########.fr       */
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
    t_vec3 dir_vec = vec3_norm(vec3_sub(screen_vec, *scene->camera->view_point));
    double t = calc_distance(nearest_obj, dir_vec, scene->camera->view_point);
    t_vec3 intersection = vec3_add(*scene->camera->view_point, vec3_mul(dir_vec, t));
    t_vec3 normal;
    //正規化による方向ベクトルの算出
    if(nearest_obj->type == SPHERE){
                normal = vec3_norm(vec3_sub(intersection, *nearest_obj->center));
    }
    if(nearest_obj->type == PLANE)
        normal = *nearest_obj->normal_vec;
    if(nearest_obj->type == CYLINDER)
    {
        normal = *nearest_obj->normal_vec;
        // normal = vec3_norm(vec3_sub(intersection, *nearest_obj->center));
        // t_vec3 cylinder_axis = vec3_norm(*nearest_obj->axic_vec); // 円柱の軸（通常は単位ベクトルとして定義）
        // t_vec3 intersection_to_center = vec3_sub(intersection, *nearest_obj->center);
        // t_vec3 projection_on_axis = vec3_mul(cylinder_axis, vec3_dot(intersection_to_center, cylinder_axis));
        // normal = vec3_norm(vec3_sub(intersection_to_center, projection_on_axis));
    }
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
    if(is_shadow(scene, t, dir_vec))
    {
        diff = 0;
        spec = 0;
    }
    // printf("amb:%f, diff:%f, spec:%f\n", amb, diff, spec);
    double brightness = amb + diff + spec; 
    int color_r = (int)(fmin(nearest_obj->rgb->r * brightness , 1.0) * 255);
    int color_g = (int)(fmin(nearest_obj->rgb->g * brightness , 1.0) * 255);
    int color_b = (int)(fmin(nearest_obj->rgb->b * brightness , 1.0) * 255);

    int color = (color_r << 16) | (color_g << 8) | color_b;
    return color;
}