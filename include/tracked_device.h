#pragma once

#include <openvr/openvr_driver.h>
#include <vector>
#include "component.h"
#include <memory>

class TrackedDevice : public vr::ITrackedDeviceServerDriver
{
    friend class ServerDriver;

public:
    const struct Data
    {
        std::string systemName;
        std::string modelNumber;
        std::string serialNumber;
        std::string renderModelName;
        bool willDriftInYaw;
        std::string manufacturerName;
        std::string trackingFirmwareVersion;
        std::string hardwareRevision;
        std::string wirelessDongleDescriptions;
        std::string connectedWirelessDongle;
        bool wireless;
        bool charging;
        float batteryPercentage;
        vr::HmdMatrix34_t statusDisplayTransform;
        bool firmwareUpdateAvailable;
        bool manualFirmwareUpdate;
        std::string manualFirmwareUpdateUrl;
        uint64_t hardwareRevisionNumber;
        uint64_t firmwareVersion;
        uint64_t fpgaVersion;
        uint64_t vrcVersion;
        uint64_t radioVersion;
        uint64_t dongleVersion;
        bool blockServerShutdown;
        bool canUnifyCoordinateSystemWithHmd;
        bool containsProximitySensor;
        bool hasBatteryStatus;
        bool canPowerOff;
        std::string firmwareProgrammingTarget;
        int32_t deviceClass;
        bool hasCamera;
        std::string driverVersion;
        bool forceFirmwareUpdateRequired;
    } trackedDeviceData;

    TrackedDevice(
        const std::vector<std::shared_ptr<Component>>& components,
        const Data& trackedDeviceData);
    virtual ~TrackedDevice();

    uint32_t getId() const;

protected:
    vr::DriverPose_t pose;

    virtual bool getBoolProperty(vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* error);
    virtual float getFloatProperty(vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* error);
    virtual int32_t getInt32Property(vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* error);
    virtual uint64_t getUint64Property(vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* error);
    virtual std::string getStringProperty(vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* error);
    virtual vr::HmdMatrix34_t getMatrix34Property(vr::ETrackedDeviceProperty prop, vr::ETrackedPropertyError* error);

    virtual void onActivate();
    virtual void onDeactivate();
    virtual void onPowerOff();
    virtual bool update();

private:
    vr::EVRInitError Activate(uint32_t unObjectId) override;
    void Deactivate() override;
    void PowerOff() override;
    void* GetComponent(const char* pchComponentNameAndVersion) override;
    void DebugRequest(const char* pchRequest, char* pchResponseBuffer, uint32_t unResponseBufferSize) override;
    vr::DriverPose_t GetPose() override;

    uint32_t GetStringTrackedDeviceProperty(
        vr::ETrackedDeviceProperty prop,
        char * pchValue,
        uint32_t unBufferSize,
        vr::ETrackedPropertyError * pError) override;
    bool GetBoolTrackedDeviceProperty(
        vr::ETrackedDeviceProperty prop,
        vr::ETrackedPropertyError *pError) override;
    float GetFloatTrackedDeviceProperty(
        vr::ETrackedDeviceProperty prop,
        vr::ETrackedPropertyError * pError) override;
    int32_t GetInt32TrackedDeviceProperty(
        vr::ETrackedDeviceProperty prop,
        vr::ETrackedPropertyError * pError) override;
    uint64_t GetUint64TrackedDeviceProperty(
        vr::ETrackedDeviceProperty prop,
        vr::ETrackedPropertyError * pError) override;
    vr::HmdMatrix34_t GetMatrix34TrackedDeviceProperty(
        vr::ETrackedDeviceProperty prop,
        vr::ETrackedPropertyError * pError) override;

    uint32_t objectId;
    std::vector<std::shared_ptr<Component>> components;
};
