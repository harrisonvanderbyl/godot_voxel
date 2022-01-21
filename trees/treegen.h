#ifndef TREE_GEN_H
#define TREE_GEN_H

#include <core/resource.h>
// Generator based on a script, like GDScript, C# or NativeScript.
// The script is expected to properly handle multithreading.
class TreeGen : public Resource {
	GDCLASS(TreeGen, Resource)
public:
	TreeGen(){};
	Dictionary gen(Dictionary treedetails ,float w,float h,Transform home);
    Dictionary addtreebranch(Dictionary inf,Dictionary treedetails);
private:
	static void _bind_methods();
};

#endif // TREE_GEN_H
