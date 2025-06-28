from pyray import *
from .Settings import *

class GRectangle:
    def __init__(self, Position: Rectangle, SpeedXY: GVector2, BColor: Color):
        self.Position = Position
        self.SpeedX = SpeedXY.X
        self.SpeedY = SpeedXY.Y
        self.BColor = BColor