//
//  animationBox2D.h
//  murmur
//
//  Created by Julien on 20/05/13.
//
//

#pragma once

#include "animations.h"
#include "ofxBox2d.h"
#include "volumeAccum.h"

class AnimationBox2D : public Animation
{
    public:
        AnimationBox2D(string name);

    protected:
    
        float           m_volumeAccum;
        float           m_volumeAccumTarget;

        ofxBox2d		m_box2d;			  //	the box2d world
        void            createBox2D(float gx, float gy, float fps, bool isBounds, ofRectangle bounds);
        bool            m_isBox2DCreated;
        AnimationSoundPlayer m_soundPlayer;
};


class AnimationBox2D_circles : public AnimationBox2D
{
    public:
        AnimationBox2D_circles(string name);

    
        virtual void			VM_update				(float dt);
        virtual void			VM_draw					(float w, float h);
        virtual void            onNewPacket             (DevicePacket*, string deviceId, float x, float y);

        virtual void            createUICustom          ();

        vector<ofxBox2dCircle>  m_listCircles;
        float                   m_gravity;
        bool                    m_isCircleInflating;
        float                   m_circleSize;
        ofVec2f                 m_posAnchor;
        //VolumeAccum             m_volAccum;
        float                   m_volTrigger;
        float                   m_sizeMin;
        float                   m_sizeMax;
        float                   m_nbObjects;

};

/*

 ofxBox2dCircle circle;
 circle.setPhysics(3.0, 0.53, 0.1);
 circle.setup(box2d.getWorld(), mouseX, mouseY, r);
 circles.push_back(circle);
 
 
 */