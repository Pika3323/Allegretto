//
// Created by derek on 5/1/2017.
//

#pragma once


#include <allegro5/transformations.h>

struct Transform {
    float matrix[4][4];

    operator ALLEGRO_TRANSFORM() {
        ALLEGRO_TRANSFORM transform = ALLEGRO_TRANSFORM();
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; ++j) {
                transform.m[i][j] = matrix[i][j];
            }
        }
        return transform;
    }

    operator ALLEGRO_TRANSFORM*() {
        auto* transform = new ALLEGRO_TRANSFORM();
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; ++j) {
                transform->m[i][j] = matrix[i][j];
            }
        }
        return transform;
    }
};

