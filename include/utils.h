#ifndef UTILS_H
#define UTILS_H

#include <tuple>
#include <QVector>
#include <iostream>
#include <cmath>

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
);

std::tuple<float, float> getIceSpeed(float hori_speed, float ice_speed, bool is_on_ice);

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
);

double distance(int x1, int y1, int x2, int y2);

std::tuple<int, int> getPlayerPositionAfterPlatformMovesHorizontally(
    int player_x, 
    int player_y, 
    int platform_x, 
    int platform_y, 
    int player_width, 
    int player_height,
    int platform_width,
    int horizontal_speed
);

int getHorizontalSpeedWithWind(int base_horizontal_speed, int wind_speed);

#endif