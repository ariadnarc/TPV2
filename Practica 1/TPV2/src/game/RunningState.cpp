// This file is part of the course TPV2@UCM - Samir Genaim

#include "RunningState.h"

#include "../components/Gun.h"
#include "../components/Transform.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../utils/Collisions.h"
#include "AsteroidsFacade.h"
#include "FighterFacade.h"
#include "BlackHoleFacade.h"
#include "MissileFacade.h"

#include "Game.h"

RunningState::RunningState(AsteroidsFacade *ast_mngr,
		FighterFacade *fighter_mngr, BlackHoleFacade *blackhole_mngr, MissileFacade* missile_mngr) :
		ihdlr(ih()), //
		ast_mngr_(ast_mngr), //
		fighter_mngr_(fighter_mngr), //
		blackhole_mngr_(blackhole_mngr),
		missile_mngr_(missile_mngr),
		lastTimeGeneratedAsteroids_() {
}

RunningState::~RunningState() {
}

void RunningState::leave() {
}

void RunningState::update() {

	auto mngr = Game::instance()->getMngr();

	// check if fighter won
	if (mngr->getEntities(ecs::grp::ASTEROIDS).size() == 0) {
		Game::instance()->setState(Game::GAMEOVER);
		return;
	}

	// move to pause if P pressed
	if (ihdlr.keyDownEvent() && ihdlr.isKeyDown(SDL_SCANCODE_P)) {
		Game::instance()->setState(Game::PAUSED);
		return;
	}

	auto fighter = mngr->getHandler(ecs::hdlr::FIGHTER);
	auto &asteroids = mngr->getEntities(ecs::grp::ASTEROIDS);
	auto &blackholes = mngr->getEntities(ecs::grp::BLACKHOLES);
	auto &missiles = mngr->getEntities(ecs::grp::MISSILES);

	// update
	mngr->update(fighter);
	for (auto a : asteroids) {
		mngr->update(a);
	}

	for (auto b : blackholes) {
		mngr->update(b);
	}

	for (auto m : missiles) {
		mngr->update(m);
	}


	// check collisions
	checkCollisions();

	// render
	sdlutils().clearRenderer();
	for (auto a : asteroids) {
		mngr->render(a);
	}
	for (auto b : blackholes) {
		mngr->render(b);
	}
	for (auto m : missiles) {
		mngr->render(m);
	}
	mngr->render(fighter);
	sdlutils().presentRenderer();

	mngr->refresh();

	if (sdlutils().virtualTimer().currTime() > lastTimeGeneratedAsteroids_ + 5000) {
		ast_mngr_->create_asteroids(1);
		lastTimeGeneratedAsteroids_ = sdlutils().virtualTimer().currTime();
	}

	if (sdlutils().virtualTimer().currTime() > lastTimeGeneratedMissile_ + 15000) {
		missile_mngr_->create_missiles(1);
		lastTimeGeneratedMissile_ = sdlutils().virtualTimer().currTime();
	}

}

void RunningState::enter() {
	lastTimeGeneratedAsteroids_ = sdlutils().virtualTimer().currTime();
	lastTimeGeneratedMissile_ = sdlutils().virtualTimer().currTime();
}

void RunningState::checkCollisions() {
	auto mngr = Game::instance()->getMngr();
	auto fighter = mngr->getHandler(ecs::hdlr::FIGHTER);
	auto &asteroids = mngr->getEntities(ecs::grp::ASTEROIDS);
	auto &blackholes = mngr->getEntities(ecs::grp::BLACKHOLES);
	auto &missiles = mngr->getEntities(ecs::grp::MISSILES);
	auto fighterTR = mngr->getComponent<Transform>(fighter);
	auto fighterGUN = mngr->getComponent<Gun>(fighter);

	auto num_of_asteroids = asteroids.size();
	for (auto i = 0u; i < num_of_asteroids; i++) {
		auto a = asteroids[i];
		if (!mngr->isAlive(a))
			continue;

		// asteroid with fighter
		auto aTR = mngr->getComponent<Transform>(a);
		if (Collisions::collidesWithRotation( //
				fighterTR->getPos(), //
				fighterTR->getWidth(), //
				fighterTR->getHeight(), //
				fighterTR->getRot(), //
				aTR->getPos(), //
				aTR->getWidth(), //
				aTR->getHeight(), //
				aTR->getRot())) {
			onFigherDeath();
			return;
		}

		// asteroid with bullets
		for (Gun::Bullet &b : *fighterGUN) {
			if (b.used) {
				if (Collisions::collidesWithRotation( //
						b.pos, //
						b.width, //
						b.height, //
						b.rot, //
						aTR->getPos(), //
						aTR->getWidth(), //
						aTR->getHeight(), //
						aTR->getRot())) {
					ast_mngr_->split_astroid(a);
					b.used = false;
					sdlutils().soundEffects().at("explosion").play();
					continue;
				}
			}
		}

		//blackhole with asteroid
		auto num_of_blackholes = blackholes.size();
		for (auto i = 0u; i < num_of_blackholes; i++) {
			auto n = blackholes[i];

			if (!mngr->isAlive(n))
				continue;

			//checks collisions of blackholes with each asteroid

			auto blh = mngr->getComponent<Transform>(n);

			if (Collisions::collidesWithRotation(
				blh->getPos(), //
				blh->getWidth(), //
				blh->getHeight(), //
				blh->getRot(), //
				aTR->getPos(), //
				aTR->getWidth(), //
				aTR->getHeight(), //
				aTR->getRot()))
			{
				// makes the asteroid dissapear and appear in a random position 
				ast_mngr_->teleport_asteroid(a);
			}
			if (Collisions::collidesWithRotation(
				fighterTR->getPos(), //
				fighterTR->getWidth(), //
				fighterTR->getHeight(), //
				fighterTR->getRot(),
				blh->getPos(), //
				blh->getWidth(), //
				blh->getHeight(), //
				blh->getRot())) {

				onFigherDeath();
				return;
			}
		}

	}

	// missile colissions
	for (auto m : missiles)
	{
		// missiles with fighter
		auto missileTR = mngr->getComponent<Transform>(m);
		if (Collisions::collidesWithRotation(
			fighterTR->getPos(),
			fighterTR->getWidth(),
			fighterTR->getHeight(),
			fighterTR->getRot(),
			missileTR->getPos(),
			missileTR->getWidth(),
			missileTR->getHeight(),
			missileTR->getRot()
		))
		{
			onFigherDeath();
		}

		// missiles with bullets
		for (Gun::Bullet& b : *fighterGUN)
			if (b.used && Collisions::collidesWithRotation(
				b.pos,
				b.width,
				b.height,
				b.rot,
				missileTR->getPos(),
				missileTR->getWidth(),
				missileTR->getHeight(),
				missileTR->getRot()
			))
			{
				mngr->setAlive(m, false);
				b.used = false;
				sdlutils().soundEffects().at("explosion").play();
			}

		// missiles going out of window
		if (!Collisions::collides(
			Vector2D(0, 0),
			sdlutils().width(),
			sdlutils().height(),
			missileTR->getPos(),
			missileTR->getWidth(),
			missileTR->getHeight()
		))
		{
			mngr->setAlive(m, false);
		}
	}
}

void RunningState::onFigherDeath() {
	sdlutils().soundEffects().at("explosion").play();
	if (fighter_mngr_->update_lives(-1) > 0)
		Game::instance()->setState(Game::NEWROUND);
	else
		Game::instance()->setState(Game::GAMEOVER);
}
