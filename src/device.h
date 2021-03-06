/*
 *  device.h
 *  murmur
 *
 *  Created by Julien on 10/04/13.
 *  Copyright 2013 2Roqs. All rights reserved.
 *
 */

#pragma once
#include "ofMain.h"
#include "oscSender.h"
#include "soundInput.h"

// ======================================================================================
class DevicePacket
{
    public:
        DevicePacket         ();

        void                  copy(DevicePacket* pPacket);
        float                 m_volume;
};


// ======================================================================================
class Device
{
	public:
		Device              (string id, int nbLEDs, float distLEDs);
        virtual ~Device ();
    
        // Identifiant du device + IP
        string              m_id;
        string              m_ip;
        string              getID(){return m_id;}
        string              getIP(){return m_ip;}
    
        // LEDs
        int                 m_nbLEDs;
        float               m_distLEDs;	// meters
        float               m_length;
        void                set     (string id, int nbLEDs, float distLEDs);
    
        int                 getNbLEDs(){return m_nbLEDs;}
        float               getDistLEDs(){return m_distLEDs;}
        float               getLength(){return m_length;}
    
        // Properties
        void                setSoundInputVolumeMax    (float v);
        void                setSoundInputVolumeMaxOSC (float v);
    
        void                setSoundInputVolHistorySize(int nb);
        void                setSoundInputVolHistorySizeOSC(int nb);

        float               getSoundInputVolumeMax();
        float               getSoundInputVolHistorySize();

        // Activity / Standby
        bool                m_isEnableStandbyMode;
        bool                m_isActive;
        float               m_timeInactivity;
        float               m_volHistoryTh;
        float               m_durationPreStandby;
    
        enum{
            EStandby_active              = 0,
            EStandby_pre_standby         = 1,
            EStandby_standby             = 2
        };
    
        int                 m_stateStandby;
        float               m_stateStandbyDuration;
        string              m_stateStandbyStr;
        float               m_timeStandby;
    
    
        void                enableStandbyMode(bool is=true);
        void                checkForActivity(float dt);
    
        void                setSoundInputVolHistoryTh(float th);
        void                setSoundInputVolHistoryThOSC(float th);
    
        void                setEnableStandbyMode(bool is);
        void                setEnableStandbyModeOSC(bool is);
    
        float               getSoundInputVolHistoryTh(){return m_volHistoryTh;}
        bool                getEnableStandbyMode(){return m_isEnableStandbyMode;}
    
        void               setTimeStandby(float v);
        void               setTimeStandbyOSC(float v);
        float               getTimeStandby(){return m_timeStandby;}
    
        void                setNbLEDsStandby        (int nb);
        void                setNbLEDsStandbyOSC     (int nb);
        int                 getNbLEDsStandby        (){return m_nbLEDsStandby;}
    
        void                setSpeedStandby         (float v);
        void                setSpeedStandbyOSC      (float v);
        float               getSpeedStandby         (){return m_angleSampleStandbySpeed;}
    
        float*              mp_sampleStandBy;
        int                 m_nbLEDsStandby;
        float               m_angleSampleStandby;
        float               m_angleSampleStandbySpeed;
    
        virtual void        sampleStandbyInput();
        virtual void        generateSampleStandBy(float dt);
    
        

    
        // Saving
        void                loadXML(string dir);
        void                saveXML(string dir);
    
        // Attach point (used only on server side)
        // normalized
        ofVec2f             m_pointSurface;
        void                setPointSurface(float xNorm, float yNorm);

        // OSC
        oscSender           m_oscSender;
    
        // Packets
        vector<DevicePacket*>   m_listPackets;
        virtual void        sampleSoundInput();
        virtual void        createPackets(int nb);
        virtual void        deletePackets();
        virtual void        sendPacketsOSC();
    
        virtual void        onReceivePacketBegin();
        virtual void        onReceivePacket(DevicePacket*);
        virtual void        onReceivePacketEnd();
    
        DevicePacket*       getLastPacket(){return m_listPackets[m_nbLEDs-1];}
    
        // Sound input
        SoundInput*         mp_soundInput;
        virtual void        startSoundInput (int deviceId, int nbChannels);
        virtual void        audioIn         (float * input, int bufferSize, int nChannels);
        virtual float       getWidthSoundInputVolume();
        virtual float       getHeightSoundInputVolume();
        virtual void        drawSoundInputVolume(float x, float y);
    
        // > only used on server side
        float               m_soundInputVolHistorySize;
        float               m_soundInputVolEmpiricalMax;
        
        // Interface
        virtual void        update(float dt);

    private:
        int                 m_indexPacketReceived;
        string              getPathXML(string dir);
    
};



// ======================================================================================
class DeviceManager
{
    public:
        DeviceManager       ();
        ~DeviceManager      ();

        void                addDevice           (Device*);
        Device*             getDeviceById       (string id);
        void                getDevicesListId    (vector<string>&);
        void                setDeviceCurrent    (Device*);
        Device*             setDeviceCurrent    (string deviceId);
        Device*             getDeviceCurrent    (){return mp_deviceCurrent;}
        void                saveDevicesXML      (string dir);
    
        vector<Device*>     m_listDevices;
    
    private:
        Device*             mp_deviceCurrent;

        vector<Device*>::iterator itDevices;
        void                deleteDevices       ();
};