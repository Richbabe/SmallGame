#pragma once
#include "GameTexture.h"

class Node {
public:
	Node():m_spriteSizeX(0.0), m_spriteSizeY(0.0), m_PosX(0.0), m_PosY(0.0), m_Visible(true)
	{}
	virtual ~Node() {};
	float GetSizeX() { return m_spriteSizeX; }
	float GetSizeY() { return m_spriteSizeY; }
	float GetPosX() { return m_PosX; }
	float GetPosY() { return m_PosY; }


	void SetSizeX(float x) { m_spriteSizeX = x; }
	void SetSizeY(float y) { m_spriteSizeY = y; }
	void SetPosX(float x) { m_PosX = x; }
	void SetPosY(float y) { m_PosY = y; }

	bool GetVisible() { return m_Visible; }
	void SetVisible(bool visible) { m_Visible = visible; }
private:

	float m_spriteSizeX;
	float m_spriteSizeY;
	float m_PosX;
	float m_PosY;
	bool m_Visible;

};

class SpriteNode :public Node
{
public:
	SpriteNode();
	~SpriteNode();
	static std::shared_ptr<SpriteNode> Create(const char* fileName);

	void SetTexture(std::shared_ptr<GameTexture> textture);
	std::shared_ptr<GameTexture> GetTexture() { return m_texture; }
private:
	std::shared_ptr<GameTexture> m_texture;


};

class FontNode :public Node
{
public:
	FontNode() {};
	virtual ~FontNode() {};
	void SetText(const wchar_t* str) {
		m_text = (wchar_t*)str;
	}
	const wchar_t* GetText() { return m_text; }

private:
	wchar_t* m_text;

};
