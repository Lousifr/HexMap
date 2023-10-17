extends Node3D

@export var speed = 10

func _ready():
	pass

func _process(delta):
	var input_axis = Vector2(
		Input.get_axis("ui_right", "ui_left"),
		Input.get_axis("ui_down", "ui_up")
	).normalized()

	translate(Vector3(
		input_axis.x * speed * delta, 
		0,
		input_axis.y * speed * delta 
	))
