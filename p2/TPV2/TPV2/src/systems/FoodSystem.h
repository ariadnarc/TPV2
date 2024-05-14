// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/System.h"
#include "../components/Transform.h"

/// <summary>
/// Cuando empieza una partida coloca las frutas en forma de grid, algunas serán milagrosas.
/// En el método update hay que actualizar el estado de la frutas milagrosas.
/// Cuando el PacMan choca con una fruta desaparece la fruta, y cuando no hay más frutas envía
/// un mensaje que se haya acabado la partida y cambia de estado as GameOverState (ver los estado abajo)
/// </summary>

class FoodSystem : public ecs::System {
public:
    __SYSID_DECL__(ecs::sys::FOOD);

    FoodSystem() {};
    ~FoodSystem() {};

    void initSystem() override;
    void update() override;

    void recieve(const Message&) override;

    // Crea entidad fruta.
    void addFood(Vector2D pos);
    // Coloca las frutas en el grid.
    void createGrid();
    // Resetea el grid para nueva partida.
    void resetGrid();

private:
    int FRUITCOLS = 8;
    int FRUITROWS = 6;

    float offset = 25;

};