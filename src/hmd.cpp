#include "hmd.h"

Hmd::Hmd(
    const std::vector<std::shared_ptr<Component>>& components,
    const TrackedDevice::Data& trackedDeviceData,
    const Data& hmdData)
    : TrackedDevice(components, trackedDeviceData), hmdData(hmdData) {}

bool Hmd::getBoolProperty(vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* error)
{
    switch (prop)
    {
    case vr::Prop_ReportsTimeSinceVSync_Bool:
        return hmdData.reportsTimeSinceVsync;
    case vr::Prop_IsOnDesktop_Bool:
        return hmdData.onDesktop;
    case vr::Prop_DisplaySuppressed_Bool:
        return hmdData.displaySuppressed;
    default:
        return TrackedDevice::getBoolProperty(prop, error);
    }
}

float Hmd::getFloatProperty(vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* error)
{
    switch (prop)
    {
    case vr::Prop_SecondsFromVsyncToPhotons_Float:
        return hmdData.secondsFromVsyncToPhotons;
    case vr::Prop_DisplayFrequency_Float:
        return hmdData.displayFrequency;
    case vr::Prop_UserIpdMeters_Float:
        return hmdData.ipdMeters;
    case vr::Prop_DisplayMCOffset_Float:
        return hmdData.displayMcOffset;
    case vr::Prop_DisplayMCScale_Float:
        return hmdData.displayMcScale;
    case vr::Prop_DisplayGCBlackClamp_Float:
        return hmdData.displayGcBlackClamp;
    case vr::Prop_DisplayGCOffset_Float:
        return hmdData.displayGcOffset;
    case vr::Prop_DisplayGCScale_Float:
        return hmdData.displayGcScale;
    case vr::Prop_DisplayGCPrescale_Float:
        return hmdData.displayGcPrescale;
    case vr::Prop_LensCenterLeftU_Float:
        return hmdData.lensCenterLeftU;
    case vr::Prop_LensCenterLeftV_Float:
        return hmdData.lensCenterLeftV;
    case vr::Prop_LensCenterRightU_Float:
        return hmdData.lensCenterRightU;
    case vr::Prop_LensCenterRightV_Float:
        return hmdData.lensCenterRightV;
    case vr::Prop_UserHeadToEyeDepthMeters_Float:
        return hmdData.userHeadToEyeDepthMeters;
    case vr::Prop_ScreenshotHorizontalFieldOfViewDegrees_Float:
        return hmdData.screenshotHorizontalFov;
    case vr::Prop_ScreenshotVerticalFieldOfViewDegrees_Float:
        return hmdData.screenshotVerticalFov;
    default:
        return TrackedDevice::getFloatProperty(prop, error);
    }
}

int32_t Hmd::getInt32Property(vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* error)
{
    switch (prop)
    {
    case vr::Prop_DisplayMCType_Int32:
        return hmdData.displayMcType;
    case vr::Prop_EdidVendorID_Int32:
        return hmdData.edidVendorId;
    case vr::Prop_EdidProductID_Int32:
        return hmdData.edidProductId;
    case vr::Prop_DisplayGCType_Int32:
        return hmdData.displayGcType;
    case vr::Prop_CameraCompatibilityMode_Int32:
        return hmdData.cameraCompatibilityMode;
    default:
        return TrackedDevice::getInt32Property(prop, error);
    }
}

uint64_t Hmd::getUint64Property(vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* error)
{
    switch (prop)
    {
    case vr::Prop_CurrentUniverseId_Uint64:
        return hmdData.currentUniverseId;
    case vr::Prop_PreviousUniverseId_Uint64:
        return hmdData.PreviousUniverseId;
    case vr::Prop_DisplayFirmwareVersion_Uint64:
        return hmdData.displayFirmwareVersion;
    case vr::Prop_CameraFirmwareVersion_Uint64:
        return hmdData.cameraFirmwareVersion;
    case vr::Prop_DisplayFPGAVersion_Uint64:
        return hmdData.displayFpgaVersion;
    case vr::Prop_DisplayBootloaderVersion_Uint64:
        return hmdData.displayBootloaderVersion;
    case vr::Prop_DisplayHardwareVersion_Uint64:
        return hmdData.displayHardwareVersion;
    case vr::Prop_AudioFirmwareVersion_Uint64:
        return hmdData.audioFirmwareVersion;
    default:
        return TrackedDevice::getUint64Property(prop, error);
    }
}

std::string Hmd::getStringProperty(vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* error)
{
    switch (prop)
    {
    case vr::Prop_DisplayMCImageLeft_String:
        return hmdData.displayMcImageLeft;
    case vr::Prop_DisplayMCImageRight_String:
        return hmdData.displayMcImageRight;
    case vr::Prop_DisplayGCImage_String:
        return hmdData.displayGcImage;
    case vr::Prop_CameraFirmwareDescription_String:
        return hmdData.cameraFirmwareDescription;
    default:
        return TrackedDevice::getStringProperty(prop, error);
    }
}

vr::HmdMatrix34_t Hmd::getMatrix34Property(vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* error)
{
    switch (prop)
    {
    case vr::Prop_CameraToHeadTransform_Matrix34:
        return hmdData.cameraToHeadTransform;
    default:
        return TrackedDevice::getMatrix34Property(prop, error);
    }
}
