#include "world.h"

World::World(float width, float height, int maxCells, Camera* camera) {
	this->aliveCells = new CellList();
	this->deadCells = new CellList();
	this->width = width;
	this->height = height;
	this->maxCells = maxCells;
	this->camera = camera;

	if(this->width < 5.0f) {
		std::cout << "Width set to invalid value, defaulting to 5.0" << std::endl;
		this->width = 5.0f;
	}

	if(this->height < 5.0f) {
		std::cout << "Height set to invalid value, defaulting to 5.0" << std::endl;
		this->height = 5.0f;
	}

	if(this->maxCells < 5) {
		std::cout << "Max cells set to invalid value, defaulting to 5" << std::endl;
		this->maxCells = 5;
	}

	const float BOUNDS_PADDING = 0.5f; // Pad the bounds of the world box to compensate for the cell size
	this->xBoundLower = 0.0f + BOUNDS_PADDING;
	this->xBoundUpper = this->width - BOUNDS_PADDING;
	this->yBoundLower = -1.0f * this->height + BOUNDS_PADDING;
	this->yBoundUpper = 0.0f - BOUNDS_PADDING;

	// Create a single model and shader for all cells
	float square[] = {
        -0.5f, 0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,

        -0.5f, 0.5f, 0.0f,
        0.5f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
    };

    this->cellModel = new Model(square, 18, MODEL_TRIANGLES);
	this->cellShader = new Shader("./res/shaders/cell.vert", "./res/shaders/cell.frag");

	// Create the model for the world box
	float worldBox[] = {
		0.0f, 0.0f, this->width, 0.0f, // x0, y0, x1, y1
		0.0f, 0.0f, 0.0f, -1.0f * this->height,
		0.0f, -1.0f * this->height, this->width, -1.0f * this->height,
		this->width, -1.0f * this->height, this->width, 0.0,
	};

	this->worldModel = new Model(worldBox, 16, MODEL_LINES);
	this->worldShader = new Shader("./res/shaders/world.vert", "./res/shaders/world.frag");

	// Create all the cells to be used so that we do not have to create them during runtime
	const int ACTIVE_CELLS = 20;
	for(int i = 0; i < maxCells; i++) {
		Cell* c = new Cell();

		if(i < ACTIVE_CELLS) {
			// Make the first 'ACTIVE_CELLS' cell active
			c->setR(0.5f)
				->setG(0.5f)
				->setB(0.5f)
				->setX(this->width / 2.0f)
				->setY(this->height / -2.0f)
				->setMovementSpeed(0.5f)
				->setAlive(true);
			aliveCells->pushBack(c);
		} else {
			// Make every other cell inactive
			c->setAlive(false);
			deadCells->pushBack(c);
		}
	}
}

void World::render() {
	this->renderWorldBox();
	this->renderCells();
}

void World::renderCells() {
	cellShader->use();
	cellShader->bindUniformMatrix4fv("projectionMatrix", camera->getProjection());
    cellShader->bindUniformMatrix4fv("camera", camera->getView());

    CellNode* node = aliveCells->getFirst();
    Cell* c;
    while(node != NULL) {
    	c = node->getCell();

    	cellShader->bindUniformMatrix4fv("translationMatrix", c->getTranslation());
    	cellShader->bindUniform4f("color", c->getR(), c->getG(), c->getB(), 1.0f);
    	cellModel->drawTriangles();

    	node = node->getNext();
    }
}

void World::renderWorldBox() {
	worldShader->use();
	worldShader->bindUniformMatrix4fv("projectionMatrix", camera->getProjection());
    worldShader->bindUniformMatrix4fv("camera", camera->getView());
    worldShader->bindUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
    worldModel->drawLines();
}

void World::tick() {
	CellNode* node = aliveCells->getFirst();
	Cell* c;
	while(node != NULL) {
		c = node->getCell();

		c->tick(this->xBoundLower, this->xBoundUpper, this->yBoundLower, this->yBoundUpper);
		if(!c->isAlive()) {
			// Cell has died, remove it from the list
			CellNode* next = node->getNext();
			aliveCells->remove(node);
			deadCells->pushBack(node);
			node = next;
		} else if(c->hasChild()) {
			createChild(c);
		} else {
			node = node->getNext();
		}
	}	
}

void World::createChild(Cell* c) {
	CellNode* node = deadCells->popFront();
	if(node == NULL) {
		return;
	}

	Cell* child = node->getCell();

	float r = c->getR();
	float g = c->getG();
	float b = c->getB();
	float movementSpeed = c->getMovementSpeed();
	float replicationChance = c->getReplicationChance();
	float lifespan = c->getLifespan();

	if(rand() % 10 == 0) {
		float modifier = static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 0.2f) - 0.1f;
		movementSpeed += movementSpeed * modifier;
		if(modifier > 0.0f)	b += 0.1f;
		else b -= 0.1f;
		if(b > 1.0f) b = 1.0f;
		if(b < 0.0f) b = 0.0f;
	}

	if(rand() % 10 == 0) {
		float modifier = static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 0.2f) - 0.1f;
		replicationChance += replicationChance * modifier;
		if(modifier > 0.0f)	g += 0.1f;
		else g -= 0.1f;
		if(g > 1.0f) g = 1.0f;
		if(g < 0.0f) g = 0.0f;
	}

	if(rand() % 10 == 0) {
		float modifier = static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 0.1f) - 0.05f;
		lifespan += lifespan * modifier;
		if(modifier > 0.0f)	r += 0.1f;
		else r -= 0.1f;
		if(r > 1.0f) r = 1.0f;
		if(r < 0.0f) r = 0.0f;
	}

	child->setR(r)
			->setG(g)
			->setB(b)
			->setX(c->getX()+((rand() % 2) - 1))
			->setY(c->getY()+((rand() % 2) - 1))
			->setMovementSpeed(movementSpeed)
			->setReplicationChance(replicationChance)
			->setLifespan(lifespan)->setLife(lifespan)
			->setAlive(true);
	aliveCells->pushBack(node);
}