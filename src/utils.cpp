#include "utils.h"
#include <iostream>

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

std::tuple<float, float> getIceSpeed(float hori_speed, float ice_speed, bool is_on_ice) {
    if(is_on_ice){
        
        if(ice_speed >= 0){
            if(hori_speed > 0){
                ice_speed = hori_speed;
            }
            if(ice_speed != 0){
                if(hori_speed == 0){
                    hori_speed = ice_speed;
                    ice_speed -= 0.1;
                    if(ice_speed < 0){
                        ice_speed = 0;
                    }
                }
                else{
                    hori_speed = ice_speed;
                    ice_speed -= 0.2;
                    if(ice_speed < 0){
                        ice_speed = 0;
                    }
                }
            }
        }
        if(ice_speed <= 0){
            if(hori_speed < 0){
                ice_speed = hori_speed;
            }
            if(ice_speed != 0){
                if(hori_speed == 0){
                    hori_speed = ice_speed;
                    ice_speed += 0.1;
                    if(ice_speed > 0){
                        ice_speed = 0;
                    }
                }
                else{
                    hori_speed = ice_speed;
                    ice_speed += 0.2;
                    if(ice_speed > 0){
                        ice_speed = 0;
                    }
                }
            }
        }
    }
    else{
        ice_speed = 0;
    }

    return std::make_tuple(hori_speed, ice_speed);
}

bool isEntityFarFromPlayer(
    int player_x, 
    int player_y, 
    int entity_x, 
    int entity_y, 
    int player_width, 
    int player_height,
    int entity_width, 
    int entity_height,
    int minimum_distance
) {
    if (entity_x + entity_width < player_x) { // Entity on the left of the player
        if (entity_y + entity_height < player_y) { // Entity above the player
            return distance(player_x, player_y, entity_x + entity_width, entity_y + entity_height) > minimum_distance;
        }
        else if (entity_y > player_y + player_height) { // Entity under the player
            return distance(player_x, player_y + player_height, entity_x + entity_width, entity_y) > minimum_distance;
        }
        else {
            return player_x - (entity_x + entity_width) > minimum_distance;
        }
    }
    else if (entity_x > player_x + player_width) { // Entity on the right of the player
        if (entity_y + entity_height < player_y) { // Entity above the player
            return distance(player_x + player_width, player_y, entity_x, entity_y + entity_height) > minimum_distance;
        }
        else if (entity_y > player_y + player_height) { // Entity under the player
            return distance(player_x + player_width, player_y + player_height, entity_x, entity_y) > minimum_distance;
        }
        else {
            return entity_x - (player_x + player_width) > minimum_distance;
        }
    }
    else {
        if (entity_y + entity_height < player_y) { // Entity above the player
            return player_y - (entity_y + entity_height) > minimum_distance;
        }
        else if (entity_y > player_y + player_height) { // Entity under the player
            return entity_y - (player_y + player_height) > minimum_distance;
        }
    }

    return false; // Collides
}

double distance(int x1, int y1, int x2, int y2) {
    return std::sqrt(std::pow((x2 - x1), 2) + std::pow((y2 - y1), 2));
}

std::tuple<int, int> getPlayerPositionAfterPlatformMovesHorizontally(
    int player_x, 
    int player_y, 
    int platform_x, 
    int platform_y, 
    int player_width, 
    int player_height,
    int platform_width,
    int horizontal_speed
) {
    if (
        (player_x < platform_x && player_x + player_width > platform_x) ||
        (player_x < platform_x + platform_width && platform_x + player_width > platform_x + platform_width) ||
        (player_x > platform_x && player_x + player_width < platform_x + platform_width)
    ) { // The player share a x position with the moving platform
        if (player_y + player_height == platform_y - 1) { // The player is on the platform
            return std::make_tuple(player_x + horizontal_speed, player_y);
        }
    }
    else {
        return std::make_tuple(player_x, player_y);
    }
}

int getPlayerHorizontalSpeedWithWind(int base_horizontal_speed, int wind_speed, int max_speed, int min_speed){
    int horizontal_speed = base_horizontal_speed;
    if (base_horizontal_speed + wind_speed > max_speed) {
        horizontal_speed = max_speed;
    }
    else if (base_horizontal_speed + wind_speed < min_speed) {
        horizontal_speed = min_speed;
    }
    else {
        horizontal_speed = base_horizontal_speed + wind_speed;
    }

    return horizontal_speed;
}