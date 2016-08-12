#include "display_component.h"

DisplayComponent::DisplayComponent(int32_t windowX, int32_t windowY, int32_t windowWidth,
    int32_t windowHeight, bool onDesktop, bool realDisplay, int32_t renderWidth, int32_t renderHeight)
    : Component(vr::IVRDisplayComponent_Version)
    , windowX(windowX)
    , windowY(windowY)
    , windowWidth(windowWidth)
    , windowHeight(windowHeight)
    , onDesktop(onDesktop)
    , realDisplay(realDisplay)
    , renderWidth(renderWidth)
    , renderHeight(renderHeight) {}

DisplayComponent::~DisplayComponent() {}

void* DisplayComponent::getComponentPointer() {
    return static_cast<IVRDisplayComponent*>(this);
}

void DisplayComponent::GetWindowBounds(int32_t* pnX, int32_t* pnY, uint32_t* pnWidth, uint32_t* pnHeight)
{
    *pnX = windowX;
    *pnY = windowY;
    *pnWidth = windowWidth;
    *pnHeight = windowHeight;
}

bool DisplayComponent::IsDisplayOnDesktop()
{
    return onDesktop;
}

bool DisplayComponent::IsDisplayRealDisplay()
{
    return realDisplay;
}

void DisplayComponent::GetRecommendedRenderTargetSize(uint32_t* pnWidth, uint32_t* pnHeight)
{
    *pnWidth = renderWidth;
    *pnHeight = renderHeight;
}

void DisplayComponent::GetEyeOutputViewport(
    vr::EVREye eEye, uint32_t* pnX, uint32_t* pnY, uint32_t* pnWidth, uint32_t* pnHeight)
{
    *pnY = 0;
    *pnWidth = windowWidth / 2;
    *pnHeight = windowHeight;

    if (eEye == vr::Eye_Left) {
        *pnX = 0;
    }
    else
    {
        *pnX = windowWidth / 2;
    }
}

void DisplayComponent::GetProjectionRaw(vr::EVREye eEye, float* pfLeft, float* pfRight, float* pfTop, float* pfBottom)
{
    *pfLeft = -1.0;
    *pfRight = 1.0;
    *pfTop = -1.0;
    *pfBottom = 1.0;
}

vr::DistortionCoordinates_t DisplayComponent::ComputeDistortion(vr::EVREye eEye, float fU, float fV)
{
    vr::DistortionCoordinates_t coordinates;
    coordinates.rfBlue[0] = fU;
    coordinates.rfBlue[1] = fV;
    coordinates.rfGreen[0] = fU;
    coordinates.rfGreen[1] = fV;
    coordinates.rfRed[0] = fU;
    coordinates.rfRed[1] = fV;
    return coordinates;
}
