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

class VolumeController
{
public:
    explicit VolumeController();
    virtual ~VolumeController();

    int getSpeakerVolume();
    bool setSpeakerVolume(int volumePercent);

    bool isSpeakerMuted();
    bool setSpeakerMuted(bool mute);

    int getMicVolume();
    bool setMicVolume(int volumePercent);

    bool isMicMuted();
    bool setMicMuted(bool mute);

private:
    IAudioEndpointVolume* getEndpointVolume(bool isSpeaker);

private:
    IAudioEndpointVolume *m_speakerEndpointVolume;
    IAudioEndpointVolume *m_micEndpointVolume;
};

};
#endif
