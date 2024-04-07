#include "RunningState.h"
#include "../sdlutils/InputHandler.h"
#include "../utils/Collisions.h"
#include <vector>

#include "Game.h"
#include "../ecs/Manager.h"
#include "../components/Transform.h"
#include "../components/Health.h"
#include "../systems/PacManSystem.h"
#include "../systems/GhostSystem.h"
#include "../systems/FoodSystem.h"
#include "../systems/ImmunitySystem.h"
#include "../systems/CollisionSystem.h"
#include "../systems/RenderSystem.h"

RunningState::RunningState(PacManSystem* pc, GhostSystem* gh, FoodSystem* fo,
	ImmunitySystem* im, CollisionSystem* col, RenderSystem* r)
	:pacManSystem(pc), ghostSystem(gh), foodSystem(fo),
	immunitySystem(im), collisionSystem(col), renderSystem(r)
{

}

RunningState::~RunningState()
{
}

void RunningState::update()
{
	// move to pause if P pressed
	if (ih().keyDownEvent() && ih().isKeyDown(SDL_SCANCODE_P)) {
		Game::instance()->setState(Game::PAUSED);


		return;
	}

	// se actualizan los sistemas
	pacManSystem->update();
	collisionSystem->update();
	ghostSystem->update();
	foodSystem->update();
	//immunitySystem->update();
	renderSystem->update();
}





void RunningState::enter()
{
	//resetear timers
}

void RunningState::leave()
{
}