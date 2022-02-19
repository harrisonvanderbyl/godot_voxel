#ifndef FLOWER_GEN_H
#define FLOWER_GEN_H

#include <core/resource.h>
#include <scene/3d/mesh_instance.h>
#include <scene/resources/primitive_meshes.h>
// Generator that creates a lower from inputed parameters
class FlowerGen  : public PrimitiveMesh  {
	GDCLASS(FlowerGen, PrimitiveMesh)
private:
	int petals = 5;
	float petal_width = 0.5;
	float petal_height = 0.5;
	Vector3 petal_curve = Vector3(0, 0, 0);
	Vector2 petal_angle = Vector2(0,1);
	int petal_rings = 10;
	float petal_scale = 1.0;
	Vector2 petal_segments = Vector2(3,3);
	

	
protected:
	static void _bind_methods();
	virtual void _create_mesh_array(Array &p_arr) const;
	
public:
	void create_flower(Array &p_arr, Array transforms) const;
	void set_petals(const int p_petals);
	int get_petals() const;
	void set_petal_width(const float p_petal_width);
	float get_petal_width() const;
	void set_petal_height(const float p_petal_height);
	float get_petal_height() const;
	void set_petal_curve(const Vector3 p_petal_curve);
	Vector3 get_petal_curve() const;
	void set_petal_angle(const Vector2 p_petal_angle);
	Vector2 get_petal_angle() const;
	void set_petal_rings(const int p_petal_rings);
	int get_petal_rings() const;
	void set_petal_scale(const float p_petal_scale);
	float get_petal_scale() const;
	void set_petal_segments(const Vector2 p_petal_segments);
	Vector2 get_petal_segments() const;



	FlowerGen(){};
	
};

#endif // FLOWER_GEN_H
