#include "WrappingArea.h"

WrappingArea::WrappingArea(const char *pName) : AreaObj(pName)
{
    mEnabled = false;
    mWarpX = false;
    mWarpY = false;
    mWarpZ = false;
}

void WrappingArea::init(const JMapInfoIter &rIter)
{
    MR::getJMapInfoArg0NoInit(rIter, &mWarpX);
    MR::getJMapInfoArg1NoInit(rIter, &mWarpY);
    MR::getJMapInfoArg2NoInit(rIter, &mWarpZ);
    MR::getJMapInfoScale(rIter, &mAreaScale);
    AreaObj::init(rIter);
    MR::connectToSceneAreaObj(this);
    MR::getAreaCenterPos(&mCenterPos, this);
    calcWarpPositions();
}
void WrappingArea::calcWarpPositions () {
    mPositions = WrappingAreaPositions();
    mPositions.rightX = mCenterPos.x + 500 * mAreaScale.x,
    mPositions.leftX = mCenterPos.x - 500 * mAreaScale.x,
    mPositions.topY = mCenterPos.y + 1000 * mAreaScale.y, // This works different because the shape is not CubeCentered
    mPositions.bottomY = mCenterPos.y,
    mPositions.frontZ = mCenterPos.z + 500 * mAreaScale.z,
    mPositions.backZ = mCenterPos.z - 500 * mAreaScale.z;
    if (!mWarpX && !mWarpY && !mWarpZ)
        mWarpX = mWarpY = mWarpZ = true;
}

void WrappingArea::movement()
{
    if (mEnabled)
        tryWarpPlayer();

    if ((isValidSwitchA() && !isOnSwitchA()) || !isInVolume(*MR::getPlayerPos())) 
        mEnabled = false;
    else 
        mEnabled = true;
}

void WrappingArea::tryWarpPlayer()
{
    TVec3f *playerPos = MR::getPlayerPos();
    if (mWarpX)
    {
        if (playerPos->x > mPositions.rightX)
            playerPos->x = mPositions.leftX;
        else if (playerPos->x < mPositions.leftX)
            playerPos->x = mPositions.rightX;
    }
    if (mWarpY)
    {
        if (playerPos->y > mPositions.topY)
            playerPos->y = mPositions.bottomY;
        else if (playerPos->y < mPositions.bottomY)
            playerPos->y = mPositions.topY;
    }
    if (mWarpZ)
    {
        if (playerPos->z > mPositions.frontZ)
            playerPos->z = mPositions.backZ;
        else if (playerPos->z < mPositions.backZ)
            playerPos->z = mPositions.frontZ;
    }
}