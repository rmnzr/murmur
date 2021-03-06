//
//  animationsFactory.cpp
//  murmur
//
//  Created by Julien on 16/05/13.
//
//

#include "animationsFactory.h"
#include "animations.h"

#include "animationWaveShader.h"
#include "animationParticlesMega2.h"
#include "animationBox2D.h"
#include "animationTunnel.h"

Animation* AnimationsFactory::create(string name)
{
    Animation* pAnimation=0;

    if (name == "shaderWave")
        pAnimation = new AnimationShaderWave(name);
/*    if (name == "particlesMega")
        pAnimation = new AnimationParticlesMega(name);
*/
    else if (name == "particlesMega2")
        pAnimation = new AnimationParticlesMega2(name);
    else if (name == "box2DCircles")
        pAnimation = new AnimationBox2D_circles(name);
    else if (name == "tunnel")
        pAnimation = new AnimationTunnel(name);
    
    return pAnimation;
}