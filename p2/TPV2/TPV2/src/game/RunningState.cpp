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
	ImmunitySystem* im, CollisionsSystem* col, RenderSystem* r)
	:pacManSystem(pc), ghostSystem(gh), foodSystem(fo),
	immunitySystem(im), collisionsSystem(col), renderSystem(r)
{

}

RunningState::~RunningState()
{
}

void RunningState::update()
{
	auto mngr = Game::instance()->getMngr();

	//aqui lo de pausa immunidad y eso

	// aqui llamar al update de todos los sistemas
	pacManSystem->update();
}





void RunningState::enter()
{
	//resetear timers
}

void RunningState::leave()
{
}