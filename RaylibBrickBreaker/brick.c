#include "main.h"
#include <raylib.h>


Entity2D CreateBrick(Rectangle Position, Color BodyColor) {
	Entity2D ThisBALL = {
		.Position  = Position,
		.BodyColor = BodyColor,
		.Active    = true };
	return ThisBALL;
}

void CheckBrickCollision(Entity2D Bricks[], Entity2D *Ball, int Bricks0_countIndex, Sound HitSound, int *Score, int *Bricks0_Count_NextLevel) {
    for (int i = 0; i < Bricks0_countIndex; i++) {
        if (!Bricks[i].Active) {
			continue;
		}

        if (CheckCollisionRecs(Ball->Position, Bricks[i].Position)) {
            Bricks[i].Active = false;
            Ball->SpeedY *= -1;
			Ball->SpeedX *= -1;
			PlaySound(HitSound);
			*Score += GetRandomValue(10, 1000);
			if (*Bricks0_Count_NextLevel > 0) {
				*Bricks0_Count_NextLevel -= 1;
			}
            break;
        }
    }
}


