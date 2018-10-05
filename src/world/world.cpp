#include "world.h"

World::World(float width, float height, int maxCells, Camera* camera) {
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
		0.0f, 			0.0f, 					this->width, 	0.0f, 					// x0, y0, x1, y1
		0.0f, 			0.0f, 					0.0f, 			-1.0f * this->height,
		0.0f, 			-1.0f * this->height, 	this->width, 	-1.0f * this->height,
		this->width, 	-1.0f * this->height, 	this->width, 	0.0,
	};

	this->worldModel = new Model(worldBox, 16, MODEL_LINES);
	this->worldShader = new Shader("./res/shaders/world.vert", "./res/shaders/world.frag");

	// Create all the cells to be used so that we do not have to create them during runtime
	for(int i = 0; i < maxCells; i++) {
		Cell* c = new Cell();
		cells.push_back(c);

		if(i < 2000) {
			// Make the first cell active
			c->setR(1.0f)
				->setG(1.0f)
				->setB(1.0f)
				->setX(this->width / 2.0f)
				->setY(this->height / -2.0f)
				->setMovementSpeed(0.5f)
				->setAlive(true);
		} else {
			// Make every other cell inactive
			c->setAlive(false);
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

    for(Cell* c : this->cells) {
    	if(c->isAlive()) {
    		cellShader->bindUniformMatrix4fv("translationMatrix", c->getTranslation());
    		cellShader->bindUniform4f("color", c->getR(), c->getG(), c->getB(), 1.0f);
    		cellModel->drawTriangles();
    	}
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
	for(Cell* c : this->cells) {
		if(c->isAlive()) {
			c->tick(this->xBoundLower, this->xBoundUpper, this->yBoundLower, this->yBoundUpper);
		}
	}	
}