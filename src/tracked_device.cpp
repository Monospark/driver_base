#include "tracked_device.h"
#include "logger.h"

TrackedDevice::TrackedDevice(
    const std::vector<std::shared_ptr<Component>>& components,
    const Data& trackedDeviceData)
    : trackedDeviceData(trackedDeviceData)
    , pose(pose)
    , objectId(vr::k_unTrackedDeviceIndexInvalid)
    , components(components) {
}

TrackedDevice::~TrackedDevice() {}

bool TrackedDevice::getBoolProperty(vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* error)
{
    *error = vr::TrackedProp_Success;
    switch (prop)
    {
    case vr::Prop_WillDriftInYaw_Bool:
        return trackedDeviceData.willDriftInYaw;
    case vr::Prop_DeviceIsWireless_Bool:
        return trackedDeviceData.wireless;
    case vr::Prop_DeviceIsCharging_Bool:
        return trackedDeviceData.charging;
    case vr::Prop_Firmware_UpdateAvailable_Bool:
        return trackedDeviceData.firmwareUpdateAvailable;
    case vr::Prop_Firmware_ManualUpdate_Bool:
        return trackedDeviceData.manualFirmwareUpdate;
    case vr::Prop_BlockServerShutdown_Bool:
        return trackedDeviceData.blockServerShutdown;
    case vr::Prop_CanUnifyCoordinateSystemWithHmd_Bool:
        return trackedDeviceData.canUnifyCoordinateSystemWithHmd;
    case vr::Prop_ContainsProximitySensor_Bool:
        return trackedDeviceData.containsProximitySensor;
    case vr::Prop_DeviceProvidesBatteryStatus_Bool:
        return trackedDeviceData.hasBatteryStatus;
    case vr::Prop_DeviceCanPowerOff_Bool:
        return trackedDeviceData.canPowerOff;
    case vr::Prop_HasCamera_Bool:
        return trackedDeviceData.hasCamera;
    case vr::Prop_Firmware_ForceUpdateRequired_Bool:
        return trackedDeviceData.forceFirmwareUpdateRequired;
    default:
        *error = vr::TrackedProp_UnknownProperty;
        return false;
    }
}

float TrackedDevice::getFloatProperty(vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* error)
{
    *error = vr::TrackedProp_Success;
    switch (prop) {
    case vr::Prop_DeviceBatteryPercentage_Float:
        return trackedDeviceData.batteryPercentage;
    default:
        *error = vr::TrackedProp_UnknownProperty;
        return 0.0f;
    }
}

int32_t TrackedDevice::getInt32Property(vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* error)
{
    *error = vr::TrackedProp_Success;
    switch (prop) {
    case vr::Prop_DeviceClass_Int32:
        return trackedDeviceData.deviceClass;
    default:
        *error = vr::TrackedProp_UnknownProperty;
        return 0;
    }
}

uint64_t TrackedDevice::getUint64Property(vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* error)
{
    *error = vr::TrackedProp_Success;
    switch (prop) {
    case vr::Prop_HardwareRevision_Uint64:
        return trackedDeviceData.hardwareRevisionNumber;
    case vr::Prop_FirmwareVersion_Uint64:
        return trackedDeviceData.firmwareVersion;
    case vr::Prop_FPGAVersion_Uint64:
        return trackedDeviceData.fpgaVersion;
    case vr::Prop_VRCVersion_Uint64:
        return trackedDeviceData.vrcVersion;
    case vr::Prop_RadioVersion_Uint64:
        return trackedDeviceData.radioVersion;
    case vr::Prop_DongleVersion_Uint64:
        return trackedDeviceData.dongleVersion;
    default:
        *error = vr::TrackedProp_UnknownProperty;
        return 0;
    }
}

std::string TrackedDevice::getStringProperty(vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* error)
{
    *error = vr::TrackedProp_Success;
    switch (prop) {
    case vr::Prop_TrackingSystemName_String:
        return trackedDeviceData.systemName;
    case vr::Prop_ModelNumber_String:
        return trackedDeviceData.modelNumber;
    case vr::Prop_SerialNumber_String:
        return trackedDeviceData.serialNumber;
    case vr::Prop_RenderModelName_String:
        return trackedDeviceData.renderModelName;
    case vr::Prop_ManufacturerName_String:
        return trackedDeviceData.manufacturerName;
    case vr::Prop_TrackingFirmwareVersion_String:
        return trackedDeviceData.trackingFirmwareVersion;
    case vr::Prop_HardwareRevision_String:
        return trackedDeviceData.hardwareRevision;
    case vr::Prop_Firmware_ManualUpdateURL_String:
        return trackedDeviceData.manualFirmwareUpdateUrl;
    case vr::Prop_Firmware_ProgrammingTarget_String:
        return trackedDeviceData.firmwareProgrammingTarget;
    case vr::Prop_DriverVersion_String:
        return trackedDeviceData.driverVersion;
    default:
        *error = vr::TrackedProp_UnknownProperty;
        return "";
    }
}

vr::HmdMatrix34_t TrackedDevice::getMatrix34Property(vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* error)
{
    *error = vr::TrackedProp_Success;
    switch (prop) {
    case vr::Prop_StatusDisplayTransform_Matrix34:
        return trackedDeviceData.statusDisplayTransform;
    default:
        *error = vr::TrackedProp_UnknownProperty;
        return {};
    }
}

void TrackedDevice::onActivate() {}

void TrackedDevice::onDeactivate() {}

void TrackedDevice::onPowerOff() {}

void TrackedDevice::update() {}

vr::EVRInitError TrackedDevice::Activate(uint32_t unObjectId) {
    objectId = unObjectId;
    onActivate();
    Logger::get().log("Activated %s with id %d\n", trackedDeviceData.modelNumber.c_str(), unObjectId);
    return vr::VRInitError_None;
}

void TrackedDevice::Deactivate() {
    objectId = vr::k_unTrackedDeviceIndexInvalid;
    onDeactivate();
    Logger::get().log("Deactivated %s\n", trackedDeviceData.modelNumber.c_str());
}

void TrackedDevice::PowerOff()
{
    onPowerOff();
    Logger::get().log("Powered off %s", trackedDeviceData.modelNumber.c_str());
}

void* TrackedDevice::GetComponent(const char* pchComponentNameAndVersion)
{
    for (std::shared_ptr<Component>& comp : components)
    {
        if (comp->getIdentifier() == pchComponentNameAndVersion)
        {
            return comp->getComponentPointer();
        }
    }
    return nullptr;
}

void TrackedDevice::DebugRequest(const char* pchRequest, char* pchResponseBuffer, uint32_t unResponseBufferSize)
{
    Logger::get().log(pchRequest);
    if (unResponseBufferSize >= 1)
    {
        pchResponseBuffer[0] = 0;
    }
}

vr::DriverPose_t TrackedDevice::GetPose()
{
    return pose;
}

uint32_t TrackedDevice::GetStringTrackedDeviceProperty(
    vr::ETrackedDeviceProperty prop,
    char* pchValue,
    uint32_t unBufferSize,
    vr::ETrackedPropertyError* pError)
{
    *pError = vr::TrackedProp_Success;
    std::string value = getStringProperty(prop, pError);
    if (*pError == vr::TrackedProp_Success)
    {
        if (value.size() + 1 > unBufferSize)
        {
            *pError = vr::TrackedProp_BufferTooSmall;
        }
        else
        {
            strcpy_s(pchValue, unBufferSize, value.c_str());
        }
        return static_cast<uint32_t>(value.size() + 1);
    }
    return 0;
}

bool TrackedDevice::GetBoolTrackedDeviceProperty(
    vr::ETrackedDeviceProperty prop,
    vr::ETrackedPropertyError* pError)
{
    *pError = vr::TrackedProp_Success;
    return getBoolProperty(prop, pError);
}

float TrackedDevice::GetFloatTrackedDeviceProperty(
    vr::ETrackedDeviceProperty prop,
    vr::ETrackedPropertyError* pError)
{
    *pError = vr::TrackedProp_Success;
    return getFloatProperty(prop, pError);
}

int32_t TrackedDevice::GetInt32TrackedDeviceProperty(
    vr::ETrackedDeviceProperty prop,
    vr::ETrackedPropertyError* pError)
{
    *pError = vr::TrackedProp_Success;
    return getInt32Property(prop, pError);
}

uint64_t TrackedDevice::GetUint64TrackedDeviceProperty(
    vr::ETrackedDeviceProperty prop,
    vr::ETrackedPropertyError* pError)
{
    *pError = vr::TrackedProp_Success;
    return getUint64Property(prop, pError);
}

vr::HmdMatrix34_t TrackedDevice::GetMatrix34TrackedDeviceProperty(
    vr::ETrackedDeviceProperty prop,
    vr::ETrackedPropertyError* pError)
{
    *pError = vr::TrackedProp_Success;
    return getMatrix34Property(prop, pError);
}


uint32_t TrackedDevice::getId() const
{
    return objectId;
}

const vr::DriverPose_t& TrackedDevice::getPose() const
{
    return pose;
}
