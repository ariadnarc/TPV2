#include "MiracleFruit.h"
#include "../sdlutils/SDLUtils.h"
#include "../ecs/Manager.h"
#include "../components/ImageWithFrames.h"

MiracleFruit::MiracleFruit()
{
	milagros = false;
	miracleTime = 0;
	lastUpdate = sdlutils().currRealTime();
}

MiracleFruit::~MiracleFruit()
{
}

void MiracleFruit::initComponent()
{
	img = mngr_->getComponent<ImageWithFrames>(ent_);
	miracleFreq = sdlutils().rand().nextInt(10000, 20000); //tiempo que tarda en salir pera
	miracleTime = sdlutils().rand().nextInt(1000, 5000); //tiempo que está la pera
}

void MiracleFruit::update()
{
	int currentTime = sdlutils().currRealTime();
	if (milagros) 
	{
		if (currentTime > lastUpdate + miracleTime) 
		{
			milagros = false;
			lastUpdate = sdlutils().currRealTime();
			img->setImage(1, 4, 1, 1);
		}
	}
	else 
	{
		if (currentTime > lastUpdate + miracleFreq)
		{
			lastUpdate = sdlutils().currRealTime();
			img->setImage(1, 7, 1, 1);
		}
	}
}

