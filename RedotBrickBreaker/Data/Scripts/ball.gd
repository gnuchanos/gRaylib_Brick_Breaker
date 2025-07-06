extends Node2D



func _physics_process(delta: float) -> void:
	position.x += GLVAR.SpeedX * delta
	position.y += GLVAR.SpeedY * delta

func _process(delta: float) -> void:
	if not $music.playing:
		$music.play()

@onready var HitSound = $Hit
@onready var TeleportSound = $Teleport

func _on_ballarea_body_entered(body: Node) -> void:
	if body.is_in_group("bar"):
		GLVAR.SpeedX *= -1
		HitSound.play()

	elif body.name == "Player" or body.name == "wallTop":
		GLVAR.SpeedY *= -1
		HitSound.play()

	if GLVAR.Point == 10:
		GLVAR.PointString = "Player Point: " + str(GLVAR.Point)
		get_tree().change_scene_to_file("res://Data/Scenes/end.tscn")


func _on_ballarea_body_exited(body: Node2D) -> void:
	GLVAR.BallOut = false
