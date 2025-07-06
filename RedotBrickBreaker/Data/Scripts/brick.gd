extends Area2D

@onready var HitSound = $Hit
var hit = false
func _on_body_entered(body: Node2D) -> void:
	if body.name == "BALL":
		GLVAR.SpeedY *= -1
		GLVAR.SpeedX *= -1
		HitSound.play()
		hit = true


func _process(delta: float) -> void:
	if not HitSound.playing and hit:
		queue_free()
