#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

#define SCREEN_WIDTH			640
#define SCREEN_HEIGHT			480
#define MAP_WIDTH				30
#define MAP_HEIGHT				20
#define TRIANGLES_FOR_TILE		2
#define VERTICES_PER_TRIANGLE	3
#define TILE_SIZE				16

int main(int argc, char* argv[])
{
	/*
	* to do - 
	* 1. uplaod to git
	* 2. no effect shader
	* 3. random colors shader
	* 4. only visablility around certain radius
	* 
	* 
	* 
	*/

	RenderWindow window(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "shaders", Style::None);

	Shader shader;
	shader.loadFromFile("assets/vertex_shader.vert", "assets/fragment_shader.frag");

	VertexArray tilemapVA(Triangles, MAP_WIDTH * MAP_HEIGHT * TRIANGLES_FOR_TILE * VERTICES_PER_TRIANGLE);

	Image img;
	img.loadFromFile("assets/16px_tileset.png");

	Texture tilemapTexture;
	tilemapTexture.loadFromImage(img);

	int mapdata[MAP_WIDTH * MAP_HEIGHT];

	RenderStates renderStates;
	renderStates.shader = &shader;
	renderStates.texture = &tilemapTexture;

	for (int i = 0, x, y, currentTile; i < MAP_WIDTH * MAP_HEIGHT; i++)
	{

		currentTile = i * VERTICES_PER_TRIANGLE * TRIANGLES_FOR_TILE;
		x = i % MAP_WIDTH;
		y = i / MAP_WIDTH;

		mapdata[i] = rand() % 3;

		tilemapVA[currentTile + 0].position = Vector2f(x * TILE_SIZE + 0			, y * TILE_SIZE + 0);
		tilemapVA[currentTile + 1].position = Vector2f(x * TILE_SIZE + TILE_SIZE	, y * TILE_SIZE + 0);
		tilemapVA[currentTile + 2].position = Vector2f(x * TILE_SIZE + 0			, y * TILE_SIZE + TILE_SIZE);
		tilemapVA[currentTile + 3].position = Vector2f(x * TILE_SIZE + 0			, y * TILE_SIZE + TILE_SIZE);
		tilemapVA[currentTile + 4].position = Vector2f(x * TILE_SIZE + TILE_SIZE	, y * TILE_SIZE + 0);
		tilemapVA[currentTile + 5].position = Vector2f(x * TILE_SIZE + TILE_SIZE	, y * TILE_SIZE + TILE_SIZE);

		tilemapVA[currentTile + 0].color = Color(125, 125, 255);
		tilemapVA[currentTile + 1].color = Color(125, 125, 255);
		tilemapVA[currentTile + 2].color = Color(125, 125, 255);
		tilemapVA[currentTile + 3].color = Color(125, 125, 255);
		tilemapVA[currentTile + 4].color = Color(125, 125, 255);
		tilemapVA[currentTile + 5].color = Color(125, 125, 255);

		tilemapVA[currentTile + 0].texCoords = Vector2f(0, 0);
		tilemapVA[currentTile + 1].texCoords = Vector2f(0, 16);
		tilemapVA[currentTile + 2].texCoords = Vector2f(16, 0);
		tilemapVA[currentTile + 3].texCoords = Vector2f(16, 0);
		tilemapVA[currentTile + 4].texCoords = Vector2f(0, 16);
		tilemapVA[currentTile + 5].texCoords = Vector2f(16, 16);
	}

	while (window.isOpen())
	{
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		window.clear();

		window.draw(tilemapVA, renderStates);

		window.display();
	}
}



class Effect : public Drawable
{
public:
	virtual ~Effect()
	{

	}

	const string& getName() const
	{
		return m_name;
	}

	void load()
	{
		m_isLoaded = sf::Shader::isAvailable() && onLoad();
	}

	void update(float time, float x, float y)
	{
		if (m_isLoaded)
		{
			onUpdate(time, x, y);
		}
	}

	void draw(RenderTarget& target, RenderStates states) const
	{
		if (m_isLoaded)
		{
			onDraw(target, states);
		}
		else
		{
			// Shader not supported
		}
	}

protected:
	Effect(const string& name) : m_name(name), m_isLoaded(false)
	{

	}

private:
	virtual bool onLoad() = 0;
	virtual void onUpdate(float time, float x, float y) = 0;
	virtual void onDraw(RenderTarget& target, RenderStates states) const = 0;

private:
	string m_name;
	bool m_isLoaded;
};