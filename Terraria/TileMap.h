#ifndef _TILE_MAP_INCLUDE
#define _TILE_MAP_INCLUDE


#include <glm/glm.hpp>
#include <vector>
#include <string>
#include "Texture.h"
#include "ShaderProgram.h"


// Class Tilemap is capable of loading a tile map from a text file in a very
// simple format (see level01.txt for an example). With this information
// it builds a single VBO that contains all tiles. As a result the render
// method draws the whole map independently of what is visible.


class TileMap
{

public:
	// Tile maps can only be created inside an OpenGL context
	static TileMap *createTileMap(const string &levelFile, const glm::vec2 &minCoords, ShaderProgram *program);

	TileMap(const string &levelFile, const glm::vec2 &minCoords, ShaderProgram *program);
	~TileMap();

	void render() const;
	void update(glm::vec2 posTile, string type);
	void free();
	//vector<Item*> getNewItems();

	int getTileSize() const { return tileSize; }
	int getTile(int x, int y);

	bool collisionMoveLeft(const glm::ivec2 &pos, const glm::ivec2 &size) const;
	bool collisionMoveRight(const glm::ivec2 &pos, const glm::ivec2 &size) const;
	bool collisionMoveDown(const glm::ivec2 &pos, const glm::ivec2 &size, int *posY) const;
	bool collisionMoveUp(const glm::ivec2 &pos, const glm::ivec2 &size, int *posY) const;
	bool collisionNecro(const glm::ivec2 &pos, const glm::ivec2 &size) const;

private:
	bool loadLevel(const string &levelFile);
	void prepareArrays(const glm::vec2 &minCoords);

private:
	GLuint vao;
	GLuint vbo;
	GLint posLocation, texCoordLocation;
	glm::ivec2 position, mapSize, tilesheetSize;
	int tileSize, blockSize;
	//vector<Item*> items;
	Texture tilesheet;
	glm::vec2 tileTexSize;
	int *map;
	vector<float> vertices;
	ShaderProgram *prog;

};


#endif // _TILE_MAP_INCLUDE


