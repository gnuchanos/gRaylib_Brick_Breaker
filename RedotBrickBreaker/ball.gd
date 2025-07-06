
extends Area2D

var velocity = Vector2(200, -200)

func _physics_process(delta):
	position += velocity * delta

	if position.x <= 0 or position.x >= 800:
		velocity.x *= -1
	if position.y <= 0:
		velocity.y *= -1
	if position.y >= 600:
		reset()

func _on_area_entered(area):
	if area.is_in_group("brick"):
		area.queue_free()
		velocity.y *= -1
	elif area.name == "Paddle":
		velocity.y *= -1

func reset():
	position = Vector2(400, 300)
	velocity = Vector2(200, -200)
