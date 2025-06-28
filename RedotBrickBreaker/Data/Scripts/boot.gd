extends Control

var timer: float = 2

func _process(delta: float) -> void:
	if timer > 0:
		timer -= delta
	else:
		timer = 2
		get_tree().change_scene_to_file("res://Data/Scenes/main.tscn")
