#pragma once
#include "../ecs/System.h"

class Vector2D;

/// <summary>
/// Responsable de generar y mover los fantasmas. 
/// Cuando acaba una ronda quitatodos los fantasmas actuales.
/// Cuando el PacMan choca con un fantasma:
///  - si el PacMan tiene inmunidad desaparece el fantasma
///  - si PacMan no tiene inmunidad muere el PacMan (y envía un mensaje correspondiente de fin de ronda / partida 
///  y cambia al estado NewRoundState o GameOverState – ver los estados abajo).
/// 
/// Recuerda que no se generan fantasmas cuando el PacMan tiene inmunidad.
/// Cuando cambia el estado de la inmunidad del PacMan tiene que cambiar la imagen que se usa para dibujar los fantasmas.
/// </summary>

class GhostSystem : public ecs::System {
public:
    __SYSID_DECL__(ecs::sys::GHOST);

    GhostSystem() : esquina(0), blueGhosts(false) {};
    ~GhostSystem() {};

    void initSystem() override;
    void update() override;

    void recieve(const Message&) override;

    // Genera un ghost en una esquina
    void addGhost();
    void deleteGhosts();

    void setBlue(bool b);

private:
    int esquina;

    int genTime = 5000;
    int lastTimeGenerated = 0;

    bool blueGhosts; // ghosts vulnerables
};