#include "ShowAtOppositeSide.h"

//un poco copia pega del StopOnBorder.cpp jiji
//esto es movimiento toroidal o tiroidal o como se diga
void ShowAtOppositeSide::update(Container* o)
{
	auto& pos = o->getPos();
	
	if (pos.getX() < 0) 	//si la posicion X es menor que 0
	{
		pos = Vector2D(sdlutils().width(), pos.getY()); //lo movemos al ancho
	}	
	else if (pos.getX() > sdlutils().width()) //si la posicion X es mayor que el ancho de la ventana
	{
		pos = Vector2D(0, pos.getY()); //lo movemos al comienzo
	}

	if (pos.getY() < 0)		//si la posicion Y es menor que 0
	{
		pos = Vector2D(pos.getX(), sdlutils().height());
	}
	else if (pos.getY() > sdlutils().height()) //si la posicion Y es mayor que el alto de la ventana
	{
		pos = Vector2D(pos.getX(), 0);
	}
}
