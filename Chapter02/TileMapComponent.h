#pragma once

#include "SpriteComponent.h"
#include "Math.h"
#include <vector>
#include <string>
class TileMapComponent : public SpriteComponent
{
public:
	TileMapComponent(class Actor* owner, int drawOrder = 10);
	
	void Update(float deltatime) override;
	void Draw(SDL_Renderer* renderer) override;
	
	void LoadTileMap(const std::string& fileName);
	std::vector<std::vector<int>> GetTileMap() const { return mTileMap; }
	void SetTileTexture(SDL_Texture* texture);
	void SetTileSize(const Vector2& size) { mTileSize = size; }

private:
	std::vector<std::vector<int>> mTileMap;
	SDL_Texture* mTileTexture;
	Vector2 mTileSize;
	int mTileWidth;
	int mTileHeight;
};