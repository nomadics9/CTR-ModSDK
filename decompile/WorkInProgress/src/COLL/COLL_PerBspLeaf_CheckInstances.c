#include <common.h>

void DECOMP_COLL_PerBspLeaf_CheckInstances(struct BSP *node, struct ScratchpadStruct *sps)
{
    int arraySize;
    struct BSP *bspArray = node->data.leaf.bspHitboxArray;
    struct BoundingBox *bbox;

    // if there are instances in this bsp
    if (bspArray != NULL)
    {
        bbox = bspArray->box;

        // check every instance hitbox until
        // end of list (null flag) is found
        while (bspArray->flag != NULL)
        {
            // 1F8001CC
            arraySize = *(int*)&sps->unk4C[0x78] - 1;
            for (;arraySize >= 0; arraySize--)
            {
                // look for member in 1F800190 array
                if (bspArray == (struct BSP **)(sps->unk4C[0x3c])[arraySize])
                    goto LAB_8001d750;
            }

            if ((((
                    // if data is invalid
                    (
                        // if collision for instance is disabled
                        ((bspArray->flag & 0x80) == 0) ||
                        // if bspHitbox.InstDef doesn't exist
                        (bspArray->data.hitbox.instDef == NULL)
                    ) 
                    
                    ||

                    // if data is valid

                    // allows drawing flag is enabled
                    ((bspArray->data.hitbox.instDef->ptrInstance->flags & 0xf) != 0)
                ) &&

                // compare bsp boundingbox to scratchpad boundingbox
                ((sps->bbox.min[0] <= bbox->max[0] &&

                (bbox->min[0] <= sps->bbox.max[0])))) &&

                ((sps->bbox.min[1] <= bbox->max[1] &&

                ((bbox->min[1] <= sps->bbox.max[1] &&

                (sps->bbox.min[2] <= bbox->max[2])))))) &&

                (bbox->min[2] <= sps->bbox.max[2]))
            {
                // check with collision for this instance
                COLL_Instance(sps, bspArray);
            }

        LAB_8001d750:

            // go to next in list, and check for null flag
            bspArray += 8;
            bbox += 8;
        }
    }
}