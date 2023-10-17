extends Node3D

var hexCellPrefab: PackedScene = preload("res://Scenes/HexCell.tscn")
var mapSize: Vector2 = Vector2(64, 32)
@export var camera: Node3D = null
var hexCellWidth: float = sqrt(3)
var hexCellArray = [[]]

func _ready():
	generateHexMap()

func _process(delta):
	for q in range(0, mapSize.x):
		for r in range(0, mapSize.y):
			checkAndWrapHex(hexCellArray[q][r])

func generateHexMap():
	# Clear the existing array in case this function is called again
	hexCellArray.clear()

	for q in range(0, mapSize.x):
		var columnArray: Array = []  # Create an array for each column
		for r in range(0, mapSize.y):
			var hexCell = hexCellPrefab.instantiate() 
			add_child(hexCell) # Instantiate a hexCell and add it as a child
			hexCell.elevation = 0.0
			hexCell.updateVisuals()
			hexCell.placeHex(q, r)
			checkAndWrapHex(hexCell)

			# Add the hexCell reference to the array for this column
			columnArray.append(hexCell)
		# Add the column array to the hexCellArray
		hexCellArray.append(columnArray)

func checkAndWrapHex(hexCell):
	# Check the distance between the tile and the camera in world coordinates (X-axis only)
	var tilePosition = hexCell.transform.origin
	var cameraPosition = camera.transform.origin
	var distanceX = abs(tilePosition.x - cameraPosition.x)

	# Calculate how many map widths away the tile is from the camera along the X-axis
	var mapWidthsAwayX = distanceX / (hexCellWidth * mapSize.x)

	# If the tile is more than 0.5 map widths away from the camera along the X-axis, wrap it to the other side
	if mapWidthsAwayX > 0.5:
		# Calculate the new position of the tile to wrap it along the X-axis
		var wrappedPosition = tilePosition
		if tilePosition.x - cameraPosition.x > 0:
			wrappedPosition.x -= hexCellWidth * mapSize.x
		else:
			wrappedPosition.x += hexCellWidth * mapSize.x

		# Set the new position for the tile
		hexCell.transform.origin.x = wrappedPosition.x
