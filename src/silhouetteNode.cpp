//
//  silhouetteNode.cpp
//  murmur
//
//  Created by Julien on 05/05/13.
//
//

#include "silhouetteNode.h"


//--------------------------------------------------------------
SilhouetteNode::SilhouetteNode(ofImage* pImage, float height)
{
    mp_image = pImage;
    m_height = height;
}


//--------------------------------------------------------------
void SilhouetteNode::customDraw()
{
    if (mp_image)
    {
        ofTexture& tex = mp_image->getTextureReference();
        float ratio = mp_image->getWidth() / mp_image->getHeight();
        float w = ratio*m_height;
        ofPushMatrix();
        ofScale(1.0f, -1.0f);
        ofSetColor(0,0,0,255);
        tex.draw(-w/2.0f,-m_height,w,m_height);
        ofPopMatrix();
    }
}