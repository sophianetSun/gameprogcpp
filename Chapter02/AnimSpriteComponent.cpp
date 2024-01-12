// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "AnimSpriteComponent.h"
#include "Math.h"

AnimSpriteComponent::AnimSpriteComponent(Actor* owner, int drawOrder)
	:SpriteComponent(owner, drawOrder)
	, mCurrFrame(0.0f)
	, mAnimFPS(24.0f)
	, mCurrAnim(0)
{
}

void AnimSpriteComponent::Update(float deltaTime)
{
	SpriteComponent::Update(deltaTime);

	if (mAnimTextures.size() > 0 && mAnimIndices.size() > 0)
	{
		// Update the current frame based on frame rate
		// and delta time
		mCurrFrame += mAnimFPS * deltaTime;

		// Wrap current frame if needed
		while (mCurrFrame > std::get<1>(mAnimIndices[mCurrAnim]))
		{
			if (std::get<2>(mAnimIndices[mCurrAnim]))
			{
				mCurrFrame -= std::get<1>(mAnimIndices[mCurrAnim]) - std::get<0>(mAnimIndices[mCurrAnim]);
			}
			else
			{
				mCurrFrame = std::get<1>(mAnimIndices[mCurrAnim]) - 1;
			}
		}

		// Set the current texture
		SetTexture(mAnimTextures[static_cast<int>(mCurrFrame)]);
	}
}

void AnimSpriteComponent::SetAnimTextures(const std::vector<SDL_Texture*>& textures)
{
	mAnimTextures = textures;
	if (mAnimTextures.size() > 0)
	{
		// Set the active texture to first frame
		mCurrFrame = 0.0f;
		SetTexture(mAnimTextures[0]);
	}
}

void AnimSpriteComponent::SetAnimIndices(const std::vector<std::tuple<int, int, bool>>& indices)
{
	mAnimIndices = indices;
	if (mAnimIndices.size() > 0)
	{
		// Set the active texture to first frame
		mCurrFrame = 0.0f;
		SetTexture(mAnimTextures[0]);
	}
}

void AnimSpriteComponent::SetCurrAnim(int anim)
{
	if (anim < mAnimIndices.size())
	{
		mCurrAnim = anim;
		mCurrFrame = 0.0f;
		SetTexture(mAnimTextures[std::get<0>(mAnimIndices[mCurrAnim])]);
	}
}