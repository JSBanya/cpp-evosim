#ifndef WORLD_H
#define WORLD_H

#include <iostream>
#include <vector>
#include <list>
#include <stdlib.h>
#include "../gfx/model.h"
#include "../gfx/shader.h"
#include "../controls/camera.h"
#include "../utils/cellList.h"
#include "cell.h"

class World {
public:
	World(float width, float height, int maxCells, Camera* camera);
	void render();
	void renderCells();
	void renderWorldBox();
	void tick();
	void createChild(Cell*);
private:
	Camera* camera;
	Model* cellModel;
	Shader* cellShader;

	Model* worldModel;
	Shader* worldShader;

	float width, height;
	float xBoundLower, xBoundUpper, yBoundLower, yBoundUpper;
	int maxCells;

	CellList* aliveCells;
	CellList* deadCells;
};

#endif