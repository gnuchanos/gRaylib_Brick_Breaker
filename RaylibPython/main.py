from GnuChanGE import *


class Paddle(GRectangle):
    def __init__(self, Position, SpeedXY, BColor):
        super().__init__(Position, SpeedXY, BColor)

    def Update(self, Key1: KeyboardKey, Key2: KeyboardKey, ScreenHeight: int):
        if (is_key_down(Key1) and self.Position.y > 0):
            self.Position.x -= self.SpeedY * get_frame_time()
        elif (is_key_down(Key2) and self.Position.y < ScreenHeight-self.Position.height):
            self.Position.x += self.SpeedY * get_frame_time()

    def Draw(self):
        draw_rectangle(int(self.Position.x), int(self.Position.y), int(self.Position.width), int(self.Position.height), self.BColor)


class BALL(GRectangle):
    def __init__(self, Position, SpeedXY, BColor):
        super().__init__(Position, SpeedXY, BColor)

        print("are you working here???")
        self.Score = 0
        self.SendUpdateSignaltoText = False

    def Update(self, ScreenWidth, ScreenHeight: int, Player: Paddle, HitSound: GSound, TeleportSound: GSound):
        self.Position.x += self.SpeedX * get_frame_time()
        self.Position.y += self.SpeedY * get_frame_time()

        if self.Position.y <= 0:
            self.SpeedY *= -1
            HitSound.Play()

        elif check_collision_recs(self.Position, Player.Position):
            if is_key_down(GKey.A):
                self.SpeedX = -abs(self.SpeedX)
            elif is_key_down(GKey.D):
                self.SpeedX = abs(self.SpeedX)

            self.SpeedY *= -1

            HitSound.Play()

        elif self.Position.x <= 0 or self.Position.x >= ScreenWidth-self.Position.width:
            self.SpeedX *= -1
            HitSound.Play()

        elif (self.Position.y >= ScreenHeight):
            self.Position.x = ScreenWidth/2-self.Position.width/2
            self.Position.y = ScreenHeight/2-self.Position.width/2
            self.SendUpdateSignaltoText = True
            TeleportSound.Play()
            
    def StopSignal(self):
        self.SendUpdateSignaltoText = False

    """
    if self.BALL.SendUpdateSignaltoText:
        self.Score.Update(f"Left Score: {self.BALL.RightPlayerScore} | Right Score: {self.BALL.LeftPlayerScore}")
    """

    def Draw(self):
        draw_rectangle(int(self.Position.x), int(self.Position.y), int(self.Position.width), int(self.Position.height), self.BColor)


class Scenes:
    def __init__(self):
        self.Logo = 0
        self.Menu = 1
        self.Game = 2
        self.End  = 3


class Game:
    def __init__(self, WindowWidth: int, WindowHeight: int, GameTitle: str):
        #set_config_flags()

        self.ScreenWidth  = WindowWidth
        self.ScreenHeight = WindowHeight
        self.GameTitle    = GameTitle

        init_window(self.ScreenWidth, self.ScreenHeight, self.GameTitle)
        init_audio_device()

        self.MouseCursor = GVector2(0, 0)
        self.Scenes = Scenes()
        self.CurrentScene = self.Scenes.Logo

        self.Timer = 2


        # Assets
        self.DefaultFont = GFont(FontPath="./Data/Fonts/FreeSans.ttf")
        self.StartButton = GButton("this is very long text", self.DefaultFont.Get, 25, GVector2(100, 100), GColor("#df9fff").Get, GColor("#2b0040").Get, GColor("#6a009f").Get, GColor("#b520ff").Get)


        # Paddles
        self.Player = Paddle(Rectangle(0, self.ScreenHeight-60, 250, 50), GVector2(0, 300), GColor("#b520ff").Get)
        self.Player.Position.x = self.ScreenWidth/2-self.Player.Position.width/2

        # Ball
        self.BALL = BALL(Rectangle(self.ScreenWidth/2-25, self.ScreenHeight/2-25, 50, 50), GVector2(-300, -300), GColor("#df9fff").Get)

        # Bricks
        self.Bricks: Entity = []
        self.Brick0_SteapX = 110
        self.Brick0_SteapY =   5
        self.Bricks0_currentPositionX = 77
        self.Bricks0_currentPositionY = 50
        self.Bricks0_index = 0

        for i in range(7):
            self.Bricks0_currentPositionX = 77
            self.Bricks0_currentPositionY += 25+self.Brick0_SteapY

            for j in range(10):
                self.Bricks0_currentPositionX += self.Brick0_SteapX
                self.Bricks[j] = Paddle(Rectangle(self.Bricks0_currentPositionX, self.Bricks0_currentPositionY, 100, 25), GVector2(0, 0), BLUE)

        self.Bricks0_count = len(self.Bricks)


        # Sounds
        self.HitSound = GSound("./Data/Sound/hit.ogg")
        self.HitSound.Volume(0.3)

        self.TeleportSound = GSound("./Data/Sound/teleport.ogg")
        self.TeleportSound.Volume(0.3)

        self.Music = GMusic("./Data/Sound/music.ogg")
        self.Music.Volume(0.1)
        # Assets


        # Score Text
        self.Score = GText(f"Left Score: {self.BALL.Score}", self.DefaultFont.Get, 60, GVector2(0, 10), GColor("#6a009f").Get)
        self.Score.CenterXPosition(self.ScreenWidth)


        # Winner Text
        self.Winner = GText("uWu", self.DefaultFont.Get, 60, GVector2(0, 0), GColor("#b520ff").Get)
        self.Winner.CenterYPosition(self.ScreenHeight)
        self.Winner.CenterXPosition(self.ScreenWidth)


        set_target_fps(60)
        while not window_should_close():
            clear_background(GColor("#43055f").Get)
            self.MouseCursor = get_mouse_position()
            self.Update()
            begin_drawing()
            self.Draw2D()
            draw_fps(10, 10)
            end_drawing()
      
        # Unload Everything Here before close game
        self.DefaultFont.Unload()
        self.HitSound.Unload()
        self.Music.Unload()

        close_audio_device()
        close_window()


    def Update(self):
        if (self.CurrentScene == self.Scenes.Logo):
            if (self.Timer > 0):
                self.Timer -= get_frame_time()
            else:
                self.Timer = 2
                self.CurrentScene = self.Scenes.Menu

        elif (self.CurrentScene == self.Scenes.Menu):
            if (self.StartButton.Update(MouseCursor=self.MouseCursor)):
                self.CurrentScene = self.Scenes.Game

        elif (self.CurrentScene == self.Scenes.Game):

            # Paddle
            self.Player.Update(Key1=GKey.A, Key2=GKey.D, ScreenHeight=self.ScreenHeight)

            # BALL
            self.BALL.Update(self.ScreenWidth, self.ScreenHeight, self.Player, self.HitSound, self.TeleportSound)
            if self.BALL.SendUpdateSignaltoText:
                self.Score.Update(f"Left Score: {self.BALL.Score}")
            self.BALL.StopSignal()

            # Music
            self.Music.UpdateStream()
            
        elif (self.CurrentScene == self.Scenes.End):
            pass

    def Draw2D(self):
        if (self.CurrentScene == self.Scenes.Logo):
            pass

        elif (self.CurrentScene == self.Scenes.Menu):
            self.StartButton.Draw

        elif (self.CurrentScene == self.Scenes.Game):
            # Draw Score
            self.Score.Draw()
            
            # Draw Paddles 
            self.Player.Draw()

            #Draw Ball
            self.BALL.Draw()

        elif (self.CurrentScene == self.Scenes.End):
            self.Winner.Draw()


if __name__ == "__main__":
    gc = Game(1600, 900, "UwU")

