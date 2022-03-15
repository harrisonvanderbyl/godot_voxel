#ifndef VOXEL_GEN_HEX_H
#define VOXEL_GEN_HEX_H

#include "voxel_generator.h"
// Generator based on a script, like GDScript, C# or NativeScript.
// The script is expected to properly handle multithreading.
    struct Parameters {
            int seed = 0;
            int scale = 500;
            Vector3 center = Vector3(0,-2200,0);
            float radius = 2200;
        };
    class VoxelGenHex : public zylann::voxel ::VoxelGenerator {
        GDCLASS(VoxelGenHex, zylann::voxel ::VoxelGenerator)
    public:
        VoxelGenHex();

        zylann::voxel::VoxelGenerator::Result generate_block(zylann::voxel::VoxelGenerator::VoxelQueryData &input) override;
        int get_used_channels_mask() const override;

        Dictionary gen(Dictionary treedetails ,float w,float h,Transform3D home);
        Dictionary addtreebranch(Dictionary inf,Dictionary treedetails);
        Vector2 hextest(int bbx,int bby, int zoom2);
        float fract(float in);
        float get_hash( Vector2 c);
        float genMountainHeight(Vector2 location, int size,float ss,int lod,Dictionary d,Parameters params);
        float randf_range(float from, float to);
        Dictionary genDetails( Vector3 location, int plod,Parameters params);
        Array getMountainsAndSkyIslands(Dictionary d,int i,int k,Vector3 origin, int plod,int ys);
        Array getBlocks(Vector3 origin,int lod,int xs,int ys,int zs,Parameters params);
        Dictionary genDeets( Vector2 location,Vector2 b,int plod,Parameters params);
        int get_seed();
        void set_seed(int seed);
        int get_scale();
        void set_scale(int scale);
        Vector3 get_center();
        void set_center(Vector3 center);
        float get_radius();
        void set_radius(float radius);
    private:
        static void _bind_methods();
    

        Parameters _parameters;
        RWLock _parameters_lock;
    };


#endif // VOXEL_GEN_HEX_H
