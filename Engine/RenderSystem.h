#pragma once
#include <vector>
#include "WeakPointer.h"
#include "GameObject2D.h"
#include "GLib/GLib.h"
namespace RenderSystem {
	struct Renderable {
		WeakPointer<GameObject2D>  m_GameObject;
		GLib::Sprites::Sprite * m_Sprite;
		bool canRender;
		Renderable(const SmartPointer<GameObject2D> & i_Other, GLib::Sprites::Sprite * i_Sprite) :
			m_GameObject(i_Other),
			m_Sprite(i_Sprite)
		{
			canRender = true;
		}
		
	};
	
	void ReleaseSprite(Renderable * i_Renderable);
	void AddRenderable(Renderable * i_Renderable);
	void Draw(); 
	void DrawSprite(GLib::Sprites::Sprite & i_Sprite, Point2D i_Pos);
	void * LoadFile(const char * i_pFilename, size_t & o_sizeFile);
	GLib::Sprites::Sprite * CreateSprite(const char * i_pFilename);
	void BeginRendering();
	void StopRendering();
	void CleanUp();


}