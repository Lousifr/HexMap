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

    Node3D* cameraRig = nullptr;
    void checkAndWrapHex(HexCell* hexCell);

public:
	HexMap();
	~HexMap();

    void _ready();
    void _process(float delta);

    void setNumCol(int p_numCol) { mapSize.x = p_numCol; generateHexMap(); }
    int getNumCol() { return mapSize.x; }

    void setNumRow(int p_numRow) { mapSize.y = p_numRow; generateHexMap(); }
    int getNumRow() { return mapSize.y; }

    void setCameraRig(NodePath p_nodePath) { cameraRig = Object::cast_to<Node3D>(get_node_internal(p_nodePath)); }
    NodePath getCameraRig() {
        if (cameraRig != nullptr) {
            return cameraRig->get_path();
        } else {
            return NodePath();
        }
    }

    void generateHexMap();

};

}

#endif // HEXMAP_H