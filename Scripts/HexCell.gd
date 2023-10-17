extends Node3D

@export var hexSize: float = 1.0
@export var matOcean: StandardMaterial3D = null
@export var matGrass: StandardMaterial3D = null
@onready var hexMesh = $HexMesh

var axial: Vector2
var cube: Vector3
var worldPosition: Vector3

var elevation: float = 0

func axialToCube(axial: Vector2) -> Vector3:
	var x = axial.x
	var z = axial.y
	var y = -x - z
	return Vector3(x, y, z)

func cubeToWorld(cube: Vector3) -> Vector3:
	var x = hexSize * sqrt(3) * (cube.x + cube.z / 2)
	var y = 0
	var z = hexSize * 3/2 * cube.z
	return Vector3(x, y, z)

func placeHex(q, r):
	axial = Vector2(q, r)
	cube = axialToCube(axial)
	worldPosition = cubeToWorld(cube)
	transform.origin = worldPosition

func updateVisuals():
	if elevation <= 0.0:
		# Set mesh material to matOcean
		hexMesh.set_surface_override_material(0, matOcean)
	else:
		# Set mesh material to matGrass
		hexMesh.set_surface_override_material(0, matGrass)
