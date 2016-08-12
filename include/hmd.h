#pragma once

#include "tracked_device.h"

class Hmd : public TrackedDevice {
public:
    const struct Data {
        bool reportsTimeSinceVsync;
        float secondsFromVsyncToPhotons;
        float displayFrequency;
        float ipdMeters;
        uint64_t currentUniverseId;
        uint64_t PreviousUniverseId;
        uint64_t displayFirmwareVersion;
        bool onDesktop;
        int32_t displayMcType;
        float displayMcOffset;
        float displayMcScale;
        int32_t edidVendorId;
        std::string displayMcImageLeft;
        std::string displayMcImageRight;
        float displayGcBlackClamp;
        int32_t edidProductId;
        vr::HmdMatrix34_t cameraToHeadTransform;
        int32_t displayGcType;
        float displayGcOffset;
        float displayGcScale;
        float displayGcPrescale;
        std::string displayGcImage;
        float lensCenterLeftU;
        float lensCenterLeftV;
        float lensCenterRightU;
        float lensCenterRightV;
        float userHeadToEyeDepthMeters;
        uint64_t cameraFirmwareVersion;
        std::string cameraFirmwareDescription;
        uint64_t displayFpgaVersion;
        uint64_t displayBootloaderVersion;
        uint64_t displayHardwareVersion;
        uint64_t audioFirmwareVersion;
        int32_t cameraCompatibilityMode;
        float screenshotHorizontalFov;
        float screenshotVerticalFov;
        bool displaySuppressed;
    } hmdData;

    Hmd(
        const std::vector<std::shared_ptr<Component>>& components,
        const TrackedDevice::Data& trackedDeviceData,
        const Data& hmdData);

protected:
    bool getBoolProperty(vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* error) override;
    float getFloatProperty(vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* error) override;
    int32_t getInt32Property(vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* error) override;
    uint64_t getUint64Property(vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* error) override;
    std::string getStringProperty(vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* error) override;
    vr::HmdMatrix34_t getMatrix34Property(vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* error) override;
};