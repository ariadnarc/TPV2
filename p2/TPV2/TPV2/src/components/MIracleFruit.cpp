#include "MiracleFruit.h"
#include "../sdlutils/SDLUtils.h"
#include "../ecs/Manager.h"
#include "../components/ImageWithFrames.h"

MiracleFruit::MiracleFruit() : 
	estadoMilagroso(false),
	miracleTime(0),
	lastUpdate(sdlutils().currRealTime()),
	img(),
	miracleFreq()
{
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

	if (estadoMilagroso) 
	{
		if (currentTime > lastUpdate + miracleTime)  // cuando pase miracleTime
		{
			estadoMilagroso = false;					// volvemos al estado normal
			lastUpdate = sdlutils().currRealTime();
			img->setImage(1, 4, 1, 1);			
		}
	}
	else 
	{
		if (currentTime > lastUpdate + miracleFreq)
		{
			estadoMilagroso = true;
			lastUpdate = sdlutils().currRealTime();
			img->setImage(1, 7, 1, 1);
		}
	}
}

