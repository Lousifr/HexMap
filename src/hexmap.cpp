#include "hexmap.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

void HexMap::_bind_methods() {

    ClassDB::bind_method(D_METHOD("setNumCol", "p_numCol"), &HexMap::setNumCol);
    ClassDB::bind_method(D_METHOD("getNumCol"), &HexMap::getNumCol);  
    ADD_PROPERTY(PropertyInfo(Variant::INT, "num_col"), "setNumCol", "getNumCol");

    ClassDB::bind_method(D_METHOD("setNumRow", "p_numRow"), &HexMap::setNumRow);
    ClassDB::bind_method(D_METHOD("getNumRow"), &HexMap::getNumRow);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "num_row"), "setNumRow", "getNumRow");

    ClassDB::bind_method(D_METHOD("setCameraRig", "p_nodePath"), &HexMap::setCameraRig);
    ClassDB::bind_method(D_METHOD("getCameraRig"), &HexMap::getCameraRig);
    ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "cameraRig", PROPERTY_HINT_NODE_PATH_VALID_TYPES, "Node3D"), "setCameraRig", "getCameraRig");

    ClassDB::bind_method(D_METHOD("generateHexMap"), &HexMap::generateHexMap);

}

HexMap::HexMap() {
    
}

HexMap::~HexMap() {
    hexCells.clear();
}

void HexMap::_ready() {
    generateHexMap();
}

void HexMap::_process(float delta) {
    if (cameraRig != nullptr) {
        for (int q = 0; q < mapSize.x; q++) {
            Array column = hexCells[q];
            for (int r = 0; r < mapSize.y; r++) {
                Object* obj = column[r];
                HexCell* hexCell = Object::cast_to<HexCell>(obj);
                checkAndWrapHex(hexCell);
                
            }
        }
    }
}

void HexMap::generateHexMap() {
    hexCells.clear();
    for (int q = 0; q < mapSize.x; q++)
    {
        Array column;
        for (int r = 0; r < mapSize.y; r++)
        {
            HexCell* hexCell = memnew(HexCell);
            add_child(hexCell);
            hexCell->set_q(q);
            hexCell->set_r(r);
            hexCell->updateHex();
            column.append(hexCell);
        }
        hexCells.append(column);
    }
}

void HexMap::checkAndWrapHex(HexCell* hexCell) {

    // Check the distance between the tile and the camera in world coordinates (X-axis only)
    Vector3 tilePosition = hexCell->get_global_transform().origin;
    Vector3 cameraPosition = cameraRig->get_global_transform().origin;
    float distanceX = abs(tilePosition.x - cameraPosition.x);

    // Calculate how many map widths away the tile is from the camera along the X-axis
    float mapWidthsAwayX = distanceX / (hexCellWidth * mapSize.x);

    // If the tile is more than 0.5 map widths away from the camera along the X-axis, wrap it to the other side
    if (mapWidthsAwayX > 0.5) {

        // Calculate the new position of the tile to wrap it along the X-axis
        Vector3 wrappedPosition = tilePosition;
        if (tilePosition.x - cameraPosition.x > 0) {
            wrappedPosition.x -= hexCellWidth * mapSize.x; 
        } else {
            wrappedPosition.x += hexCellWidth * mapSize.x;
        }

        // Set the new position for the tile
        hexCell->set_global_transform(Transform3D(hexCell->get_global_transform().basis, wrappedPosition));

    }

}