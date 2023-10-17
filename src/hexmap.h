#ifndef HEXMAP_H
#define HEXMAP_H

#include "hexcell.h"

#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/variant/node_path.hpp>

namespace godot {

class HexMap : public Node3D {
	GDCLASS(HexMap, Node3D)

protected:
	static void _bind_methods();

private:
    double hexSize { 1.0 };
    double hexCellWidth { hexSize * sqrt(3) };

	Vector2 mapSize = Vector2(64, 32);
	Array hexCells;

    NodePath cameraRigPath;

public:
	HexMap();
	~HexMap();

    void _ready();

    void setNumCol(int p_numCol) { mapSize.x = p_numCol; }
    int getNumCol() { return mapSize.x; }

    void setNumRow(int p_numRow) { mapSize.y = p_numRow; }
    int getNumRow() { return mapSize.y; }

    void setCameraRigPath(NodePath p_nodePath) { cameraRigPath = p_nodePath; }
    NodePath getCameraRigPath() const { return cameraRigPath; }

    void generateHexMap();

};

}

#endif // HEXMAP_H