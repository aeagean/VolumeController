/**********************************************************
 * Author: Qt君
 * 微信公众号: Qt君(首发)
 * Email:  2088201923@qq.com
 * QQ交流群: 732271126
 * LISCENSE: MIT
 ************************************************************/
#ifndef VOLUME_CONTROLLER_H
#define VOLUME_CONTROLLER_H

#include <windows.h>
#include <mmdeviceapi.h>
#include <audiopolicy.h>
#include <endpointvolume.h>

namespace QtHub {

#define VOLUME_RELEASE(x) if(x) { x->Release(); x = NULL; }

class VolumeController
{
public:
    explicit VolumeController()
    {
        m_speakerEndpointVolume = getEndpointVolume(true);
        m_micEndpointVolume     = getEndpointVolume(false);
    }

    virtual ~VolumeController()
    {
        VOLUME_RELEASE(m_speakerEndpointVolume)
        VOLUME_RELEASE(m_micEndpointVolume)
    }

    int getSpeakerVolume()
    {
        if (m_speakerEndpointVolume == NULL)
            return -1;

        float level;
        m_speakerEndpointVolume->GetMasterVolumeLevelScalar(&level);
        return int(level * 100);
    }

    bool setSpeakerVolume(int volumePercent)
    {
        if (m_speakerEndpointVolume == NULL)
            return false;

        return m_speakerEndpointVolume->SetMasterVolumeLevelScalar(float(volumePercent)/100, NULL) == S_OK;
    }

    bool isSpeakerMuted()
    {
        if (m_speakerEndpointVolume == NULL)
            return false;

        BOOL mute;
        m_speakerEndpointVolume->GetMute(&mute);
        return mute;
    }

    bool setSpeakerMuted(bool mute)
    {
        if (m_speakerEndpointVolume == NULL)
            return false;

        return m_speakerEndpointVolume->SetMute(mute, NULL) == S_OK;
    }

    int getMicVolume()
    {
        if (m_micEndpointVolume == NULL)
            return -1;

        float level;
        m_micEndpointVolume->GetMasterVolumeLevelScalar(&level);
        return int(level * 100);
    }

    bool setMicVolume(int volumePercent)
    {
        if (m_micEndpointVolume == NULL)
            return false;

        return m_micEndpointVolume->SetMasterVolumeLevelScalar(float(volumePercent)/100, NULL) == S_OK;
    }

    bool isMicMuted()
    {
        if (m_micEndpointVolume == NULL)
            return false;

        BOOL mute;
        m_micEndpointVolume->GetMute(&mute);
        return mute;
    }

    bool setMicMuted(bool mute)
    {
        if (m_micEndpointVolume == NULL)
            return false;

        return m_micEndpointVolume->SetMute(mute, NULL) == S_OK;
    }

private:
    IAudioEndpointVolume* getEndpointVolume(bool isSpeaker)
    {
        CoInitialize(NULL);

        IMMDeviceEnumerator     *enumerator = NULL;
        IMMDevice               *device = NULL;
        IAudioEndpointVolume    *endpoint= NULL;

        if ( CoCreateInstance(__uuidof(MMDeviceEnumerator),
                              NULL,
                              CLSCTX_INPROC_SERVER,
                              __uuidof(IMMDeviceEnumerator),
                              (void**)&enumerator) != S_OK )
        {
            goto EXIT;
        }

        if ( enumerator->GetDefaultAudioEndpoint(isSpeaker ? eRender : eCapture,
                                                 eConsole,
                                                 &device) != S_OK )
        {
            goto EXIT;
        }

        if ( device->Activate(__uuidof(IAudioEndpointVolume),
                              CLSCTX_INPROC_SERVER,
                              NULL,
                              (void **)&endpoint) != S_OK )
        {
            goto EXIT;
        }

        EXIT:
            VOLUME_RELEASE(enumerator)
            VOLUME_RELEASE(device)
            CoUninitialize();

        return endpoint;
    }

private:
    IAudioEndpointVolume *m_speakerEndpointVolume;
    IAudioEndpointVolume *m_micEndpointVolume;
};

};
#endif
