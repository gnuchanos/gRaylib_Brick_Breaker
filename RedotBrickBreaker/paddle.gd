
extends Area2D

export var speed := 400.0

func _process(delta):
	var dir = 0
	if Input.is_action_pressed("ui_left"):
		dir -= 1
	if Input.is_action_pressed("ui_right"):
		dir += 1
	position.x += dir * speed * delta
	position.x = clamp(position.x, 32, 768 - 32)
