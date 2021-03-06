//
//  soundManager.cpp
//  murmur
//
//  Created by Julien on 16/05/13.
//
//

#include "soundManager.h"

//--------------------------------------------------------------
SoundManager* SoundManager::smp_instance = 0;

//--------------------------------------------------------------
SoundManager::SoundManager()
{
    mp_soundMain = 0;
    m_soundMainVolumeMin    = 0.0f;
    m_soundMainVolumeMax    = 1.0f;
    m_soundMainVolume       = 1.0f;
}

//--------------------------------------------------------------
SoundManager* SoundManager::instance()
{
	if (smp_instance == 0)
		smp_instance = new SoundManager();
	return smp_instance;
}

//--------------------------------------------------------------
void SoundManager::setup()
{
	ofDirectory dirSounds("Sounds");
	if (dirSounds.exists())
	{
		dirSounds.listDir();
		printf("DIR %s [%d file(s)]\n", dirSounds.path().c_str(),dirSounds.size());
        
		vector<ofFile> files = dirSounds.getFiles();
		vector<ofFile>::iterator it;
		for (it = files.begin(); it != files.end(); ++it)
        {
            if ((*it).getExtension() == "mp3" || (*it).getExtension() == "wav")
			{
                string filename = (*it).getFileName();

                printf("- [%s]\n", filename.c_str());
                
                SoundPlayer* pSoundPlayer = new SoundPlayer(filename);
                pSoundPlayer->loadSound( "Sounds/"+filename );
                pSoundPlayer->setLoop(false);
                pSoundPlayer->setMultiPlay(true);

                m_listSoundPlayer.push_back( pSoundPlayer );
            }
        }
    }
    
    
    mp_soundMain = getSoundPlayer("main.mp3");
    if (mp_soundMain == 0)
        mp_soundMain = getSoundPlayer("main.wav");
    if (mp_soundMain)
    {
//        mp_soundMain->setLoop(true);
//        mp_soundMain->play();
    }
}

//--------------------------------------------------------------
void SoundManager::update()
{
    ofSoundUpdate();
}

//--------------------------------------------------------------
void SoundManager::playSound(string name, bool isLoop, float volume)
{
    SoundPlayer* pSoundPlayer = getSoundPlayer(name);
    if (pSoundPlayer){
        pSoundPlayer->play();
        pSoundPlayer->setLoop(isLoop);
        pSoundPlayer->setVolume(volume);

        //printf("SoundManager::playSound, name=%s, isLoop=%s, volume=%.2f\n", name.c_str(), isLoop ? "true" : "false", volume);
    }
}

//--------------------------------------------------------------
void SoundManager::setVolume(string name, float volume)
{
    SoundPlayer* pSoundPlayer = getSoundPlayer(name);
    if (pSoundPlayer)
        pSoundPlayer->setVolume(volume);
}

//--------------------------------------------------------------
void SoundManager::setVolumeAll(float volume)
{
    vector< SoundPlayer* >::iterator it = m_listSoundPlayer.begin();
    for ( ; it != m_listSoundPlayer.end() ; ++it)
        (*it)->setVolume(volume);
}

//--------------------------------------------------------------
void SoundManager::stopAll()
{
    vector< SoundPlayer* >::iterator it = m_listSoundPlayer.begin();
    for ( ; it != m_listSoundPlayer.end() ; ++it)
        (*it)->stop();
}

//--------------------------------------------------------------
SoundPlayer* SoundManager::getSoundPlayer(string name)
{
    vector< SoundPlayer* >::iterator it = m_listSoundPlayer.begin();
    for ( ; it != m_listSoundPlayer.end() ; ++it)
    {
        if ( (*it)->m_name == name)
            return *it;
    }
    return 0;
}

//--------------------------------------------------------------
void SoundManager::activateSoundMain(bool is)
{
    if (mp_soundMain)
    {
        if (is){
            mp_soundMain->setLoop(true);
            mp_soundMain->play();
        }
        else
            mp_soundMain->stop();
    }
}

//--------------------------------------------------------------
void SoundManager::setVolumeSoundMain(float vol)
{
    m_soundMainVolume = vol;
    if (mp_soundMain)
        mp_soundMain->setVolume(vol);
}

//--------------------------------------------------------------
void SoundManager::setVolumeSoundMainNormalized(float t)
{
    setVolumeSoundMain( ofLerp(m_soundMainVolumeMin, m_soundMainVolumeMax, t ) );
}



