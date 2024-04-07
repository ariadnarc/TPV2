#include "GhostSystem.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/ImageWithFrames.h"
#include "../components/Transform.h"

GhostSystem::GhostSystem()
{
}

GhostSystem::~GhostSystem()
{
}

void GhostSystem::initSystem()
{
}

void GhostSystem::update()
{
	auto ghostGr = mngr_->getEntities(ecs::grp::GHOSTS);

	//GENERACION DE GHOSTS
	if (genTime + lastTimeGenerated < sdlutils().virtualTimer().currTime() && !pcImmune &&
		ghostGr.size() < 10)
	{
		lastTimeGenerated = sdlutils().virtualTimer().currTime();
		addGhost();
	}



	//MOVIMIENTO
	//por cada elemento de ghost group
	for (auto& elem : ghostGr)
	{
		//pillamos transform del ghost
		auto ghostTr = mngr_->getComponent<Transform>(elem);

		int rand = sdlutils().rand().nextInt(1, 1000);

		if (rand < 5) 
		{
			//coge pos del pacman
			auto posPM = mngr_->getComponent<Transform>(mngr_->getHandler(ecs::hdlr::PACMAN))->pos_;
			
			//formula del enunciado para el movimiento del ghost
			ghostTr->vel_ = (posPM - ghostTr->pos_).normalize() * 1.1f;
		}
		//actualizamos pos del fantasma
		ghostTr->pos_ = ghostTr->pos_ + ghostTr->vel_;

		// check left/right borders
		if (ghostTr->pos_.getX() < 0) {
			ghostTr->pos_.setX(0.0f);
			ghostTr->vel_.set(0.0f, 0.0f);
		}
		else if (ghostTr->pos_.getX() + ghostTr->width_ > sdlutils().width()) {
			ghostTr->pos_.setX(sdlutils().width() - ghostTr->width_);
			ghostTr->vel_.set(0.0f, 0.0f);
		}

		// check upper/lower borders
		if (ghostTr->pos_.getY() < 0) {
			ghostTr->pos_.setY(0.0f);
			ghostTr->vel_.set(0.0f, 0.0f);
		}
		else if (ghostTr->pos_.getY() + ghostTr->height_ > sdlutils().height()) {
			ghostTr->pos_.setY(sdlutils().height() - ghostTr->height_);
			ghostTr->vel_.set(0.0f, 0.0f);
		}
	}

}

void GhostSystem::recieve(const Message&)
{
}

void GhostSystem::addGhost()
{
	esquina = sdlutils().rand().nextInt(0, 4);
	Vector2D pos;
	switch (esquina)
	{
	case 0: //arriba izquierda
		pos = Vector2D(0, 0);
		break;
	case 1:
		pos = Vector2D(sdlutils().width(), 0);
		break;
	case 2:
		pos = Vector2D(0, sdlutils().height());
		break;
	default:
		pos = Vector2D(sdlutils().width(), sdlutils().height());
		break;
	}

	auto ghost = mngr_->addEntity(ecs::grp::GHOSTS);
	mngr_->addComponent<Transform>(ghost, pos, Vector2D(0, 0), 50, 50, 0); //pos_(), vel_(), width_(), height_(), rot_()
	mngr_->addComponent<ImageWithFrames>(ghost, &sdlutils().images().at("spriteSheet"), 8, 8, 0, 0, 128, 128, 4, 0, 1, 8);
	
}
