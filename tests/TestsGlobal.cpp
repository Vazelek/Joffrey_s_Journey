#include "TestsGlobal.h"

void simulate(int seconds, MyScene* scene) {
    for (unsigned short int i = 0; i < seconds * FPS; i++) {
        scene->update();
    }
}