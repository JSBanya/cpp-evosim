#include "cell.h"

Cell::Cell() {

}

Cell::Cell(float x, float y, float r, float g, float b) {
	this->x = x;
	this->y = y;
	this->r = r;
	this->g = g;
	this->b = b;
	this->movementSpeed = movementSpeed;
}

Cell* Cell::addX(float x, float xBoundLower, float xBoundUpper) {
	this->x += x;

	if(this->x < xBoundLower) {
		this->x = xBoundLower;
	}

	if(this->x > xBoundUpper) {
		this->x = xBoundUpper;
	}

	return this;
}

Cell* Cell::addY(float y, float yBoundLower, float yBoundUpper) {
	this->y += y;

	if(this->y < yBoundLower) {
		this->y = yBoundLower;
	}

	if(this->y > yBoundUpper) {
		this->y = yBoundUpper;
	}

	return this;
}

glm::mat4 Cell::getTranslation() {
	glm::mat4 trans(1);
    return glm::translate(trans, glm::vec3(x, y, 0.0f));
}

Cell* Cell::setAttack(float a) {
	this->attack = a;
	if(this->attack > 1.0f) this->attack = 1.0f;
	if(this->attack < 0.0f) this->attack = 0.0f;
	return this;
}

Cell* Cell::setDefense(float d) {
	this->defense = d;
	if(this->defense > 1.0f) this->defense = 1.0f;
	if(this->defense < 0.0f) this->defense = 0.0f;
	return this;
}

bool Cell::hasChild() {
	bool b = this->hasReplicated;
	this->hasReplicated = false;
	return b;
}

void Cell::tick(float xBoundLower, float xBoundUpper, float yBoundLower, float yBoundUpper) {
	int dir = rand() % 6;
	if(dir == 0) {
		// NORTH
		this->addY(this->movementSpeed, yBoundLower, yBoundUpper);
	} else if(dir == 1) {
		// SOUTH
		this->addY(-1.0f * this->movementSpeed, yBoundLower, yBoundUpper);
	} else if(dir == 2) {
		// EAST
		this->addX(this->movementSpeed, xBoundLower, xBoundUpper);
	} else if(dir == 4) {
		// WEST
		this->addX(-1.0f * this->movementSpeed, xBoundLower, xBoundUpper);
	} else {
		// NO MOVEMENT
	}

	// Tick lifespan
	this->life--;
	if(this->life == 0) {
		this->setAlive(false);
	}

	// Tick replication chance
	if(this->isAlive()) {
		float repValue = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
		if(repValue <= this->replicationChance) {
			this->hasReplicated = true;
		}
	}
}