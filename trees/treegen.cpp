#include "treegen.h"

Transform IDENTITY = Transform(Basis(1, 0, 0, 0, 1, 0, 0, 0, 1 ),Vector3(0,0,0));
void TreeGen::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_order", "order"), &TreeGen::set_order);
	ClassDB::bind_method(D_METHOD("get_order"), &TreeGen::get_order);
	ClassDB::bind_method(D_METHOD("set_une", "une"), &TreeGen::set_une);
	ClassDB::bind_method(D_METHOD("get_une"), &TreeGen::get_une);
	ClassDB::bind_method(D_METHOD("set_sideAngleB", "sideAngleB"), &TreeGen::set_sideAngleB);
	ClassDB::bind_method(D_METHOD("get_sideAngleB"), &TreeGen::get_sideAngleB);
	ClassDB::bind_method(D_METHOD("set_sidangle", "sidangleB"), &TreeGen::set_sidangle);
	ClassDB::bind_method(D_METHOD("get_sidangle"), &TreeGen::get_sidangle);
	ClassDB::bind_method(D_METHOD("set_rotation", "rotation"), &TreeGen::set_rotation);
	ClassDB::bind_method(D_METHOD("get_rotation"), &TreeGen::get_rotation);
	ClassDB::bind_method(D_METHOD("set_distA", "distA"), &TreeGen::set_distA);
	ClassDB::bind_method(D_METHOD("get_distA"), &TreeGen::get_distA);
	ClassDB::bind_method(D_METHOD("set_wor", "wor"), &TreeGen::set_wor);
	ClassDB::bind_method(D_METHOD("get_wor"), &TreeGen::get_wor);
	ClassDB::bind_method(D_METHOD("gen", "w", "h", "home"), &TreeGen::gen);
	ClassDB::bind_method(D_METHOD("addtreebranch", "inf"), &TreeGen::addtreebranch);
	ClassDB::bind_method(D_METHOD("createTree"), &TreeGen::createTree);
	ClassDB::bind_method(D_METHOD("set_top_radius", "radius"), &TreeGen::set_top_radius);
	ClassDB::bind_method(D_METHOD("get_top_radius"), &TreeGen::get_top_radius);
	ClassDB::bind_method(D_METHOD("set_bottom_radius", "radius"), &TreeGen::set_bottom_radius);
	ClassDB::bind_method(D_METHOD("get_bottom_radius"), &TreeGen::get_bottom_radius);
	ClassDB::bind_method(D_METHOD("set_height", "height"), &TreeGen::set_height);
	ClassDB::bind_method(D_METHOD("get_height"), &TreeGen::get_height);
	ClassDB::bind_method(D_METHOD("set_width", "width"), &TreeGen::set_width);
	ClassDB::bind_method(D_METHOD("get_width"), &TreeGen::get_width);
	ClassDB::bind_method(D_METHOD("set_radial_segments", "segments"), &TreeGen::set_radial_segments);
	ClassDB::bind_method(D_METHOD("get_radial_segments"), &TreeGen::get_radial_segments);
	ClassDB::bind_method(D_METHOD("set_rings", "rings"), &TreeGen::set_rings);
	ClassDB::bind_method(D_METHOD("get_rings"), &TreeGen::get_rings);
	ClassDB::bind_method(D_METHOD("set_leafScale", "leafScale"), &TreeGen::set_leafScale);
	ClassDB::bind_method(D_METHOD("get_leafScale"), &TreeGen::get_leafScale);
	ClassDB::bind_method(D_METHOD("get_transforms"), &TreeGen::get_transforms);
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "order", PROPERTY_HINT_RANGE, "2.0,50.0,0.01"), "set_order", "get_order");
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "une", PROPERTY_HINT_RANGE, "0.0,2.0,0.01"), "set_une", "get_une");
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "sideAngleB", PROPERTY_HINT_RANGE, "0.0,2.0,0.01"), "set_sideAngleB", "get_sideAngleB");
	ADD_PROPERTY(PropertyInfo(Variant::POOL_VECTOR3_ARRAY, "sidangle", PROPERTY_HINT_NONE, ""), "set_sidangle", "get_sidangle");
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "rotation", PROPERTY_HINT_RANGE, "0.0,1.0,0.01"), "set_rotation", "get_rotation");
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "distA", PROPERTY_HINT_RANGE, "0.0,1.0,0.01"), "set_distA", "get_distA");
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "wor", PROPERTY_HINT_RANGE, "-2.0,2.0,0.01"), "set_wor", "get_wor");
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "top_radius", PROPERTY_HINT_RANGE, "0.0,1.0,0.01"), "set_top_radius", "get_top_radius");
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "bottom_radius", PROPERTY_HINT_RANGE, "-2.0,2.0,0.01"), "set_bottom_radius", "get_bottom_radius");
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "height", PROPERTY_HINT_RANGE, "0.0,100.0,0.01"), "set_height", "get_height");
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "width", PROPERTY_HINT_RANGE, "0.0,100.0,0.01"), "set_width", "get_width");
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "radial_segments", PROPERTY_HINT_RANGE, "3.0,20.0,1.0"), "set_radial_segments", "get_radial_segments");
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "rings", PROPERTY_HINT_RANGE, "0.0,10.0,0.01"), "set_rings", "get_rings");
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "leafScale", PROPERTY_HINT_RANGE, "0.0,20.0,0.01"), "set_leafScale", "get_leafScale");
	
	
}
void TreeGen::set_order(float order) {
	this->order = order;
	_request_update();
}
float TreeGen::get_order() const {
	return order;
}
void TreeGen::set_une(float une) {
	this->une = une;
	_request_update();
}
float TreeGen::get_une() const {
	return une;
}
void TreeGen::set_sideAngleB(float sideAngleB) {
	this->sideAngleB = sideAngleB;
	PoolVector3Array temp = PoolVector3Array();
	if(this->sidangle.size()<2){
		this->sidangle=PoolVector3Array();
		this->sidangle.push_back(Vector3(0, 0, 0));
		this->sidangle.push_back(Vector3(0, 0, 0));
	}
	for (int i = 0; i < sidangle.size(); i++) {
		float tp = float(i)/float(sidangle.size());
		float atp = ((tp-0.5)*float(une))+0.5;
		temp.append(Vector3(atp*sideAngleB,0,0));
	}
	this->sidangle = temp;
	this->updateParts();
	_request_update();
}
float TreeGen::get_sideAngleB() const {
	return sideAngleB;
}
void TreeGen::set_sidangle(PoolVector3Array sidangle) {
	PoolVector3Array temp = PoolVector3Array();

	float tot = 0.0;
	for (int i = 0; i < sidangle.size(); i++) {
		tot += sidangle[i].y*sidangle[i].y;
	}
	tot = MAX(sqrt(tot),0.0001);
	for (int i = 0; i < sidangle.size(); i++) {
		temp.append(Vector3(sidangle[i].x, sidangle[i].y/tot, sidangle[i].z));
	}
	this->sidangle = temp;
	this->updateParts();
	_request_update();
}
PoolVector3Array TreeGen::get_sidangle() const {
	return sidangle;
}
void TreeGen::set_rotation(float rotation) {
	this->rotation = rotation;
	this->updateParts();
	_request_update();
}
float TreeGen::get_rotation() const {
	return rotation;
}
void TreeGen::set_distA(float distA) {
	this->distA = distA;
	_request_update();
}
float TreeGen::get_distA() const {
	return distA;
}
void TreeGen::set_wor(float wor) {
	this->wor = wor;
	_request_update();
}
float TreeGen::get_wor() const {
	return wor;
}
void TreeGen::set_top_radius(float radius) {
	this->top_radius = radius;
	_request_update();
}
float TreeGen::get_top_radius() const {
	return top_radius;
}
void TreeGen::set_bottom_radius(float radius) {
	this->bottom_radius = radius;
	_request_update();
}
float TreeGen::get_bottom_radius() const {
	return bottom_radius;
}
void TreeGen::set_height(float height) {
	this->height = height;
	_request_update();
}
float TreeGen::get_height() const {
	return height;
}
void TreeGen::set_width(float width) {
	this->width = width;
	_request_update();
}
float TreeGen::get_width() const {
	return width;
}
void TreeGen::set_radial_segments(int segments) {
	this->radial_segments = segments;
	this->updateParts();
	_request_update();
}
int TreeGen::get_radial_segments() const {
	return radial_segments;
}
void TreeGen::set_rings(int rings) {
	this->rings = rings;
	_request_update();
}
int TreeGen::get_rings() const {
	return rings;
}
void TreeGen::set_leafScale(float leafScale) {
	this->leafScale = leafScale;
	_request_update();
}
float TreeGen::get_leafScale() const {
	return leafScale;
}
Array TreeGen::get_transforms() {
	if(!transforms.empty())
		return transforms;
	else{
		Dictionary tr = createTree();
		Array tree = tr["tree"];
		Array leaf = tr["leaf"];
		transforms = tree;
		return tree;
		
		}
}


Dictionary TreeGen::gen(float w,float h,Transform home) const{
	Dictionary thisbranch = Dictionary{};
	Transform az = home.translated((Vector3(0.0,h,0.0)));
	thisbranch["branches"] = Array{};
	for(int i = 0; i < sidangle.size();i++){
		Dictionary z = Dictionary{};
		float tp = float(i)/float(sidangle.size());
		float atp = ((tp-0.5)*float(une))+0.5;
		z["tran"]=(az*sid[i]);
		z["w"] =sqrt((w*w)*float(distA)*(1.0-atp));
		z["h"] = sqrt(h*h*(1.0-atp)*float(wor));
		Array(thisbranch["branches"]).append(z);
	}
	Transform t = home.translated(Vector3(0.0,h/2,0.0)) * IDENTITY.scaled(Vector3(w,h,w));
	thisbranch["myTransform"] = t;
	
	thisbranch["leaftransform"] = home.translated(Vector3(0.0,h/2,0.0))* IDENTITY.scaled(Vector3(leafScale,leafScale,leafScale)) ;
	return thisbranch;
	}
Dictionary TreeGen::addtreebranch(Dictionary inf) const{

	Array leaftransforms = Array{};
	Array treetransforms = Array{};
	Array parentTransforms = Array{};
	Transform tree = Dictionary(inf["b"])["myTransform"];
	Transform leaf = Dictionary(inf["b"])["leaftransform"];
	if(int(inf["d"]) > 0){
		for(int bi = 0; bi < Array(Dictionary(inf["b"])["branches"]).size();bi++){
			Dictionary b = Array(Dictionary(inf["b"])["branches"])[bi];
			Dictionary a = gen(b["w"],b["h"],b["tran"]);
			//Transform zz = a["myTransform"];
			if(float(b["w"]) > 0.5){
				Dictionary n = Dictionary{};
				a["parent"] = tree*sidL[bi];
				n["b"] = a;
				n["d"] = int(inf["d"])-1;
				
				Dictionary r = addtreebranch(n);
				Array nt = r["tree"];
				Array nl = r["leaf"];
				Array npt = r["parent"];
				for(int yy = 0; yy < nt.size(); yy++){
					treetransforms.append(nt[yy]);
					parentTransforms.append(npt[yy]);
				}
				for(int xx = 0; xx < nl.size(); xx++){
					leaftransforms.append(nl[xx]);
				}
			}
			else{
				if(bi == 0){
					//leaf =  IDENTITY.translated(Vector3(0.0,-1.0,0.0))*leaf;
					leaftransforms.append(leaf);

				}
		
		}}
	}
	else{
					//leaf =  IDENTITY.translated(Vector3(0.0,-1.0,0.0))*leaf;
		leaftransforms.append(leaf);
	}
	
	treetransforms.append(tree);;
	Transform parent = Dictionary(inf["b"])["parent"];
	parentTransforms.append(parent);
	Dictionary ret = Dictionary{};
	ret["tree"] = treetransforms;
	ret["leaf"] = leaftransforms;
	ret["parent"] = parentTransforms;
	return ret;
}
Dictionary TreeGen::createTree() const {
	Dictionary b =  gen(width,height,Transform(Basis(1, 0, 0, 0, 1, 0, 0, 0, 1 ),Vector3(0,0,0)));
	Dictionary z = Dictionary{};
	b["parent"] = Transform(Basis(1, 0, 0, 0, 1, 0, 0, 0, 1 ),Vector3(0,-0.5,0)).scaled(Vector3(width,height,width));
	z["b"] = b;
	z["d"] = order;
	
	Dictionary t = addtreebranch(z);
	return t;
	
}
void TreeGen::updateParts(){
	this->sid = Array();
	this->sidL = Array();
	for (int i = 0; i < sidangle.size(); i++) {
		float tp = float(i)/float(sidangle.size());
		sid.append(
			IDENTITY.rotated(Vector3(0.0,0.0,1.0), (float(sidangle[i].x)*3.1415/2)).rotated(Vector3(0.0,1.0,0.0),2.0*((tp+rotation)*3.1415))
		);
		sidL.append(
			IDENTITY.rotated(Vector3(0,1,0),(2.0*(round((float(i)/float(sidangle.size())+rotation)*float(radial_segments))/float(radial_segments))*3.1415))
		);
	}
}
void TreeGen::_create_mesh_array(Array &p_arr, Dictionary tr) const {
	#define ADD_TANGENT(m_x, m_y, m_z, m_d) \
	tangents.push_back(m_x);            \
	tangents.push_back(m_y);            \
	tangents.push_back(m_z);            \
	tangents.push_back(m_d);

	p_arr[VS::ARRAY_VERTEX] = Array();
	p_arr[VS::ARRAY_NORMAL] =Array();
	Vector2 split = Vector2(0.5,0);
	Array tree = tr["tree"];
	Array leaf = tr["leaf"];
	Array parent = tr["parent"];
	int i, j, prevrow, thisrow, point;
	float x, y, z, u, v, radius;

	PoolVector<Vector3> points;
	PoolVector<Vector3> normals;
	PoolVector<float> tangents;
	PoolVector<Vector2> uvs;
	PoolVector<int> indices;
	point = 0;
	//Generate a Cylinder for the trunk for each transform in the tree array
	thisrow = 0;
	prevrow = 0;
	for(int cr = 0; cr < tree.size(); cr++){
		Transform t = tree[cr];
		Transform n = parent[cr];
		Transform par = n*IDENTITY.translated(Vector3(0.0,0.5,0.0));
		
		
		for (j = 0; j <= (rings + 1); j++) {
			v = j;
			v /= (rings + 1);

			radius = top_radius + ((top_radius - top_radius) * v);
			y = 1.0 * v;
			y = (0.1) - y*0.5;

			for (i = 0; i <= radial_segments; i++) {
				u = i;
				u /= radial_segments;

				x = sin(u * (Math_PI * 2.0));
				z = cos(u * (Math_PI * 2.0));
				
				Vector3 pointa = Vector3(x * radius, y, z * radius);
				Transform cur = t.interpolate_with(par,v);
				Vector3 p =((cur)*Transform(Basis(1, 0, 0, 0, 1, 0, 0, 0, 1 ),pointa)).origin;	
				Vector3 c = ((cur)*Transform(Basis(1, 0, 0, 0, 1, 0, 0, 0, 1 ),Vector3(0,y,0))).origin;
				Vector3 nn = (p-(c)).normalized();
				Vector3 tangent = cur.basis.elements[1].normalized().cross(nn).normalized();
				points.push_back(p);
				normals.push_back(nn);
				ADD_TANGENT(tangent.x,tangent.y,tangent.z, 1.0)
				uvs.push_back(Vector2(u, v ));
				point++;

				if (i > 0 && j > 0) {
					indices.push_back(prevrow + i - 1);
					indices.push_back(prevrow + i);
					indices.push_back(thisrow + i - 1);

					indices.push_back(prevrow + i);
					indices.push_back(thisrow + i);
					indices.push_back(thisrow + i - 1);
			
				};
				
			};

			prevrow = thisrow;
			thisrow = point;
		};
	
		/* add top
		if (top_radius > 0.0) {
			y = 1.0 * 0.5;

			thisrow = point;
			points.push_back(((t*Transform(Basis(1, 0, 0, 0, 1, 0, 0, 0, 1 ),Vector3(0.0, y, 0.0)))).origin);
			
			normals.push_back(dir);
			ADD_TANGENT(1.0, 0.0, 0.0, 1.0)
			uvs.push_back(Vector2(0.5,1.0)*Vector2(0.25, 0.75));
			point++;

			for (i = 0; i <= radial_segments; i++) {
				float r = i;
				r /= radial_segments;

				x = sin(r * (Math_PI * 2.0));
				z = cos(r * (Math_PI * 2.0));

				u = ((x + 1.0) * 0.25);
				v = 0.5 + ((z + 1.0) * 0.25);

				Vector3 p = (t*Transform(Basis(1, 0, 0, 0, 1, 0, 0, 0, 1 ),Vector3(x * top_radius, y, z * top_radius))).origin;
				points.push_back(p);
				ADD_TANGENT(1.0, 0.0, 0.0, 1.0)
				uvs.push_back(Vector2(0.5,1.0)*Vector2(u, v));
				point++;

				if (i > 0) {
					indices.push_back(thisrow);
					indices.push_back(point - 1);
					indices.push_back(point - 2);
				};
				normals.push_back(dir);
			};
		};

		// add bottom
		if (bottom_radius > 0.0) {
			y = 1.0 * -0.5;

			thisrow = point;
			points.push_back((t*Transform(Basis(1, 0, 0, 0, 1, 0, 0, 0, 1 ),Vector3(0.0, y, 0.0))).origin);
			normals.push_back(-dir);
			ADD_TANGENT(1.0, 0.0, 0.0, 1.0)
			uvs.push_back(Vector2(0.5,1.0)*Vector2(0.75, 0.75));
			point++;

			for (i = 0; i <= radial_segments; i++) {
				float r = i;
				r /= radial_segments;

				x = sin(r * (Math_PI * 2.0));
				z = cos(r * (Math_PI * 2.0));

				u = 0.5 + ((x + 1.0) * 0.25);
				v = 1.0 - ((z + 1.0) * 0.25);

				Vector3 p = (t*Transform(Basis(1, 0, 0, 0, 1, 0, 0, 0, 1 ),Vector3(x * bottom_radius, y, z * bottom_radius))) .origin;
				points.push_back(p);
				
				ADD_TANGENT(1.0, 0.0, 0.0, 1.0)
				uvs.push_back(Vector2(0.5,1.0)*Vector2(u, v));
				point++;

				if (i > 0) {
					indices.push_back(thisrow);
					indices.push_back(point - 2);
					indices.push_back(point - 1);
				};
				normals.push_back(-dir);
			};
		};*/
		thisrow = point;
	}
	// for(int lr = 0; lr < leaf.size(); lr++){
	// 	Transform t = leaf[lr];
	// 	Vector3 a = (t*Transform(Basis(1, 0, 0, 0, 1, 0, 0, 0, 1 ),Vector3(0.0, 1.0, 0.5)*leafScale)).origin;
	// 	Vector3 b = (t*Transform(Basis(1, 0, 0, 0, 1, 0, 0, 0, 1 ),Vector3(0.0, 1.0, -0.5)*leafScale)).origin;
	// 	Vector3 c = (t*Transform(Basis(1, 0, 0, 0, 1, 0, 0, 0, 1 ),Vector3(0.0, 0.0, 0.5)*leafScale)).origin;
	// 	Vector3 d = (t*Transform(Basis(1, 0, 0, 0, 1, 0, 0, 0, 1 ),Vector3(0.0, 0.0, -0.5)*leafScale)).origin;
	// 	Vector3 n = (t*Transform(Basis(1, 0, 0, 0, 1, 0, 0, 0, 1 ),Vector3(-1.0, 0.0, 0.0))).origin - t.origin;
	// 	points.push_back(a);
	// 	points.push_back(b);
	// 	points.push_back(c);
	// 	points.push_back(c);
	// 	points.push_back(b);
	// 	points.push_back(d);
	// 	normals.push_back(-n);
	// 	normals.push_back(-n);
	// 	normals.push_back(-n);
	// 	normals.push_back(-n);
	// 	normals.push_back(-n);
	// 	normals.push_back(-n);
	// 	ADD_TANGENT(1.0, 0.0, 0.0, 1.0);
	// 	ADD_TANGENT(1.0, 0.0, 0.0, 1.0);
	// 	ADD_TANGENT(1.0, 0.0, 0.0, 1.0);
	// 	ADD_TANGENT(1.0, 0.0, 0.0, 1.0);
	// 	ADD_TANGENT(1.0, 0.0, 0.0, 1.0);
	// 	ADD_TANGENT(1.0, 0.0, 0.0, 1.0);
	// 	uvs.push_back(split+Vector2(0.5,1.0)*Vector2(0.0, 0.0));
	// 	uvs.push_back(split+Vector2(0.5,1.0)*Vector2(1.0, 0.0));
	// 	uvs.push_back(split+Vector2(0.5,1.0)*Vector2(0.0, 1.0));
	// 	uvs.push_back(split+Vector2(0.5,1.0)*Vector2(0.0, 1.0));
	// 	uvs.push_back(split+Vector2(0.5,1.0)*Vector2(1.0, 0.0));
	// 	uvs.push_back(split+Vector2(0.5,1.0)*Vector2(1.0, 1.0));
		
	// 	indices.push_back(point);
	// 	indices.push_back(point+1);
	// 	indices.push_back(point+2);
	// 	indices.push_back(point+3);
	// 	indices.push_back(point+4);
	// 	indices.push_back(point+5);
	// 	point += 6;
	// 	thisrow = point;
	//}
	p_arr[VS::ARRAY_VERTEX] = points;
	p_arr[VS::ARRAY_NORMAL] = normals;
	p_arr[VS::ARRAY_TANGENT] = tangents;
	p_arr[VS::ARRAY_TEX_UV] = uvs;
	p_arr[VS::ARRAY_INDEX] = indices;
	
}


	