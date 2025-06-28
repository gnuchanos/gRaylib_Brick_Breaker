from pyray import *
from enum import IntEnum


class GKey(IntEnum):
    NULL = 0
    APOSTROPHE = 39
    COMMA = 44
    MINUS = 45
    PERIOD = 46
    SLASH = 47
    ZERO = 48
    ONE = 49
    TWO = 50
    THREE = 51
    FOUR = 52
    FIVE = 53
    SIX = 54
    SEVEN = 55
    EIGHT = 56
    NINE = 57
    SEMICOLON = 59
    EQUAL = 61
    A = 65
    B = 66
    C = 67
    D = 68
    E = 69
    F = 70
    G = 71
    H = 72
    I = 73
    J = 74
    K = 75
    L = 76
    M = 77
    N = 78
    O = 79
    P = 80
    Q = 81
    R = 82
    S = 83
    T = 84
    U = 85
    V = 86
    W = 87
    X = 88
    Y = 89
    Z = 90
    LEFT_BRACKET = 91
    BACKSLASH = 92
    RIGHT_BRACKET = 93
    GRAVE = 96
    SPACE = 32
    ESCAPE = 256
    ENTER = 257
    TAB = 258
    BACKSPACE = 259
    INSERT = 260
    DELETE = 261
    RIGHT = 262
    LEFT = 263
    DOWN = 264
    UP = 265
    PAGE_UP = 266
    PAGE_DOWN = 267
    HOME = 268
    END = 269
    CAPS_LOCK = 280
    SCROLL_LOCK = 281
    NUM_LOCK = 282
    PRINT_SCREEN = 283
    PAUSE = 284
    F1 = 290
    F2 = 291
    F3 = 292
    F4 = 293
    F5 = 294
    F6 = 295
    F7 = 296
    F8 = 297
    F9 = 298
    F10 = 299
    F11 = 300
    F12 = 301
    LEFT_SHIFT = 340
    LEFT_CONTROL = 341
    LEFT_ALT = 342
    LEFT_SUPER = 343
    RIGHT_SHIFT = 344
    RIGHT_CONTROL = 345
    RIGHT_ALT = 346
    RIGHT_SUPER = 347
    KB_MENU = 348
    KP_0 = 320
    KP_1 = 321
    KP_2 = 322
    KP_3 = 323
    KP_4 = 324
    KP_5 = 325
    KP_6 = 326
    KP_7 = 327
    KP_8 = 328
    KP_9 = 329
    KP_DECIMAL = 330
    KP_DIVIDE = 331
    KP_MULTIPLY = 332
    KP_SUBTRACT = 333
    KP_ADD = 334
    KP_ENTER = 335
    KP_EQUAL = 336
    BACK = 4
    MENU = 5
    VOLUME_UP = 24
    VOLUME_DOWN = 25

class GFlags(IntEnum):
    VSYNC_HINT = 64
    FULLSCREEN_MODE = 2
    WINDOW_RESIZABLE = 4
    WINDOW_UNDECORATED = 8
    WINDOW_HIDDEN = 128
    WINDOW_MINIMIZED = 512
    WINDOW_MAXIMIZED = 1024
    WINDOW_UNFOCUSED = 2048
    WINDOW_TOPMOST = 4096
    WINDOW_ALWAYS_RUN = 256
    WINDOW_TRANSPARENT = 16
    WINDOW_HIGHDPI = 8192
    WINDOW_MOUSE_PASSTHROUGH = 16384
    BORDERLESS_WINDOWED_MODE = 32768
    MSAA_4X_HINT = 32
    INTERLACED_HINT = 65536

class GMouse(IntEnum):
    LEFT = 0
    RIGHT = 1
    MIDDLE = 2
    SIDE = 3
    EXTRA = 4
    FORWARD = 5
    BACK = 6

class CameraMode(IntEnum):
    CUSTOM = 0
    FREE = 1
    ORBITAL = 2
    FIRST_PERSON = 3
    THIRD_PERSON = 4

class CameraProjection(IntEnum):
    PERSPECTIVE = 0
    ORTHOGRAPHIC = 1

class GVector2:
    def __init__(self, x: float, y: float):
        self.X = x
        self.Y = y

class GVector3:
    def __init__(self, x: float, y: float, z: float):
        self.X = x
        self.Y = y
        self.Z = z

class GColor:
    def __init__(self, HexColor: str):
        hex_str = HexColor.lstrip('#')
        if len(hex_str) == 6:
            self.r = int(hex_str[0:2], 16)
            self.g = int(hex_str[2:4], 16)
            self.b = int(hex_str[4:6], 16)
            self.a = 255
        elif len(hex_str) == 8:
            self.r = int(hex_str[0:2], 16)
            self.g = int(hex_str[2:4], 16)
            self.b = int(hex_str[4:6], 16)
            self.a = int(hex_str[6:8], 16)
        else:
            raise ValueError("Hex color code must be in #RRGGBB or #RRGGBBAA format.")

    @property
    def Get(self):
        return (self.r, self.g, self.b, self.a)

class GFont:
    def __init__(self, FontPath: str):
        self.Font: Font = load_font(FontPath)
    
    @property
    def Get(self):
        return self.Font

    def Unload(self):
        unload_font(self.Font)


class GSound:
    def __init__(self, SoundFilePath: str):
        self.Sound: Sound = load_sound(SoundFilePath)

    def Volume(self, Volume: float):
        set_sound_volume(self.Sound, Volume)

    def Play(self):
        play_sound(self.Sound)

    def Unload(self):
        unload_sound(self.Sound)


class GMusic:
    def __init__(self, MusicFilePath: str):
        self.Music: Music = load_music_stream(MusicFilePath)
        play_music_stream(self.Music)

    def Volume(self, Volume: float):
        set_music_volume(self.Music, Volume)

    def UpdateStream(self):
        update_music_stream(self.Music)

    def Play(self):
        play_music_stream(self.Music)

    def Stop(self):
        stop_music_stream(self.Music)

    def Pause(self):
        pause_music_stream(self.Music)

    def Resume(self):
        resume_music_stream(self.Music)

    def Unload(self):
        unload_music_stream(self.Music)    
