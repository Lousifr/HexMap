#ifndef HEXCELL_H
#define HEXCELL_H

#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/mesh_instance3d.hpp>

namespace godot {

class HexCell : public Node3D {
	GDCLASS(HexCell, Node3D)

protected:
	static void _bind_methods() {
		ClassDB::bind_method(D_METHOD("updateHex"), &HexCell::updateHex);
	}

private:
	ResourceLoader* loader = ResourceLoader::get_singleton();

	Ref<PackedScene> meshScene = loader->load("res://Scenes/HexMesh.tscn");
	MeshInstance3D* meshInstance;

	// TODO: Load hex materials

	float hexSize { 1.0 };
	float elevation { 0.0 };
	int q;
	int r;

	Vector3 axialToCube(Vector2 axial) {
		float x { axial.x };
		float z { axial.y };
		float y { -x - z };
		return Vector3(x, y, z);
	}

	Vector3 cubeToWorld(Vector3 cube) {
		float x = hexSize * sqrt(3) * (cube.x + cube.z / 2);
		float y = 0; 
		float z = hexSize * 3/2 * cube.z;
		return Vector3(x, y, z);
	}

public:
	HexCell() {}
	~HexCell() {

	}

	void _init() {
		
	}

	void _ready() {
		meshInstance = cast_to<MeshInstance3D>(meshScene->instantiate());
		add_child(meshInstance);
	}

	void set_hexSize(float p_hexSize) { hexSize = p_hexSize; }
	int get_hexSize() { return hexSize; }

	void set_elevation(float p_elevation) { elevation = p_elevation; }
	float get_elevation() { return elevation; }

	void set_q(int pQ) { q = pQ; }
	int get_q() { return q; }

	void set_r(int pR) { r = pR; }
	int get_r() { return r; }

	void updateHex() {
		Vector2 axial = Vector2(q, r);
		Vector3 cube = axialToCube(axial);
		Vector3 worldPosition = cubeToWorld(cube);

		// Set hex elevation / material

		set_global_transform(Transform3D(Basis(), worldPosition));
	}
	
};

}

#endif // HEXCELL_H