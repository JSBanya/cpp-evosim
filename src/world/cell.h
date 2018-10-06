#ifndef CELL_H
#define CELL_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdlib.h>

class Cell {
public:
	Cell();
	Cell(float x, float y, float r, float g, float b);

	float getX() { return x; };
	Cell* setX(float x) { this->x = x; return this; };
	Cell* addX(float x) { this->x += x; return this; };
	Cell* addX(float x, float xBoundLower, float xBoundUpper);

	float getY() { return y; };
	Cell* setY(float y) { this->y = y; return this; };
	Cell* addY(float y) { this->y += y; return this; };
	Cell* addY(float y, float yBoundLower, float yBoundUpper);

	float getR() { return r; };
	Cell* setR(float r) { this->r = r; return this; };

	float getG() { return g; };
	Cell* setG(float g) { this->g = g; return this; };

	float getB() { return b; };
	Cell* setB(float b) { this->b = b; return this; };

	float getMovementSpeed() { return this->movementSpeed; };
	Cell* setMovementSpeed(float mv) { this->movementSpeed = mv; return this; };

	float getReplicationChance() { return this->replicationChance; };
	Cell* setReplicationChance(float rc) { this->replicationChance = rc; return this; };

	float getLifespan() { return this->lifespan; };
	Cell* setLifespan(int l) { this->lifespan = l; return this; };

	float getLife() { return this->life; };
	Cell* setLife(int l) { this->life = l; return this; };

	float getAttack() { return this->attack; };
	Cell* setAttack(float a);

	float setDefense() { return this->defense; };
	Cell* setDefense(float d);

	bool isAlive() { return alive; };
	Cell* setAlive(bool alive) { this->alive = alive; return this; };

	bool hasChild(); // If a cell has split, this will return true and reset hasChild to false.

	glm::mat4 getTranslation();

	void tick(float xBoundLower, float xBoundUpper, float yBoundLower, float yBoundUpper);
private:
	float x, y;
	float r, g, b;
	bool alive;
	bool hasReplicated; // Whether to create a child cell

	// Attributes
	float movementSpeed = 0.5f;
	float attack = 0.5f;
	float defense = 0.5f;
	float replicationChance = 0.02f; // 0.01 gives ~63% chance to duplicate once during a lifetime of 100
	int lifespan = 100; // Original lifespan (does not tick)
	int life = 100; // ticks left to live
};

#endif