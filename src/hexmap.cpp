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

    ClassDB::bind_method(D_METHOD("setCameraRigPath", "p_nodePath"), &HexMap::setCameraRigPath);
    ClassDB::bind_method(D_METHOD("getCameraRigPath"), &HexMap::getCameraRigPath);
    ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "cameraRigPath", PROPERTY_HINT_NODE_PATH_VALID_TYPES, "Node3D"), "setCameraRigPath", "getCameraRigPath");

}

HexMap::HexMap() {
    
}

HexMap::~HexMap() {
    hexCells.clear();
}

void HexMap::_ready() {
    generateHexMap();
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
            hexCell->placeHex();
            column.append(hexCell);
        }
        hexCells.append(column);
    }
}