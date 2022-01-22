#include "voxel_gen_hex.h"
#include "../constants/voxel_string_names.h"
#include "../util/godot/funcs.h"
#include "core/math/random_number_generator.h"
VoxelGenHex::VoxelGenHex() {
}
float scale = 1.0;
Vector2 VoxelGenHex::hextest(int bbx,int bby, int zoom2){
    
	
	
	int bbox = bbx;
	int bboy = bby;
	int bunx = bbx;
	int buny = bby;
	int bununx = bbx;
	int zoom2x2 = zoom2<<1;
	int zoom2x4 = zoom2<<2;
	int zoom2d2 = zoom2>>1;
	if(Math::wrapi(bby,0,(zoom2x2))<zoom2){
		if(Math::wrapi(bby,0,(zoom2x4))<zoom2){
			bbox += zoom2;}
		if(Math::wrapi(bbox,0,(zoom2x2))<zoom2){
			bbox -=zoom2;}
    }
	
	else{
		if(Math::wrapi(bby,0,(zoom2x4))>=zoom2x2){
			if(Math::wrapi(bbx,0,(zoom2x2))>=zoom2){
				bunx*= -1;
				bbox -=   zoom2;}
			if(Math::wrapi(((bunx+buny)>>1),0,(zoom2)) <(zoom2d2)){
				bbox +=zoom2;
				bboy += zoom2;}
			else{
				bboy -=zoom2;
				bbox = (bunx-Math::wrapi(bunx,0,zoom2)) - zoom2;
				if(Math::wrapi(bununx,0,(zoom2x2))>=zoom2){
					bbox = (bununx-Math::wrapi(bununx,0,zoom2));}
            }
					
        }
		else{
			if(Math::wrapi(bbx,0,(zoom2x2))<zoom2){
				bunx *= -1;
				bbox -= zoom2;}
			 

			if(Math::wrapi(((bunx+buny)>>1),0,(zoom2)) > (zoom2d2)){
				bboy += zoom2;}
			else{
				bbox = (bunx-Math::wrapi(bunx,0,zoom2));
				bboy -= zoom2;
				if(Math::wrapi(bununx,0,(zoom2x2))<zoom2){
					bbox = (bununx-Math::wrapi(bununx,0,zoom2)) + zoom2;}
    }}}
	
	if(Math::wrapi(bboy,0,(zoom2x4))>zoom2){
		bbox += zoom2;}
	
	Vector2 bbo = Vector2(bbox-Math::wrapi(bbox,0,zoom2),bboy-Math::wrapi(bboy,0,zoom2));
	
	return Vector2(bbo.x,bbo.y+zoom2d2);
}
float VoxelGenHex::fract(float in){
	return in-floor(in);
}
float VoxelGenHex::get_hash( Vector2 c){
	return fract(Math::sin(c.dot(Vector2(12.9898,78.233))) * 43758.5453);}
float VoxelGenHex::genMountainHeight(Vector2 location, int initialSize,float ss,int lod,Dictionary d,Parameters params){
	
	float mtnheight = 0.0;
	int size = initialSize;
	Vector2 OldHex = hextest(int(location.x),int(location.y),params.scale );
	for(int s = 0; s < 50; s++){
		
	Vector2 hex = hextest(int(location.x),int(location.y),(size));
	
	float dist = hex.distance_to(location);
	
	
	float modifier = (get_hash(hex));
	//if(params.isWater){
	//	modifier = max(0.0f,modifier);
	//}
	float height =  modifier * ss * ((cos((min(dist,float(size))/float(size))*3.1415)*0.5+0.5)*float(size));
	if(OldHex.distance_to(hex)>params.scale ){
		break;
	}
	mtnheight += height;

	OldHex = hex;
	
	size = size >> 1;
	if(size < 8)break;
	}
	
	
	

	
	return mtnheight;
}
float VoxelGenHex::randf_range(float from, float to){
	
	return (to-from)*float(rand())/float(RAND_MAX) + from;

}
float xrandf_range(RandomNumberGenerator* seed,float from, float to){
	return seed->randf_range(from,to);
}
Dictionary VoxelGenHex::genDeets( Vector2 location,Vector2 b,int plod,Parameters params){
	
	float seeed = get_hash(location);
	RandomNumberGenerator* sed = new RandomNumberGenerator();
	sed->set_seed(int(floor(seeed*100000.0))+params.seed);
	
	
	Dictionary deets = Dictionary{};
	
	deets["EZislandWidth"] = xrandf_range(sed,2,4);
	deets["islandHeight"] = xrandf_range(sed,10,1000);
	deets["islandScale"] = round(xrandf_range(sed,0.1,1.5)*4.0)/4.0+0.1;
	deets["islandDensity"] = xrandf_range(sed,0.5,0.99);
	
	deets["islandDrip"] = round(xrandf_range(sed,0.1,3))+0.1;
	deets["connectiveness"] = xrandf_range(sed,0.1,0.8);
	deets["landheight"] = xrandf_range(sed,40,400);
	deets["islandLift"] = float(deets["landheight"])+xrandf_range(sed,0,450);
	deets["landScale"] = xrandf_range(sed,0.1,3);
	deets["watertable"] = 3;
	deets["tip"] = genMountainHeight(b,params.scale >> int(deets["EZislandWidth"]),1.0,plod,deets,params);
	
				//move to gendeets
	deets["groundTip"] =  Math::lerp(genMountainHeight(b,params.scale,deets["landScale"],plod,deets,params),deets["tip"],min(1.0f,float(deets["connectiveness"])));
	
	
	return deets;}
Dictionary VoxelGenHex::genDetails( Vector3 location,int plod,Parameters params){
	int scale = params.scale;
	//Vector2 fix = Vector2(scale,0);
   // Vector2 fix2 = Vector2(scale/2,scale);
   // Vector2 fix3 = Vector2(scale/2+scale,scale);
    Vector2 dd = Vector2(location.x,location.z);
    
    Vector2 n = (hextest(dd.x,dd.y, scale));
    //Vector2 nn = (hextest(dd.x+fix.x,dd.y+fix.y, scale));
    //Vector2 nnn = (hextest(dd.x+fix2.x,dd.y+fix2.y, scale));
    //Vector2 nnnn = (hextest(dd.x+fix3.y,dd.y+fix3.y, scale));
    //float col  = max(0.0,1.0- n.distance_to(dd)/float(scale));
    //float col2 = max(0.0,1.0- nn.distance_to(dd+fix)/float(scale));
    //float col3 = max(0.0,1.0- nnn.distance_to(dd+fix2)/float(scale));
    //float col4 = max(0.0,1.0- nnnn.distance_to(dd+fix3)/float(scale));


	
	Dictionary deets = genDeets(n,dd,plod,params);
	//Dictionary deet1 = genDeets(nn,dd,plod,params);
	//Dictionary deet2 = genDeets(nnn,dd,plod,params);
	//Dictionary deet3 = genDeets(nnnn,dd,plod,params);
	//Dictionary bb = Dictionary{};
	//for(int i = 0; i < deets.keys().size();i++){
	//	bb[deets.keys()[i]] = 
	//	float(deets[deets.keys()[i]])*col+
	//	float(deet1[deets.keys()[i]])*col2+
	//	float(deet2[deets.keys()[i]])*col3+
	//	float(deet3[deets.keys()[i]])*col4;
	//}
	return deets;
}
Array VoxelGenHex::getMountainsAndSkyIslands(Dictionary d,int i,int k,Vector3 origin, int plod,int ys){
	
	Array smbuffer = Array{} ;

	for(int j = 0; j < ys;j++){
	smbuffer.append(1.0);
	Vector3 a = (origin+Vector3(i,j,k)*plod)*scale;
	float tbd = 1.0;
	float groundTip = d["groundTip"];
	if(a.y < groundTip ){
		tbd = a.y - groundTip;
		smbuffer[j] = tbd;}
	float islandEdge = float(d["islandHeight"])*(1.0-float(d["islandDensity"]));
	if(float(d["tip"])>islandEdge){
		if(a.y>(float(d["islandLift"])+islandEdge)-max(0.0f,float(d["tip"])*float(d["islandDrip"]))){
			if(a.y > (float(d["islandLift"])+islandEdge)){
				
				float islandSplit = float(d["islandLift"])+islandEdge;
				float tdb = (a.y-islandSplit)/float(d["islandScale"])-(float(d["tip"])-islandEdge);
				if(tdb<1){
					smbuffer[j] = tdb;
				}
					
			}else{
				float islandSplit =float(d["islandLift"])+islandEdge;
				a.y = abs(a.y-islandSplit)/float(d["islandDrip"])+islandSplit;
				float bb = (a.y-islandSplit)-(float(d["tip"])-islandEdge);
				if(bb<1){
					smbuffer[j]=bb;
				}
	}}}
}
return smbuffer;
};
Array VoxelGenHex::getBlocks(Vector3 origin,int lod,int xs,int ys,int zs, Parameters params){
	int plod = pow(2,lod);
	Array blocks = Array{};
	if(origin.y > - 100){
		for(int i = 0; i < xs; i++){
			Array BlocksI = Array{};
			for(int k = 0; k < zs; k++){
				Dictionary d = genDetails((origin+Vector3(i,0,k)*plod)*scale,plod,params);
				
				
				
				Array pieces = getMountainsAndSkyIslands(d,i,k,origin,plod,ys);
				BlocksI.push_back(pieces);
			}
			blocks.push_back(BlocksI);
		}
	}	
	return blocks;
}
void VoxelGenHex::set_seed(int seed) {
	RWLockWrite wlock(_parameters_lock);
	_parameters.seed = seed;
}

int VoxelGenHex::get_seed() {
	RWLockRead rlock(_parameters_lock);
	return _parameters.seed;
}
void VoxelGenHex::set_scale(int scale) {
	RWLockWrite wlock(_parameters_lock);
	_parameters.scale = scale;
}

int VoxelGenHex::get_scale() {
	RWLockRead rlock(_parameters_lock);
	return _parameters.scale;
}
VoxelGenerator::Result VoxelGenHex::generate_block(VoxelBlockRequest &input) {
	Result result;
	Parameters params;
	{
		RWLockRead rlock(_parameters_lock);
		params = _parameters;
	}
	// Create a temporary wrapper so Godot can pass it to scripts
	Ref<VoxelBuffer> buffer_wrapper;
	buffer_wrapper.instance();
	buffer_wrapper->get_buffer().copy_format(input.voxel_buffer);
	buffer_wrapper->get_buffer().create(input.voxel_buffer.get_size());
	
	// The wrapper is discarded
	
	
	int xs = buffer_wrapper->get_buffer().get_size().x;
	int ys = buffer_wrapper->get_buffer().get_size().y;
	int zs = buffer_wrapper->get_buffer().get_size().z;
	Array blocks = getBlocks(Vector3(input.origin_in_voxels.x,input.origin_in_voxels.y,input.origin_in_voxels.z),input.lod,xs,ys,zs,params);
	if(blocks.size()>0){
		
		for(int i = 0; i < xs; i++){
			for(int j = 0; j < ys; j++){
				for(int k = 0; k < zs; k++){
					
					buffer_wrapper->get_buffer().set_voxel_f((0.1/(1 << input.lod))*float(Array(Array(blocks[i])[k])[j]),i,j,k,1);
					}
					
				}}}
	
	;
	buffer_wrapper->get_buffer().move_to(input.voxel_buffer);

	// We may expose this to scripts the day it actually gets used
	// if (ret.get_type() == Variant::DICTIONARY) {
	// 	Dictionary d = ret;
	// 	result.max_lod_hint = d.get("max_lod_hint", false);
	// }

	return result;
}

int VoxelGenHex::get_used_channels_mask() const {
	
	return 1 << 1;
}

void VoxelGenHex::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_seed", "isWater"), &VoxelGenHex::set_seed);
	ClassDB::bind_method(D_METHOD("get_seed"), &VoxelGenHex::get_seed);
	ClassDB::bind_method(D_METHOD("set_scale", "scale"), &VoxelGenHex::set_scale);
	ClassDB::bind_method(D_METHOD("get_scale"), &VoxelGenHex::get_scale);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "seed"), "set_seed", "get_seed");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "scale"), "set_scale", "get_scale");
}
