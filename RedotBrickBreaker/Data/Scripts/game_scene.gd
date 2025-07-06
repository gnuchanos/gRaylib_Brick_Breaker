extends Node2D

@onready var PointShow = $bg/PointShow

func _ready() -> void:
	PointShow.text = "Player Point: " + str(GLVAR.Point)

func _process(delta: float) -> void:
	if GLVAR.BallOut:
		PointShow.text = "Player Point: " + str(GLVAR.Point) 
