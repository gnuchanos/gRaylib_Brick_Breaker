#include "main.h"
#include <raylib.h>


Entity2D CreatePaddle(Rectangle Position, int SpeedY, Color BodyColor) {
	Entity2D ThisPaddle = {
		.Position   = Position,
		.SpeedX     = 0,
		.SpeedY     = SpeedY,
		.BodyColor  = BodyColor,
		.Active     = true };
	return ThisPaddle;
}

void MovePaddle(Entity2D *ThisPaddle, int Key1, int Key2) {
	if (IsKeyDown(Key1) && ThisPaddle->Position.x > 0) {
		ThisPaddle->Position.x -= ThisPaddle->SpeedY * GetFrameTime();
	} else if (IsKeyDown(Key2) && ThisPaddle->Position.x < GetScreenWidth()-ThisPaddle->Position.width) {
		ThisPaddle->Position.x += ThisPaddle->SpeedY * GetFrameTime();
	}
}


void DrawPadle(Entity2D *ThisPaddle) {
	DrawRectangleRec(ThisPaddle->Position, ThisPaddle->BodyColor);
}
