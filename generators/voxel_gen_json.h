#ifndef VOXEL_GEN_JSON_H
#define VOXEL_GEN_JSON_H

#include "voxel_generator.h"
// Generator based on a script, like GDScript, C# or NativeScript.
// The script is expected to properly handle multithreading.
    struct VParameters {
            int scale=1;
            float hsc = 1.0;
        };
    class VoxelGenJson : public zylann::voxel ::VoxelGenerator {
        GDCLASS(VoxelGenJson, zylann::voxel ::VoxelGenerator)
    public:
        VoxelGenJson();

        zylann::voxel::VoxelGenerator::Result generate_block(zylann::voxel::VoxelGenerator::VoxelQueryData &input) override;
        int get_used_channels_mask() const override;

        void set_scale(int scale);
        int get_scale();
        void set_hsc(float hsc);
        float get_hsc();

    private:
        static void _bind_methods();
    

        VParameters _parameters;
        RWLock _parameters_lock;
    };


#endif // VOXEL_GEN_JSON_H
