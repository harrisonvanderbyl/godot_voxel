#include "voxel_gen_json.h"
#include "../constants/voxel_string_names.h"
#include "../util/godot/funcs.h"
#include "../constants/voxel_string_names.h"
#include "../storage/voxel_buffer_gd.h"
#include "../util/godot/funcs.h"
#include "core/math/random_number_generator.h"

#include "./filedata/heights.h"
#include "./filedata/heights01.h"
#include "./filedata/heights10.h"
#include "./filedata/heights11.h"
VoxelGenJson::VoxelGenJson() {

}
zylann::voxel::VoxelGenerator::Result VoxelGenJson::generate_block(zylann::voxel::VoxelGenerator::VoxelQueryData &input) {
	zylann::voxel ::VoxelGenerator::Result result;
	VParameters params;
	{
		RWLockRead rlock(_parameters_lock);
		params = _parameters;
	}
	// Create a temporary wrapper so Godot can pass it to scripts
	Ref<zylann::voxel ::gd::VoxelBuffer> buffer_wrapper;
	buffer_wrapper.instantiate();
	buffer_wrapper->get_buffer().copy_format(input.voxel_buffer);
	buffer_wrapper->get_buffer().create(input.voxel_buffer.get_size());
	
	// The wrapper is discarded
	
	
	int xs = buffer_wrapper->get_buffer().get_size().x;
	int ys = buffer_wrapper->get_buffer().get_size().y;
	int zs = buffer_wrapper->get_buffer().get_size().z;
		
		for(int i = 0; i < xs; i++){
			for(int j = 0; j < ys; j++){
				for(int k = 0; k < zs; k++){
					int cux = input.origin_in_voxels.z + k*(1<<input.lod);
					int cuy = input.origin_in_voxels.y + j*(1<<input.lod);
					int cuz = input.origin_in_voxels.x + i*(1<<input.lod);
					if(cux < 0 || cux >= 4000 || cuy < 0 || cuy >= 4000 ){
						buffer_wrapper->get_buffer().set_voxel_f(1.0,i,j,k,1);
						
					}else{
					float height = 0.0;
					
					if(cux < 2000 && cuz < 2000){
						height = H00::H00[cux][cuz];
					}else if(cux < 2000 && cuz >= 2000){
						height = H10::H10[cux][cuz-2000];
					}else if(cux >= 2000 && cuz < 2000){
						height = H01::H01[cux-2000][cuz];
					}else if(cux >= 2000 && cuz >= 2000){
						height = H11::H11[cux-2000][cuz-2000];
					}

					
					buffer_wrapper->get_buffer().set_voxel_f(params.hsc*(float(cuy)-height),i,j,k,1);
					
					}
					
					}
					
				}}
	
	;
	buffer_wrapper->get_buffer().move_to(input.voxel_buffer);

	// We may expose this to scripts the day it actually gets used
	// if (ret.get_type() == Variant::DICTIONARY) {
	// 	Dictionary d = ret;
	// 	result.max_lod_hint = d.get("max_lod_hint", false);
	// }

	return result;
}

void VoxelGenJson::set_scale(int scale) {
	RWLockWrite wlock(_parameters_lock);
	_parameters.scale = scale;
}
int VoxelGenJson::get_scale() {
	RWLockRead rlock(_parameters_lock);
	return _parameters.scale;
}
void VoxelGenJson::set_hsc(float hsc) {
	RWLockWrite wlock(_parameters_lock);
	_parameters.hsc = hsc;
}
float VoxelGenJson::get_hsc() {
	RWLockRead rlock(_parameters_lock);
	return _parameters.hsc;
}
int VoxelGenJson::get_used_channels_mask() const {
	
	return 1 << 1;
}

void VoxelGenJson::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_scale", "scale"), &VoxelGenJson::set_scale);
	ClassDB::bind_method(D_METHOD("get_scale"), &VoxelGenJson::get_scale);
	ClassDB::bind_method(D_METHOD("set_hsc", "hsc"), &VoxelGenJson::set_hsc);
	ClassDB::bind_method(D_METHOD("get_hsc"), &VoxelGenJson::get_hsc);
	
	ADD_PROPERTY(PropertyInfo(Variant::INT, "scale", PROPERTY_HINT_RANGE, "1,16,1"), "set_scale", "get_scale");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "hsc", PROPERTY_HINT_RANGE, "0.0,1.0,0.01"), "set_hsc", "get_hsc");

}
