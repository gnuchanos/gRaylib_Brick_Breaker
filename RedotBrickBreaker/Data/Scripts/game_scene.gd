extends Node2D

@onready var PointShow = $Panel/PointShow

func _ready() -> void:
	PointShow.text = "Left Player: " + str(GLVAR.leftPoint) + " | " + "Right Player: " + str(GLVAR.RightPoint)

func _process(delta: float) -> void:
	if GLVAR.BallOut:
		PointShow.text = "Left Player: " + str(GLVAR.leftPoint) + " | " + "Right Player: " + str(GLVAR.RightPoint)
