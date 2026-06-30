#pragma once

#include"../libs/includes.h"

struct vector2 { float x, y; };
struct vector3 { float x, y, z; };


struct view_matrix_t {
    float m[4][4];

    float* operator[](int i) {
        return m[i];
    }

    const float* operator[](int i) const {
        return m[i];
    }
};

struct Entity {
    vector3 position;        // 0x00
    char pad1[0x3C - 0x0C];
    vector3 angles;          // 0x3C (x = yaw, y = pitch)
    char pad2[0x178 - 0x48];
    int health;           // 0x178
    char pad3[0x274 - 0x17C];
    char name[16];        // 0x274
    char pad4[0x378 - 0x284];
    char team[4];         // 0x378
};

struct WorldSnapshot {
    std::vector<Entity> entities;
    Entity localPlayer;
    view_matrix_t viewMatrix;
};