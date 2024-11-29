
#define S_H 600       // 屏幕高度
#define S_W 800       // 屏幕宽度
#define TILE_SIZE 30  // 墙体单元大小
#define fov_rd (M_PI / 3)  // 60度的视野角度（弧度制）

#include <stdio.h>
#include <math.h>
#include <math.h>
#include <math.h>
int main() {
    double distance = TILE_SIZE / S_H * S_W / 2 * tan(fov_rd / 2);
    printf("玩家到墙体的距离为: %.2f\n", distance);
    return 0;
}
