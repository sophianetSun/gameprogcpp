#include "TileMapComponent.h"
#include "Actor.h"
#include <fstream>
#include <sstream>
#include <iostream>

TileMapComponent::TileMapComponent(Actor* owner, int drawOrder)
	:SpriteComponent(owner, drawOrder)
	, mTileSize(Vector2(32.0f, 32.0f))
	, mTileWidth(0)
	, mTileHeight(0)
{
}

void TileMapComponent::LoadTileMap(const std::string& fileName)
{
	auto ss = std::ostringstream{};
	std::ifstream input_file(fileName);
	if (!input_file.is_open()) {
		std::cerr << "Could not open the file - '" << fileName << "'" << std::endl;
		exit(EXIT_FAILURE);
	}
	ss << input_file.rdbuf();
	auto data = ss.str();

	char delimiter = ',';

	std::istringstream ss_data(data);
	std::string row;

	while (std::getline(ss_data, row)) {
		std::vector<int> row_data;
		std::istringstream ss_row_data(row);
		std::string token;
		while (std::getline(ss_row_data, token, delimiter)) {
			token.erase(std::remove_if(token.begin(), token.end(), std::isspace),
								token.end());
			
			row_data.push_back(std::stoi(token));
		}
		mTileMap.push_back(row_data);
	}
}

void TileMapComponent::SetTileTexture(SDL_Texture* texture)
{
	mTexture = texture;
	SDL_QueryTexture(texture, nullptr, nullptr, &mTileWidth, &mTileHeight);
}

void TileMapComponent::Update(float deltaTime)
{
	SpriteComponent::Update(deltaTime);
}

void TileMapComponent::Draw(SDL_Renderer* renderer)
{
	for (int i = 0; i < mTileMap.size(); i++) {
		for (int j = 0; j < mTileMap[i].size(); j++) {
			if (mTileMap[i][j] == -1) {
				continue;
			}
			int tileNum = mTileMap[i][j];
			
			int xTileIdx = static_cast<int>(mTileWidth / mTileSize.x);
			int yTileIdx = static_cast<int>(mTileHeight / mTileSize.y);
			int xIdx = xTileIdx ? tileNum % xTileIdx : 0;
			int yIdx = yTileIdx ? tileNum / yTileIdx : 0;

			SDL_Rect srcRect;
			srcRect.w = static_cast<int>(mTileSize.x);
			srcRect.h = static_cast<int>(mTileSize.y);
			srcRect.x = static_cast<int>(mTileSize.x * xIdx);
			srcRect.y = static_cast<int>(mTileSize.y * yIdx);

			SDL_Rect dstRect;
			dstRect.w = static_cast<int>(mTileSize.x);
			dstRect.h = static_cast<int>(mTileSize.y);
			dstRect.x = static_cast<int>(mTileSize.x * j + mOwner->GetPosition().x);
			dstRect.y = static_cast<int>(mTileSize.y * i + mOwner->GetPosition().y);
			
			SDL_RenderCopyEx(renderer, mTexture, &srcRect, &dstRect, 0.0f, nullptr, SDL_FLIP_NONE);
		}
	}
}

