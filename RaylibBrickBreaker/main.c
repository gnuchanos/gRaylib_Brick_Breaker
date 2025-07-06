#include "main.h"
#include <raylib.h>
#include <stdio.h>

int main(void) {
    const int screenWidth = 1600;
    const int screenHeight = 900;
    const char GameTitle[] = "Game Title UwU";
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(screenWidth, screenHeight, GameTitle);
    InitAudioDevice();

    Scenes CurrentScene = LogoScene;
    float LogoTimer    = 2;

    Texture2D BG = LoadTexture("./Data/Images/bg.png");
	BG.height = screenHeight; BG.width  = screenWidth;	

	// Buttons
	Button StartButton = CreateButton( "Start Game", "./Data/Fonts/FreeSans.ttf", 25, 50, 100, WHITE, BLACK, GRAY, YELLOW );

	// Paddles
	Entity2D Player = CreatePaddle((Rectangle){(float)screenWidth/2-125, (float)screenHeight-60, 250, 50}, 600, RED);

	// Ball
	Entity2D ThisBALL = CreateBALL((Rectangle){(float)screenWidth/2-25, (float)screenHeight/2-25, 50, 50}, 300, 300, YELLOW);

	// Bricks
	Entity2D Bricks0[88];
	int      Brick0_SteapX = 110;
	int      Brick0_SteapY = 5;
	int      Bricks0_currentPositionX = 77;
	int      Bricks0_currentPositionY = 50;
	int      Bricks0_index = 0;
	for (int i = 0; i < 8; i++) {
		Bricks0_currentPositionX = 77;
		Bricks0_currentPositionY += 25+Brick0_SteapY;

		for (int j = 0; j < 11; j++) {
			Bricks0_currentPositionX += Brick0_SteapX;
			Bricks0[Bricks0_index++] = CreateBrick((Rectangle){Bricks0_currentPositionX, Bricks0_currentPositionY, 100, 25}, BLUE);
			printf("		:| %d \n", Brick0_SteapY);
		}
	}
	int Bricks0_count = sizeof(Bricks0) / sizeof(Bricks0[0]);
	int Bricks0_Count_NextLevel = sizeof(Bricks0) / sizeof(Bricks0[0]);

	// Score
	int PlayerScore = 0;
	GText ScoreText = CreateGText("", "./Data/Fonts/FreeSans.ttf", 60, (Vector2){0, 0}, WHITE);

	int TextSizeX = MeasureTextEx(ScoreText.ThisTextFont, ScoreText.ThisText, ScoreText.ThisTextFontSize, 0).x;
	ScoreText.ThisTextPosition.x = (float)screenWidth/2-(float)TextSizeX/2;

	// Sound
	Sound HitSound = LoadSound("./Data/Sound/hit.ogg");
	Sound Teleport = LoadSound("./Data/Sound/teleport.ogg");

	// Music
	Music GMusic = LoadMusicStream("./Data/Sound/music.ogg");
	PlayMusicStream(GMusic);

	// multiple unload arrays
	Sound AllSounds[] = { HitSound, Teleport };
	int allSoundCount = sizeof(AllSounds) / sizeof(AllSounds[0]);

	Font AllFonts[] = { StartButton.ButtonTextFont, ScoreText.ThisTextFont };
	int allFontsCount = sizeof(AllFonts) / sizeof(AllFonts[0]);





    bool ShowMouse = false;
	Vector2 MouseCursor = {0, 0};
    SetTargetFPS(60);
    while (!WindowShouldClose()) {	
    
        // Show Cursor or Hide
        if (IsKeyPressed(KEY_ESCAPE) && ShowMouse) {
            ShowMouse = false;
            DisableCursor();
        } else if (IsKeyPressed(KEY_ESCAPE) && !ShowMouse) {
            ShowMouse = true;
            EnableCursor(); }
        // Show Cursor or Hide

        if (CurrentScene == LogoScene) {
            //Logo time
            if (LogoTimer > 0) {
                LogoTimer -= GetFrameTime();
            } else {
                CurrentScene = MenuScene; }


        } else if (CurrentScene == MenuScene) {
			MouseCursor = GetMousePosition();
			
			// Start Game Button	
			if (UpdateButton(&StartButton, MouseCursor)) {
				CurrentScene = GameScene;
			}


        } else if (CurrentScene == GameScene) {
			// Move Paddle
			MovePaddle(&Player, KEY_A, KEY_D);

			// Move Ball
			MoveBALL(&ThisBALL, Player, HitSound);

			// Check Ball
			BallOutside(&ThisBALL, Teleport);
			
			// Update Score Text
			UpdateGText(&ScoreText, PlayerScore, ScoreText.ThisTextFont);

			// Check Score
			CheckBrickCollision(Bricks0, &ThisBALL, Bricks0_count, HitSound, &PlayerScore, &Bricks0_Count_NextLevel);
			if (Bricks0_Count_NextLevel == 0) {
				CurrentScene = EndScene;
			}

			// Music
			UpdateMusicStream(GMusic);		
		} else if (CurrentScene == EndScene) {
			// Reset Scene and Score
			if (IsKeyPressed(KEY_R)) {
				CurrentScene = MenuScene;
				
				PlayerScore = 0;
				Player.Position = (Rectangle){10, (float)screenHeight/2-125, 50, 250};
			}
        }
        BeginDrawing();
            ClearBackground(Purple0);
            if (CurrentScene == LogoScene) {
				DrawTexture(BG, 0, 0, WHITE);
            } else if (CurrentScene == MenuScene) {
				// Draw Button and Background Color
				DrawRectangleRec((Rectangle){0, 0, screenWidth, screenHeight}, Purple3);
				DrawButton(&StartButton);
            } else if (CurrentScene == GameScene) {
				// Draw Paddles, balls and Background color
				DrawRectangleRec((Rectangle){0, 0, screenWidth, screenHeight}, Purple2);

				DrawPadle(&Player);
				DrawBALL(&ThisBALL);

				for (int i = 0; i < Bricks0_count; i++) {
					if (Bricks0[i].Active) {
						DrawRectangleRec(Bricks0[i].Position, Bricks0[i].BodyColor);
					}
				}

				DrawGText(&ScoreText);
            } else if (CurrentScene == EndScene) {
				// Draw Winner on the screen
               DrawText("Right is Win", screenWidth/2-200, screenHeight/2, 80, WHITE);
            }
		DrawFPS(10, 10);
        EndDrawing(); 
    }

        CloseAudioDevice();

		UnloadTexture(BG);
		for (int i = 0; i < allFontsCount; i++) { UnloadFont(AllFonts[i]); }
		for (int i = 0; i < allSoundCount; i++) { UnloadSound(AllSounds[i]); }

    CloseWindow();
    return 0; }
