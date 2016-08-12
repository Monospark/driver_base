#pragma once

#include "tracked_device.h"

class TrackingReference : public TrackedDevice
{
public:
    const struct Data
    {
        float fovLeft;
        float fovRight;
        float fovTop;
        float fovBottom;
        float minRange;
        float maxRange;
        std::string modelLabel;
    } trackingReferenceData;

    TrackingReference(
        const std::vector<std::shared_ptr<Component>>& components,
        const TrackedDevice::Data& trackedDeviceData,
        const Data& trackingReferenceData,
        const vr::DriverPose_t& pose);

protected:
    int32_t getInt32Property(vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* error) override;
    float getFloatProperty(vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* error) override;
    std::string getStringProperty(vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* error) override;
};
