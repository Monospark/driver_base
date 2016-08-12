#include "client_driver.h"

#include "logger.h"

ClientDriver::~ClientDriver() {}

vr::EVRInitError ClientDriver::onInit(vr::EClientDriverMode driverMode)
{
    return vr::VRInitError_None;
}

void ClientDriver::onShutdown() {}

bool ClientDriver::isHmdPresent()
{
    return false;
}

vr::HiddenAreaMesh_t ClientDriver::getHiddenAreaMesh(vr::EVREye eEye)
{
    return vr::HiddenAreaMesh_t{};
}

vr::EVRInitError ClientDriver::Init(
    vr::EClientDriverMode eDriverMode,
    vr::IDriverLog* pDriverLog,
    vr::IClientDriverHost* pDriverHost,
    const char* pchUserDriverConfigDir,
    const char* pchDriverInstallDir)
{
    clientDriverHost = pDriverHost;
    Logger::init(pDriverLog);
    Logger::get().log("Starting up client driver");
    return onInit(eDriverMode);
}

void ClientDriver::Cleanup()
{
    onShutdown();
}

bool ClientDriver::BIsHmdPresent(const char* pchUserDriverConfigDir)
{
    return isHmdPresent();
}

vr::EVRInitError ClientDriver::SetDisplayId(const char* pchDisplayId)
{
    return vr::VRInitError_None;
}

vr::HiddenAreaMesh_t ClientDriver::GetHiddenAreaMesh(vr::EVREye eEye)
{
    return getHiddenAreaMesh(eEye);
}

uint32_t ClientDriver::GetMCImage(
    uint32_t* pImgWidth,
    uint32_t* pImgHeight,
    uint32_t* pChannels,
    void* pDataBuffer,
    uint32_t unBufferLen)
{
    return 0;
}
