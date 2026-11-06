#include "Entity.h"

class Player : public Entity {
public:
	Player(Vector2 position, int health);

	void onCollision(Entity* other) override;
	void onUpdate() override;

	void readPlayerInputs(const Map& map);
	void GetDirection(Vector2& direction) const;
	
};