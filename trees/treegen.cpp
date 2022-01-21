#include "treegen.h"
Transform IDENTITY = Transform(Basis(1, 0, 0, 0, 1, 0, 0, 0, 1 ),Vector3(0,0,0));
Dictionary TreeGen::gen(Dictionary treedetails ,float w,float h,Transform home){
	Dictionary thisbranch = Dictionary{};
	
	thisbranch["branches"] = Array{};
	for(int i = 0; i < int(treedetails["order"]);i++){
		Dictionary z = Dictionary{};
		z["tran"] = IDENTITY;
		float tp = float(i)/float(treedetails["order"]);
		float atp = ((tp-0.5)*float(treedetails["une"]))+0.5;
		z["tran"]=(z["tran"].operator Transform()).rotated(Vector3(0.0,0.0,1.0), (float(treedetails["sidangleB"])*3.1415/2)*(atp));
		z["tran"]=(z["tran"].operator Transform()).rotated(Vector3(0.0,1.0,0.0),3.1415*2*tp+float(treedetails["rotation"]));
		 
		z["tran"]=(home.translated((Vector3(0.0,h,0.0)))*(z["tran"]));
		z["w"] = sqrt((w*w)*float(treedetails["distA"])*(1.0-atp));
		z["h"] = sqrt(h*h*(1.0-atp)*float(treedetails["wor"]));
		Array(thisbranch["branches"]).append(z);
	}
	thisbranch["myTransform"] = home.translated(Vector3(0.0,h/2,0.0)) * IDENTITY.scaled(Vector3(w,h,w));
	thisbranch["leaftransform"] = home;
	return thisbranch;
	}
Dictionary TreeGen::addtreebranch(Dictionary inf,Dictionary treedetails){
	Array leaftransforms = Array{};
	Array treetransforms = Array{};
	if(int(inf["d"]) > 0){
		for(int bi = 0; bi < Array(Dictionary(inf["b"])["branches"]).size();bi++){
			Dictionary b = Array(Dictionary(inf["b"])["branches"])[bi];
			Dictionary a = gen(treedetails,b["w"],b["h"],b["tran"]);
			
			if(float(b["w"]) > 0.5){
				Dictionary n = Dictionary{};
				n["b"] = a;
				n["d"] = int(inf["d"])-1;
				Dictionary r = addtreebranch(n,treedetails);
				Array nt = r["tree"];
				Array nl = r["leaf"];
				for(int yy = 0; yy < nt.size(); yy++){
					treetransforms.append(nt[yy]);
				}
				for(int xx = 0; xx < nl.size(); xx++){
					leaftransforms.append(nl[xx]);
				}
			}
			else{
			Transform leaf =(a["leaftransform"]);
		leaftransforms.append((leaf.basis.get_row(0)).x);
		leaftransforms.append((leaf.basis.get_row(0)).y);
		leaftransforms.append((leaf.basis.get_row(0)).z);
		leaftransforms.append(leaf.origin.x);
		leaftransforms.append((leaf.basis.get_row(1)).x);
		leaftransforms.append((leaf.basis.get_row(1)).y);
		leaftransforms.append((leaf.basis.get_row(1)).z);
		leaftransforms.append(leaf.origin.y);
		leaftransforms.append((leaf.basis.get_row(2)).x);
		leaftransforms.append((leaf.basis.get_row(2)).y);
		leaftransforms.append((leaf.basis.get_row(2)).z);
		leaftransforms.append(leaf.origin.z);
		
		}}
	}
	else{
		Transform leaf = Dictionary(Array(Dictionary(inf["b"])["branches"])[int(treedetails["order"])-1])["tran"];
		leaftransforms.append((leaf.basis.get_row(0)).x);
		leaftransforms.append((leaf.basis.get_row(0)).y);
		leaftransforms.append((leaf.basis.get_row(0)).z);
		leaftransforms.append(leaf.origin.x);
		leaftransforms.append((leaf.basis.get_row(1)).x);
		leaftransforms.append((leaf.basis.get_row(1)).y);
		leaftransforms.append((leaf.basis.get_row(1)).z);
		leaftransforms.append(leaf.origin.y);
		leaftransforms.append((leaf.basis.get_row(2)).x);
		leaftransforms.append((leaf.basis.get_row(2)).y);
		leaftransforms.append((leaf.basis.get_row(2)).z);
		leaftransforms.append(leaf.origin.z);
	}
	Transform tree = Dictionary(inf["b"])["myTransform"];
		treetransforms.append((tree.basis.get_row(0)).x);
		treetransforms.append((tree.basis.get_row(0)).y);
		treetransforms.append((tree.basis.get_row(0)).z);
		treetransforms.append(tree.origin.x);
		treetransforms.append((tree.basis.get_row(1)).x);
		treetransforms.append((tree.basis.get_row(1)).y);
		treetransforms.append((tree.basis.get_row(1)).z);
		treetransforms.append(tree.origin.y);
		treetransforms.append((tree.basis.get_row(2)).x);
		treetransforms.append((tree.basis.get_row(2)).y);
		treetransforms.append((tree.basis.get_row(2)).z);
		treetransforms.append(tree.origin.z);
	Dictionary ret = Dictionary{};
	ret["tree"] = treetransforms;
	ret["leaf"] = leaftransforms;
	return ret;
}
void TreeGen::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("addtreebranch","inf", "treedetails"),
			&TreeGen::addtreebranch);
    ClassDB::bind_method(D_METHOD("gen","treedetails", "w","h","home"),
			&TreeGen::gen);
}
