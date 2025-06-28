extends Node2D

var SpeedX = 300.0
var SpeedY = 300.0

func _physics_process(delta: float) -> void:
	position.x += SpeedX * delta
	position.y += SpeedY * delta

func _process(delta: float) -> void:
	if not $music.playing:
		$music.play()

@onready var HitSound = $Hit
@onready var TeleportSound = $Teleport

func _on_ballarea_body_entered(body: Node) -> void:
	if body.is_in_group("bar"):
		SpeedY *= -1
		HitSound.play()
	elif body.is_in_group("player"):
		SpeedX *= -1
		HitSound.play()
	elif body.name == "LeftPoint":
		GLVAR.leftPoint += 1
		position.x = 576
		position.y = 351
		GLVAR.BallOut = true
		SpeedX *= -1
		TeleportSound.play()
	elif body.name == "RightPoint":
		GLVAR.RightPoint += 1
		position.x = 576
		position.y = 351
		GLVAR.BallOut = true
		SpeedX *= -1
		TeleportSound.play()

	if GLVAR.leftPoint == 10:
		GLVAR.Kazanan = "Left is Win!"
		get_tree().change_scene_to_file("res://Data/Scenes/end.tscn")
	elif GLVAR.RightPoint == 10:
		GLVAR.Kazanan = "Right is win"
		get_tree().change_scene_to_file("res://Data/Scenes/end.tscn")

func _on_ballarea_body_exited(body: Node2D) -> void:
	GLVAR.BallOut = false
