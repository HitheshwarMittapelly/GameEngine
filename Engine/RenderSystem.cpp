#pragma once
#include "RenderSystem.h"
static std::vector<RenderSystem::Renderable *> AllRenderables;
#define PI 3.14159265f
	
#define Deg2Rad ( PI / 180.0f )
GLib::Sprites::Sprite * RenderSystem::CreateSprite(const char * i_pFilename)
{
	assert(i_pFilename);

	size_t sizeTextureFile = 0;

	// Load the source file (texture data)
	void * pTextureFile = LoadFile(i_pFilename, sizeTextureFile);

	// Ask GLib to create a texture out of the data (assuming it was loaded successfully)
	GLib::Texture * pTexture = pTextureFile ? GLib::CreateTexture(pTextureFile, sizeTextureFile) : nullptr;

	// exit if something didn't work
	// probably need some debug logging in here!!!!
	if (pTextureFile)
		delete[] pTextureFile;

	if (pTexture == nullptr)
		return NULL;

	unsigned int width = 0;
	unsigned int height = 0;
	unsigned int depth = 0;

	// Get the dimensions of the texture. We'll use this to determine how big it is on screen
	bool result = GLib::GetDimensions(pTexture, width, height, depth);
	assert(result == true);
	assert((width > 0) && (height > 0));

	// Define the sprite edges
	GLib::Sprites::SpriteEdges	Edges = { -float(width / 2.0f), float(height), float(width / 2.0f), 0.0f };
	GLib::Sprites::SpriteUVs	UVs = { { 0.0f, 0.0f },{ 1.0f, 0.0f },{ 0.0f, 1.0f },{ 1.0f, 1.0f } };
	GLib::RGBA							Color = { 255, 255, 255, 255 };

	// Create the sprite
	GLib::Sprites::Sprite * pSprite = GLib::Sprites::CreateSprite(Edges, 0.1f, Color, UVs);
	if (pSprite == nullptr)
	{
		GLib::Release(pTexture);
		return nullptr;
	}

	// Bind the texture to sprite
	GLib::Sprites::SetTexture(*pSprite, *pTexture);

	return pSprite;
}

void RenderSystem::BeginRendering()
{
	// IMPORTANT: Tell GLib that we want to start rendering
	GLib::BeginRendering();
	// Tell GLib that we want to render some sprites
	GLib::Sprites::BeginRendering();
}

void RenderSystem::StopRendering()
{
	// Tell GLib we're done rendering sprites
	GLib::Sprites::EndRendering();
	// IMPORTANT: Tell GLib we're done rendering
	GLib::EndRendering();
}

void RenderSystem::CleanUp() {
	for (unsigned i = 0; i < AllRenderables.size(); i++) {
		GLib::Sprites::Release(AllRenderables.at(i)->m_Sprite);
		delete AllRenderables.at(i);
	}
	AllRenderables.clear();
	AllRenderables.shrink_to_fit();
	std::vector<Renderable *>().swap(AllRenderables);
	AllRenderables.~vector();
}

void RenderSystem::ReleaseSprite(Renderable * i_Renderable)
{
	GLib::Sprites::Release(i_Renderable->m_Sprite);
}

void RenderSystem::AddRenderable(Renderable * i_Renderable)
{
	AllRenderables.push_back(i_Renderable);
}

void RenderSystem::Draw()
{
	for (size_t i = 0; i < AllRenderables.size();i++) {
		auto renderable = AllRenderables.at(i);
		if (renderable->canRender) {
			if (renderable->m_GameObject.AquireOwnership() != nullptr) {
				SmartPointer<GameObject2D> tempSmartObj = renderable->m_GameObject.AquireOwnership();
				GLib::Point2D	Offset = { tempSmartObj->GetPosition().x(), tempSmartObj->GetPosition().y() };


				// Tell GLib to render this sprite at our calculated location
				GLib::Sprites::RenderSprite(*(renderable->m_Sprite), Offset, tempSmartObj->GetZRotation()* Deg2Rad);
			}
			else {
				//We no longer need to draw this object coz its killed
				renderable->m_GameObject.ReleaseReference();
				renderable->canRender = false;
				
			}
		}
	}
}

void RenderSystem::DrawSprite(GLib::Sprites::Sprite & i_Sprite,Point2D i_Pos)
{
	GLib::Point2D	Offset = { i_Pos.x(), i_Pos.y() };
	GLib::Sprites::RenderSprite(i_Sprite, Offset, 0);
}

void * RenderSystem::LoadFile(const char * i_pFilename, size_t & o_sizeFile)
{
	assert(i_pFilename != NULL);

	FILE * pFile = NULL;

	errno_t fopenError = fopen_s(&pFile, i_pFilename, "rb");
	if (fopenError != 0)
		return NULL;

	assert(pFile != NULL);

	int FileIOError = fseek(pFile, 0, SEEK_END);
	assert(FileIOError == 0);

	long FileSize = ftell(pFile);
	assert(FileSize >= 0);

	FileIOError = fseek(pFile, 0, SEEK_SET);
	assert(FileIOError == 0);

	uint8_t * pBuffer = new uint8_t[FileSize];
	assert(pBuffer);

	size_t FileRead = fread(pBuffer, 1, FileSize, pFile);
	assert(FileRead == FileSize);

	fclose(pFile);

	o_sizeFile = FileSize;

	return pBuffer;
}
