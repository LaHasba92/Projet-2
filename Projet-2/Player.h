#include "Entity.h"

enum class Direction
{
	HAUT,
	BAS,
	GAUCHE,
	DROITE,
	AUCUNE
};

class Player : Entity {
public:
	Player(Vector2 position, int health);

	void onCollision(Entity* other) override;
	void onUpdate() override;

	void readPlayerInputs(const Map& map);
	void GetDirection(Vector2& direction) const;
	
};