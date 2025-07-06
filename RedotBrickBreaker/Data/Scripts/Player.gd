extends Area2D

const SPEED = 600.0
var velocity = Vector2.ZERO
var screen_width

func _ready() -> void:
	screen_width = get_viewport().get_visible_rect().size.x

func _process(delta):
	var direction = 0
	if Input.is_action_pressed("d"):
		direction += 1
	if Input.is_action_pressed("a"):
		direction -= 1

	velocity.x = direction * SPEED
	position += velocity * delta

	position.x = clamp(position.x, 110, screen_width - 110)

func _on_body_entered(body: Node2D) -> void:
	if body.name == "BALL":
		GLVAR.SpeedY *= -1
