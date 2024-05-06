#pragma once
/*
    olcPGEX_MiniAudio.h

    +-------------------------------------------------------------+
    |         OneLoneCoder Pixel Game Engine Extension            |
    |                     MiniAudio v1.4                          |
    +-------------------------------------------------------------+

    NOTE: UNDER ACTIVE DEVELOPMENT - THERE MAY BE BUGS/GLITCHES

    What is this?
    ~~~~~~~~~~~~~
    This extension abstracts the very robust and powerful miniaudio
    library. It provides simple loading and playback of WAV and MP3
    files. Because it's built on top of miniaudio, it requires next
    to no addictional build configurations in order to be built
    for cross-platform.

    License (OLC-3)
    ~~~~~~~~~~~~~~~

    Copyright 2023 Moros Smith <moros1138@gmail.com>

    Redistribution and use in source and binary forms, with or without modification,
    are permitted provided that the following conditions are met:

    1. Redistributions or derivations of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.

    2. Redistributions or derivative works in binary form must reproduce the above
    copyright notice. This list of conditions and the following	disclaimer must be
    reproduced in the documentation and/or other materials provided with the distribution.

    3. Neither the name of the copyright holder nor the names of its contributors may
    be used to endorse or promote products derived from this software without specific
    prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS	"AS IS" AND ANY
    EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
    OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
    SHALL THE COPYRIGHT	HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
    INCIDENTAL,	SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
    TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
    BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
    CONTRACT, STRICT LIABILITY, OR TORT	(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
    ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
    SUCH DAMAGE.

    Links
    ~~~~~
    YouTube:	https://www.youtube.com/@Moros1138
    GitHub:		https://www.github.com/Moros1138
    Homepage:	https://www.moros1138.com
*/

#if defined (__ANDROID__)||(__APPLE__)

#include "olcPixelGameEngine_Mobile.h"
#else

#include "olcPixelGameEngine.h"
#endif // defined (__ANDROID__) || (__APPLE__)
#include <exception>

#ifdef OLC_PGEX_MINIAUDIO
#define MINIAUDIO_IMPLEMENTATION
#endif

#include "miniaudio.h"

namespace olc
{
    class MiniAudio : public olc::PGEX
    {
    public:
        std::string name = "olcPGEX_MiniAudio v1.4";

    public:
        MiniAudio();
        ~MiniAudio();
        virtual bool OnBeforeUserUpdate(float& fElapsedTime) override;
        static void data_callback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount);
        static bool backgroundPlay;

    public: // CONFIGURATION
        // set whether audio will continue playing when the app has lost focus
        void SetBackgroundPlay(bool state);

    public: // LOADING ROUTINES
        const int LoadSound(const std::string& path);
        void UnloadSound(const int id);

    public: // PLAYBACK CONTROLS
        // plays a sample, can be set to loop
        void Play(const int id, const bool loop = false);
        // plays a sound file, as a one off, and automatically unloads it
        void Play(const std::string& path);
        // stops a sample, rewinds to beginning
        void Stop(const int id);
        // pauses a sample, does not change position
        void Pause(const int id);
        //  toggle between play and pause
        void Toggle(const int id, bool rewind = false);

    public: // SEEKING CONTROLS
        // seek to the provided position in the sound, by milliseconds
        void Seek(const int id, const unsigned long long milliseconds);
        // seek to the provided position in the sound, by float 0.f is beginning, 1.0f is end
        void Seek(const int id, float& location);
        // seek forward from current position by the provided time
        void Forward(const int id, const unsigned long long milliseconds);
        // seek forward from current position by the provided time
        void Rewind(const int id, const unsigned long long milliseconds);

    public: // MISC CONTROLS
        // set volume of a sound, 0.0f is mute, 1.0f is full
        void SetVolume(const int id, float& volume);
        // set pan of a sound, -1.0f is left, 1.0f is right, 0.0f is center
        void SetPan(const int id, float& pan);
        // set pitch of a sound, 1.0f is normal
        void SetPitch(const int id, float& pitch);

    public: // MISC INFORMATION
        // determine if a sound is playing
        bool IsPlaying(const int id);
        // gets the current position in the sound, in milliseconds
        unsigned long long GetCursorMilliseconds(const int id);
        // gets the current position in the sound, as a float between 0.0f and 1.0f
        float GetCursorFloat(const int id);

    public: // ADVANCED FEATURES for those who want to use more of miniaudio
        // gets the currently loaded persistent sounds
        const std::vector<ma_sound*>& GetSounds() const;
        // gets the currently loaded one-off sounds
        const std::vector<ma_sound*>& GetOneOffSounds() const;
        // gets a pointer to the ma_device
        const ma_device* GetDevice() const;
        // gets a pointer to the ma_engine
        const ma_engine* GetEngine() const;

    private:

        /*
            Soooo, i'm not going to spend a whole lot of time
            documenting miniaudio features, if you want to
            know more I invite you to visit their very very
            nicely documented webiste at:

            https://miniaud.io/docs/manual/index.html
        */

        ma_device device;
        ma_engine engine;
        ma_resource_manager resourceManager;

        // sample rate for the device and engine
        int sampleRate;
        // this is where the sounds are kept
        std::vector<ma_sound*> vecSounds;
        std::vector<ma_sound*> vecOneOffSounds;
    };

    /**
     * EXCEPTIONS, long story short. I needed to be able
     * to construct the PGEX in a state where it could
     * fail at runtime. If you have a better way of
     * accomplishing the PGEX pattern without using
     * exceptions, I'm open to suggestions!
    */
    struct MiniAudioDeviceException : public std::exception
    {
        const char* what() const throw()
        {
            return "Failed to initialize a device.";
        }
    };

    struct MiniAudioResourceManagerException : public std::exception
    {
        const char* what() const throw()
        {
            return "Failed to initialize the resource manager.";
        }
    };

    struct MiniAudioEngineException : public std::exception
    {
        const char* what() const throw()
        {
            return "Failed to initialize the audio engine.";
        }
    };

    struct MiniAudioSoundException : public std::exception
    {
        const char* what() const throw()
        {
            return "Failed to initialize a sound.";
        }
    };

}


#ifdef OLC_PGEX_MINIAUDIO
#undef OLC_PGEX_MINIAUDIO

namespace olc
{
    bool MiniAudio::backgroundPlay = false;

    MiniAudio::MiniAudio() : olc::PGEX(true)
    {
        sampleRate = 48000;

        ma_device_config deviceConfig = ma_device_config_init(ma_device_type_playback);
        deviceConfig.playback.format = ma_format_f32;
        deviceConfig.playback.channels = 2;
        deviceConfig.sampleRate = sampleRate;
        deviceConfig.dataCallback = MiniAudio::data_callback;
        deviceConfig.pUserData = &engine;

        if (ma_device_init(NULL, &deviceConfig, &device) != MA_SUCCESS)
            throw MiniAudioDeviceException();

        ma_resource_manager_config resourceManagerConfig = ma_resource_manager_config_init();
        resourceManagerConfig.decodedFormat = ma_format_f32;
        resourceManagerConfig.decodedChannels = 0;
        resourceManagerConfig.decodedSampleRate = sampleRate;

#ifdef __EMSCRIPTEN__
        resourceManagerConfig.jobThreadCount = 0;
        resourceManagerConfig.flags |= MA_RESOURCE_MANAGER_FLAG_NON_BLOCKING;
        resourceManagerConfig.flags |= MA_RESOURCE_MANAGER_FLAG_NO_THREADING;
#endif

        if (ma_resource_manager_init(&resourceManagerConfig, &resourceManager) != MA_SUCCESS)
            throw MiniAudioResourceManagerException();

        ma_engine_config engineConfig = ma_engine_config_init();
        engineConfig.pDevice = &device;
        engineConfig.pResourceManager = &resourceManager;

        if (ma_engine_init(&engineConfig, &engine) != MA_SUCCESS)
            throw MiniAudioEngineException();

        MiniAudio::backgroundPlay = false;
    }

    MiniAudio::~MiniAudio()
    {
        for (auto sound : vecSounds)
        {
            if (sound != nullptr)
            {
                ma_sound_uninit(sound);
                delete sound;
            }
        }

        ma_resource_manager_uninit(&resourceManager);

        ma_engine_uninit(&engine);
    }

    bool MiniAudio::OnBeforeUserUpdate(float& fElapsedTime)
    {
#ifdef __EMSCRIPTEN__
        ma_resource_manager_process_next_job(&resourceManager);
#endif

        for (int i = 0; i < vecOneOffSounds.size(); i++)
        {
            if (!ma_sound_is_playing(vecOneOffSounds.at(i)))
            {
                ma_sound_uninit(vecOneOffSounds.at(i));
                vecOneOffSounds.erase(vecOneOffSounds.begin() + i);
                break;
            }
        }

        return false;
    }

    void MiniAudio::data_callback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount)
    {

        if (!MiniAudio::backgroundPlay && !pge->IsFocused())
            return;

        ma_engine_read_pcm_frames((ma_engine*)(pDevice->pUserData), pOutput, frameCount, NULL);
    }

    void MiniAudio::SetBackgroundPlay(bool state)
    {
        MiniAudio::backgroundPlay = state;
    }

    const int MiniAudio::LoadSound(const std::string& path)
    {

        // create the sound
        ma_sound* sound = new ma_sound();

#if defined (__ANDROID__)
        // Android and iOS store their assets in a compressed file
        // We need to extract them so the miniAudio can play them
        std::string soundPath = path;

        //1: does the path exist?
        if (!std::filesystem::exists(soundPath))
        {
            //2: nope ok lets try to extract it
            std::string songFullPath = (std::string)olc::filehandler->GetInternalAppStorage() + soundPath;
            olc::rcode result = olc::filehandler->ExtractFileFromAssets(soundPath, songFullPath);

            switch (result) {

            case olc::rcode::NO_FILE:
                return -1;
                break;
            case olc::rcode::FAIL:
                return -1;
                break;
            case olc::rcode::OK:
                soundPath = songFullPath;
                break;
            default:
                break;
            }
        }

        // load it from the file and decode it
        if (ma_sound_init_from_file(&engine, soundPath.c_str(), MA_SOUND_FLAG_DECODE | MA_SOUND_FLAG_ASYNC, NULL, NULL, sound) != MA_SUCCESS)
            throw MiniAudioSoundException();
#else
        // load it from the file and decode it
        if (ma_sound_init_from_file(&engine, path.c_str(), MA_SOUND_FLAG_DECODE | MA_SOUND_FLAG_ASYNC, NULL, NULL, sound) != MA_SUCCESS)
            throw MiniAudioSoundException();
#endif //(__ANDROID__)

        // attempt to re-use an empty slot
        for (int i = 0; i < vecSounds.size(); i++)
        {
            if (vecSounds.at(i) == nullptr)
            {
                vecSounds.at(i) = sound;
                return i;
            }
        }

        // no empty slots, make more room!
        const int id = vecSounds.size();
        vecSounds.push_back(sound);

        return id;
    }

    void MiniAudio::UnloadSound(const int id)
    {
        ma_sound_uninit(vecSounds.at(id));
        delete vecSounds.at(id);
        vecSounds.at(id) = nullptr;
    }

    void MiniAudio::Play(const int id, const bool loop)
    {
        if (ma_sound_is_playing(vecSounds.at(id)))
        {
            ma_sound_seek_to_pcm_frame(vecSounds.at(id), 0);
            return;
        }

        ma_sound_set_looping(vecSounds.at(id), loop);
        ma_sound_start(vecSounds.at(id));
    }

    void MiniAudio::Play(const std::string& path)
    {
        // create the sound
        ma_sound* sound = new ma_sound();

#if defined (__ANDROID__)
        // Android and iOS store their assets in a compressed file
        // We need to extract them so the miniAudio can play them
        std::string soundPath = path;

        //1: does the path exist?
        if (!std::filesystem::exists(soundPath))
        {
            //2: nope ok lets try to extract it
            std::string songFullPath = (std::string)olc::filehandler->GetInternalAppStorage() + soundPath;
            olc::rcode result = olc::filehandler->ExtractFileFromAssets(soundPath, songFullPath);

            switch (result) {

            case olc::rcode::NO_FILE:
            case olc::rcode::FAIL:
                break;
            case olc::rcode::OK:
                soundPath = songFullPath;
                break;
            default:
                break;
            }
        }

        // load it from the file and decode it
        if (ma_sound_init_from_file(&engine, soundPath.c_str(), MA_SOUND_FLAG_DECODE | MA_SOUND_FLAG_ASYNC, NULL, NULL, sound) != MA_SUCCESS)
            throw MiniAudioSoundException();
#else
        // load it from the file and decode it
        if (ma_sound_init_from_file(&engine, path.c_str(), MA_SOUND_FLAG_DECODE | MA_SOUND_FLAG_ASYNC, NULL, NULL, sound) != MA_SUCCESS)
            throw MiniAudioSoundException();
#endif //(__ANDROID__)

        ma_sound_start(sound);
        vecOneOffSounds.push_back(sound);
    }

    void MiniAudio::Stop(const int id)
    {
        ma_sound_seek_to_pcm_frame(vecSounds.at(id), 0);
        ma_sound_stop(vecSounds.at(id));
    }

    void MiniAudio::Pause(const int id)
    {
        auto it = vecSounds.begin() + id;
        ma_sound_stop(vecSounds.at(id));
    }

    void MiniAudio::Toggle(const int id, bool rewind)
    {
        if (ma_sound_is_playing(vecSounds.at(id)))
        {
            ma_sound_stop(vecSounds.at(id));

            if (rewind)
                ma_sound_seek_to_pcm_frame(vecSounds.at(id), 0);

            return;
        }

        ma_sound_start(vecSounds.at(id));
    }

    void MiniAudio::Seek(const int id, const unsigned long long milliseconds)
    {
        unsigned long long frame = (milliseconds * engine.sampleRate) / 1000;

        ma_sound_seek_to_pcm_frame(vecSounds.at(id), frame);
    }

    void MiniAudio::Seek(const int id, float& location)
    {
        unsigned long long length;
        ma_sound_get_length_in_pcm_frames(vecSounds.at(id), &length);

        unsigned long long frame = length * location;

        ma_sound_seek_to_pcm_frame(vecSounds.at(id), frame);
    }

    void MiniAudio::Forward(const int id, const unsigned long long milliseconds)
    {
        unsigned long long cursor;
        ma_sound_get_cursor_in_pcm_frames(vecSounds.at(id), &cursor);

        unsigned long long frame = (milliseconds * engine.sampleRate) / 1000;
        ma_sound_seek_to_pcm_frame(vecSounds.at(id), cursor + frame);
    }

    void MiniAudio::Rewind(const int id, const unsigned long long milliseconds)
    {
        unsigned long long cursor;
        ma_sound_get_cursor_in_pcm_frames(vecSounds.at(id), &cursor);

        unsigned long long frame = (milliseconds * engine.sampleRate) / 1000;
        ma_sound_seek_to_pcm_frame(vecSounds.at(id), cursor - frame);
    }

    void MiniAudio::SetVolume(const int id, float& volume)
    {
        ma_sound_set_volume(vecSounds.at(id), volume);
    }

    void MiniAudio::SetPan(const int id, float& pan)
    {
        ma_sound_set_pan(vecSounds.at(id), pan);
    }

    void MiniAudio::SetPitch(const int id, float& pitch)
    {
        ma_sound_set_pitch(vecSounds.at(id), pitch);
    }

    unsigned long long MiniAudio::GetCursorMilliseconds(const int id)
    {
        unsigned long long cursor;
        ma_sound_get_cursor_in_pcm_frames(vecSounds.at(id), &cursor);

        cursor /= sampleRate;
        cursor /= 1000;

        return cursor;
    }

    bool MiniAudio::IsPlaying(const int id)
    {
        return ma_sound_is_playing(vecSounds.at(id));
    }

    float MiniAudio::GetCursorFloat(const int id)
    {
        unsigned long long cursor;
        ma_sound_get_cursor_in_pcm_frames(vecSounds.at(id), &cursor);

        unsigned long long length;
        ma_sound_get_length_in_pcm_frames(vecSounds.at(id), &length);

        return (float)cursor / length;
    }

    const std::vector<ma_sound*>& MiniAudio::GetSounds() const
    {
        return vecSounds;
    }

    const std::vector<ma_sound*>& MiniAudio::GetOneOffSounds() const
    {
        return vecOneOffSounds;
    }

    const ma_device* MiniAudio::GetDevice() const
    {
        return &device;
    }

    const ma_engine* MiniAudio::GetEngine() const
    {
        return &engine;
    }

} // olc

#endif
