#ifndef MAINFILE
#define MAINFILE

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include <raylib.h>
#include <raymath.h>


// Colors
#define Purple0 CLITERAL(Color){  11, 0,  20, 255 }
#define Purple1 CLITERAL(Color){  20, 0,  38, 255 }
#define Purple2 CLITERAL(Color){  28, 0,  51, 255 }
#define Purple3 CLITERAL(Color){  43, 0,  79, 255 }
#define Purple4 CLITERAL(Color){  61, 0, 112, 255 }
#define Purple5 CLITERAL(Color){  84, 2, 153, 255 }
#define Purple6 CLITERAL(Color){ 103, 2, 190, 255 }
#define Purple7 CLITERAL(Color){ 117, 2, 214, 255 }
#define Purple8 CLITERAL(Color){ 129, 0, 237, 255 }
#define Purple9 CLITERAL(Color){ 139, 3, 252, 255 }

// Scenes
typedef enum {
    LogoScene = 0,
    MenuScene = 1,
    GameScene = 2,
    EndScene  = 3
} Scenes;


// Text ======================================================================================================================================
typedef struct {
	char    ThisText[64];
	Font    ThisTextFont;
	int     ThisTextFontSize;
	Vector2 ThisTextPosition;
	Color   ThisTextColor;
} GText;

GText CreateGText(char ThisText[64], char *TFont, int TFontSize, Vector2 TPosition, Color TColor);
void UpdateGText(GText *ThisGText, int LeftPlayer, Font font);
void DrawGText(GText *ThisGText);

// Progress Bar ==============================================================================================================================
typedef struct {
    Rectangle FirstBar;
	Rectangle SecondBar;
	Color FirstBarColor;
	Color SecondBarColor;
	int Time;
	float divideTimeAndWidth;
	float wait;
} ProgressBar;

ProgressBar CreateProgressBar ( float X, float Y, float SizeX, float SizeY, Color FirstBarColor, Color SecondBarColor, int Time ); 
void DrawProgressBar ( ProgressBar *ThisProgressBar );
bool UpdateProgressBar ( ProgressBar *ThisProgressBar );

// Button ====================================================================================================================================
typedef struct {
	char   *ButtonText;
	Color   TextColor;
	int     ButtonTextSize;
	Rectangle ButtonSize;
	Color   CurrentButtonColor;
	Color   ButtonNormalColor;
	Color   ButtonHoverColor;
	Color   ButtonPressColor;
	float   ButtonPressWaitTime;
	bool    ButtonPressCheck;
	Font    ButtonTextFont;
	Vector2 ButtonFontSize;
} Button;

Button CreateButton(char *Text, char *TextFont, int TextSize, float X, float Y, Color TextColor, Color NormalColor, Color HoverColor, Color PressColor); 
bool UpdateButton(Button *ThisButton, Vector2 MouseCursor); 
void DrawButton(Button *ThisButton);

// CheckBox ====================================================================================================================================
typedef struct {
	bool       Press;
	Rectangle  CheckButton;
	Rectangle  TickBox;
	Color      CheckButtonColor;
	Color      TickBoxCurrentColor;
	Color      TickBoxColorNormal;
	Color      TickBoxColorHover;
	Color      TickBoxActiveColor;
} CheckBox;


CheckBox CreateCheckBox(float x, float y, float SizeX, float SizeY, Color CheckboxButtonColor, Color TickBoxNormalColor, Color TickBoxColorHover, Color TickBoxActiveColor);
void DrawCheckbox(CheckBox *ThisCheckbox);
void UpdateCheckbox(CheckBox *ThisCheckbox, Vector2 MousePosition);


// Game Hello ===============================================================================
typedef struct {
	Rectangle Position;
	int       SpeedX;
	int       SpeedY;
	Color     BodyColor;
	bool      Active;
} Entity2D;

Entity2D CreatePaddle(Rectangle Position, int SpeedY, Color BodyColor);
void MovePaddle(Entity2D *ThisPaddle, int Key1, int Key2); 
void DrawPadle(Entity2D  *ThisPaddle);

Entity2D CreateBALL(Rectangle Position, int SpeedX, int SpeedY, Color BodyColor);
void MoveBALL(Entity2D *ThisBALL, Entity2D Player, Sound HitSound);
void DrawBALL(Entity2D *ThisBALL);
void BallOutside(Entity2D *ThisBALL, Sound TeleportSound);


Entity2D CreateBrick(Rectangle Position, Color BodyColor);
void CheckBrickCollision(Entity2D Bricks[], Entity2D *Ball, int Bricks0_countIndex, Sound HitSound, int *Score, int *Bricks0_Count_NextLevel); 

#endif
