#include "main.h"
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>


Entity2D CreateBALL(Rectangle Position, int SpeedX, int SpeedY, Color BodyColor) {
	Entity2D ThisBALL = {
		.Position  = Position,
		.SpeedX    = SpeedX,
		.SpeedY    = SpeedY,
		.BodyColor = BodyColor,
		.Active    = true };
	return ThisBALL;
}

void MoveBALL(Entity2D *ThisBALL, Entity2D Player, Sound HitSound) {
	ThisBALL->Position.x += ThisBALL->SpeedX * GetFrameTime();
	ThisBALL->Position.y += ThisBALL->SpeedY * GetFrameTime();
	
	if (ThisBALL->Position.x <= 0 || ThisBALL->Position.x >= GetScreenWidth()-ThisBALL->Position.width) {
	 	ThisBALL->SpeedX *= -1;
	 	PlaySound(HitSound);

	} else if (ThisBALL->Position.y <= 0) {
	 	ThisBALL->SpeedY *= -1;
	 	PlaySound(HitSound);

	} else if (CheckCollisionRecs(ThisBALL->Position, Player.Position)) {
		int _Speed = ThisBALL->SpeedX;
		if (IsKeyDown(KEY_A)) {
			ThisBALL->SpeedX = -abs(_Speed);
			printf("D: %d \n", ThisBALL->SpeedX );

		} else if (IsKeyDown(KEY_D)) {
			ThisBALL->SpeedX = +abs(_Speed);
			printf("A: %d \n", ThisBALL->SpeedX );
		}

		ThisBALL->SpeedY *= -1;
		PlaySound(HitSound);
	}
}

void BallOutside(Entity2D *ThisBALL, Sound TeleportSound) {
	if (ThisBALL->Position.y > GetScreenHeight()) {
		ThisBALL->Position.x = (float)GetScreenWidth()/2-ThisBALL->Position.width/2;
		ThisBALL->Position.y = (float)GetScreenHeight()/2-ThisBALL->Position.height/2;
		ThisBALL->SpeedY *= -1;
		PlaySound(TeleportSound);
	}
}

void DrawBALL(Entity2D *ThisBALL) {
	DrawRectangle(ThisBALL->Position.x, ThisBALL->Position.y, ThisBALL->Position.width, ThisBALL->Position.height, ThisBALL->BodyColor);
}
