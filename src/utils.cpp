#include "utils.h"

bool collidesWithPlatform(
    int platform_x, 
    int platform_y, 
    int entity_x, 
    int entity_y, 
    int platform_width, 
    int platform_height,
    int entity_width, 
    int entity_height,
    int entity_v_speed, 
    int entity_h_speed
) {
    if(platform_x < entity_x + entity_width + entity_h_speed && platform_x + platform_width > entity_x + entity_h_speed){
        if(platform_y < entity_y + entity_height - entity_v_speed && platform_y + platform_height > entity_y - entity_v_speed){
            return true;
        }
    }
    return false;
}
