#include "server_driver.h"

#include "logger.h"

ServerDriver::~ServerDriver() {}

vr::EVRInitError ServerDriver::onInit(std::vector<std::unique_ptr<TrackedDevice>>& devices)
{
    return vr::VRInitError_None;
}

void ServerDriver::onShutdown() {}

void ServerDriver::onUpdate() {}

void ServerDriver::onStandbyEnter() {}

void ServerDriver::onStandbyLeave() {}

TrackedDevice* ServerDriver::getTrackedDeviceById(uint32_t id) const
{
    if (id >= trackedDevices.size()) {
        return nullptr;
    }

    return trackedDevices[id].get();
}

vr::EVRInitError ServerDriver::Init(
    vr::IDriverLog* pDriverLog,
    vr::IServerDriverHost* pDriverHost,
    const char* pchUserDriverConfigDir,
    const char* pchDriverInstallDir)
{
    driverHost = pDriverHost;
    Logger::init(pDriverLog);
    Logger::get().log("Starting up driver server\n");
    return onInit(trackedDevices);
}

void ServerDriver::Cleanup()
{
    onShutdown();
    Logger::get().log("Shutting down driver server\n");
    trackedDevices.clear();
}

const char* const* ServerDriver::GetInterfaceVersions()
{
    return vr::k_InterfaceVersions;
}

uint32_t ServerDriver::GetTrackedDeviceCount()
{
    return static_cast<uint32_t>(trackedDevices.size());
}

vr::ITrackedDeviceServerDriver* ServerDriver::GetTrackedDeviceDriver(uint32_t unWhich)
{
    return getTrackedDeviceById(unWhich);
}

vr::ITrackedDeviceServerDriver* ServerDriver::FindTrackedDeviceDriver(const char* pchId)
{
    for (const std::unique_ptr<TrackedDevice>& d : trackedDevices)
    {
        if (d->trackedDeviceData.serialNumber == pchId)
        {
            return d.get();
        }
    }
    return nullptr;
}

void ServerDriver::RunFrame()
{
    for (const std::unique_ptr<TrackedDevice>& d : trackedDevices)
    {
        if (d->update())
        {
            driverHost->TrackedDevicePoseUpdated(d->getId(), d->GetPose());
        }
    }
    onUpdate();
}

bool ServerDriver::ShouldBlockStandbyMode()
{
    return false;
}

void ServerDriver::EnterStandby()
{
    onStandbyEnter();
}

void ServerDriver::LeaveStandby()
{
    onStandbyLeave();
}
