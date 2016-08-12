#include "tracking_reference.h"


TrackingReference::TrackingReference(
    const std::vector<std::shared_ptr<Component>>& components,
    const TrackedDevice::Data& trackedDeviceData,
    const Data& trackingReferenceData,
    const vr::DriverPose_t& pose)
    : TrackedDevice(components, trackedDeviceData), trackingReferenceData(trackingReferenceData)
{
    TrackedDevice::pose = pose;
}

float TrackingReference::getFloatProperty(vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* error)
{
    switch (prop) {
    case vr::Prop_FieldOfViewLeftDegrees_Float:
        return trackingReferenceData.fovLeft;
    case vr::Prop_FieldOfViewRightDegrees_Float:
        return trackingReferenceData.fovRight;
    case vr::Prop_FieldOfViewTopDegrees_Float:
        return trackingReferenceData.fovTop;
    case vr::Prop_FieldOfViewBottomDegrees_Float:
        return trackingReferenceData.fovBottom;
    case vr::Prop_TrackingRangeMinimumMeters_Float:
        return trackingReferenceData.minRange;
    case vr::Prop_TrackingRangeMaximumMeters_Float:
        return trackingReferenceData.maxRange;
    default:
        return TrackedDevice::getFloatProperty(prop, error);
    }
}

int32_t TrackingReference::getInt32Property(vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* error)
{
    switch (prop) {
    case vr::Prop_DeviceClass_Int32:
        return vr::TrackedDeviceClass_TrackingReference;
    default:
        return TrackedDevice::getInt32Property(prop, error);
    }
}

std::string TrackingReference::getStringProperty(vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* error)
{
    switch (prop) {
    case vr::Prop_ModeLabel_String:
        return trackingReferenceData.modelLabel;
    default:
        return TrackedDevice::getStringProperty(prop, error);
    }
}
