#ifndef TREE_GEN_H
#define TREE_GEN_H

#include <scene/3d/mesh_instance_3d.h>
#include <scene/resources/primitive_meshes.h>
#include "duomesh.h"
// Generator based on a script, like GDScript, C# or NativeScript.
// The script is expected to properly handle multithreading.
class TreeGen  : public DuoMesh  {
	GDCLASS(TreeGen, DuoMesh)
private:
	float order = 2;
	float une = 0.5;
	float sideAngleB = 0.5;
	PackedVector3Array sidangle = PackedVector3Array();
	Array sid = Array();
	Array sidL = Array();
	float rotation = 0;
	float distA = 2.0;
	float wor = 0.5;
	float top_radius = 1.0;
	float bottom_radius = 1.0;
	float height = 20.0;
	float width = 30.0;
	int radial_segments = 10;
	int rings = 0;
	float leafScale = 2.0;
	
	Array transforms;
protected:
	static void _bind_methods();
	void _create_mesh_array(Array &p_arr, Dictionary tr) const;
	
public:
	
	void set_order(const float p_order);
	float get_order() const;
	void set_une(const float p_une);
	float get_une() const;
	void set_sideAngleB(const float p_sideAngleB);
	float get_sideAngleB() const;
	void set_sidangle(const PackedVector3Array p_sidangleB);
	PackedVector3Array get_sidangle() const;
	void set_rotation(const float p_rotation);
	float get_rotation() const;
	void set_distA(const float p_distA);
	float get_distA() const;
	void set_wor(const float p_wor);
	float get_wor() const;
	void set_top_radius(const float p_radius);
	float get_top_radius() const;

	void set_bottom_radius(const float p_radius);
	float get_bottom_radius() const;

	void set_height(const float p_height);
	float get_height() const;

	void set_width(const float p_width);
	float get_width() const;

	void set_radial_segments(const int p_segments);
	int get_radial_segments() const;

	void set_rings(const int p_rings);
	int get_rings() const;
	
	void set_leafScale(const float p_leafScale);
	float get_leafScale() const;

	void set_transforms(const Array p_transforms);
	Array get_transforms();

	void updateParts ();
	Dictionary gen( float w,float h,Transform3D home) const;
    Dictionary addtreebranch(Dictionary inf) const;
	Dictionary createTree() const;

	TreeGen(){};
	
};

#endif // TREE_GEN_H
