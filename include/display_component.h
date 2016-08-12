#pragma once

#include "component.h"
#include <openvr_driver.h>

class DisplayComponent final : public Component, public vr::IVRDisplayComponent
{
public:
    DisplayComponent(int32_t windowX, int32_t windowY, int32_t windowWidth, int32_t windowHeight,
        bool onDesktop, bool realDisplay, int32_t renderWidth, int32_t renderHeight);
    ~DisplayComponent() override;

private:
    void* getComponentPointer() override;
    void GetWindowBounds(int32_t* pnX, int32_t* pnY, uint32_t* pnWidth, uint32_t* pnHeight) override;
    bool IsDisplayOnDesktop() override;
    bool IsDisplayRealDisplay() override;
    void GetRecommendedRenderTargetSize(uint32_t* pnWidth, uint32_t* pnHeight) override;
    void GetEyeOutputViewport(vr::EVREye eEye, uint32_t* pnX, uint32_t* pnY, uint32_t* pnWidth, uint32_t* pnHeight) override;
    void GetProjectionRaw(vr::EVREye eEye, float* pfLeft, float* pfRight, float* pfTop, float* pfBottom) override;
    vr::DistortionCoordinates_t ComputeDistortion(vr::EVREye eEye, float fU, float fV) override;

    int32_t windowX;
    int32_t windowY;
    int32_t windowWidth;
    int32_t windowHeight;
    bool onDesktop;
    bool realDisplay;
    int32_t renderWidth;
    int32_t renderHeight;
};
