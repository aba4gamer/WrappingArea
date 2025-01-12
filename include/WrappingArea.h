#pragma once
#include "syati.h"

struct WrappingAreaPositions {
    f32 rightX;
    f32 leftX;
    f32 topY;
    f32 bottomY;
    f32 frontZ;
    f32 backZ;
};

class WrappingArea : public AreaObj
{
public:
    WrappingArea(const char *pName);
    virtual void init(const JMapInfoIter &rIter);
    virtual void movement();
    void calcWarpPositions();
    void tryWarpPlayer();

    TVec3f mAreaScale;
    TVec3f mCenterPos;
    bool mEnabled;
    bool mWarpX;
    bool mWarpY;
    bool mWarpZ;
    WrappingAreaPositions mPositions;
};
