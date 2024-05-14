#include "GhostSystem.h"
#include "ImmunitySystem.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/ImageWithFrames.h"
#include "../components/Transform.h"
#include "../components/Health.h"

void GhostSystem::initSystem()
{
	std::cout << "inicia el sistem GhostSystem" << std::endl;
}

void GhostSystem::update()
{
	auto ghostGr = mngr_->getEntities(ecs::grp::GHOSTS);

	///GENERACION DE GHOSTS
	if (genTime + lastTimeGenerated < sdlutils().virtualTimer().currTime() &&  // si 5000 + lastTimeGen es mas pequeño que current
		!blueGhosts &&														   // el pacman no esta en estado de inmunidad
		ghostGr.size() < 10 &&												   // hay menos de 10 fantasmas
		!(mngr_->getSystem<ImmunitySystem>()->getImmunity()))		           // pacman es vulnerable (no es inmune)
	{
		lastTimeGenerated = sdlutils().virtualTimer().currTime();
		addGhost();
	}

	/// MOVIMIENTO
	//por cada elemento de ghost group
	for (auto& elem : ghostGr)
	{
		// transform del ghost
		auto ghostTr = mngr_->getComponent<Transform>(elem);

		int rand = sdlutils().rand().nextInt(1, 1000);

		if (rand < 5) 
		{
			// coge pos del pacman
			auto posPM = mngr_->getComponent<Transform>(mngr_->getHandler(ecs::hdlr::PACMAN))->pos_;
			
			// movimiento del ghost (formula enunciado)
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

void GhostSystem::recieve(const Message& msg)
{
	switch (msg.id)
	{
	case _m_PACMAN_GHOST_COLLISION:
		//std::cout << "GhostSystem recibe _m_PACMAN_GHOST_COLLISION" << std::endl;

		if (msg.ghost_collision_data.blue) // Si el pacman es inmune (estaran los ghosts azules)
		{
			mngr_->setAlive(msg.ghost_collision_data.ghostToDelete, false); // borra ghost
			std::cout << mngr_->getEntities(ecs::grp::GHOSTS).size() << std::endl;
		}

		break;

	case _m_IMMUNITY_START:
		std::cout << "GhostSystem recibe _m_IMMUNITY_START" << std::endl;
		setBlue(true); // cuando el pacman esta en inmunidad, el ghost sera vulnerable/blue
		break;

	case _m_IMMUNITY_END:
		std::cout << "GhostSystem recibe _m_IMMUNITY_END" << std::endl;
		setBlue(false); // cuando el pacman NO esta en inmunidad, el ghost NO sera vulnerable/blue
		break;

	case _m_ROUND_START:
		//std::cout << "GhostSystem recibe _m_ROUND_START" << std::endl;
		lastTimeGenerated = sdlutils().virtualTimer().currTime();
		break;

	case _m_ROUND_OVER:
		std::cout << "GhostSystem recibe _m_ROUND_OVER" << std::endl;
		//deleteGhosts();
		break;

	case _m_GAME_OVER:
		//std::cout << "GhostSystem recibe _m_GAME_OVER" << std::endl;
		deleteGhosts();
		break;

	default:
		break;
	}
}

void GhostSystem::addGhost()
{
	esquina = sdlutils().rand().nextInt(0, 4);
	Vector2D posEsquina;
	switch (esquina)
	{
	case 0: //arriba izquierda
		posEsquina = Vector2D(0, 0);
		break;
	case 1:
		posEsquina = Vector2D(sdlutils().width(), 0);
		break;
	case 2:
		posEsquina = Vector2D(0, sdlutils().height());
		break;
	default:
		posEsquina = Vector2D(sdlutils().width(), sdlutils().height());
		break;
	}

	auto ghost = mngr_->addEntity(ecs::grp::GHOSTS);
	mngr_->addComponent<Transform>(ghost, posEsquina, Vector2D(0, 0), 50, 50, 0); //pos_(), vel_(), width_(), height_(), rot_()
	mngr_->addComponent<ImageWithFrames>(ghost, &sdlutils().images().at("spriteSheet"), 8, 8, 0, 0, 128, 128, 4, 0, 1, 8);
}

void GhostSystem::deleteGhosts()
{
	for (auto& e : mngr_->getEntities(ecs::grp::GHOSTS))
		mngr_->setAlive(e, false);
}

void GhostSystem::setBlue(bool b)
{
	blueGhosts = b;
	switch (b)
	{
	case true:
		for (auto& e : mngr_->getEntities(ecs::grp::GHOSTS)) {
			mngr_->getComponent<ImageWithFrames>(e)->setImage(3, 6, 1, 2);
		}
		break;

	case false:
		for (auto& e : mngr_->getEntities(ecs::grp::GHOSTS)) {
			mngr_->getComponent<ImageWithFrames>(e)->setImage(0, 4, 8, 1);
		}
		break;

	default:
		break;
	}
}
