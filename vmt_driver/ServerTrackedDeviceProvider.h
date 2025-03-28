/*
MIT License

Copyright (c) 2020 gpsnmeajp

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#pragma once
#include "dllmain.h"

//OpenVRデバイスサーバー
//デバイスを管理する親であり、この下に子としてデバイスがぶら下がる
namespace VMTDriver {
    class ServerTrackedDeviceProvider : public IServerTrackedDeviceProvider
    {
    private:
        vector<TrackedDeviceServerDriver> m_devices{};
        IVRDriverContext* m_pDriverContext = nullptr;
        std::string m_installPath{ "" };
        std::vector<std::string> m_subscribeDevices;

    public:
        //内部向け
        vector<TrackedDeviceServerDriver>& GetDevices();
        TrackedDeviceServerDriver& GetDevice(int index);
        void DeviceResetAll();
        bool IsVMTDeviceIndex(int index);
        std::string GetInstallPath();
        std::string GetOpenVRDevicesString();
        void SubscribeDevice(std::string serial);
        void UnsubscribeDevice(std::string serial);
        int SearchDevice(vr::TrackedDevicePose_t* poses, string serial);
        void RequestRestart();

        //OpenVR向け
        virtual EVRInitError Init(IVRDriverContext* pDriverContext) override;
        virtual void Cleanup() override;
        virtual const char* const* GetInterfaceVersions() override;
        virtual void RunFrame() override;
        virtual bool ShouldBlockStandbyMode() override;
        virtual void EnterStandby() override;
        virtual void LeaveStandby() override;
    };
}