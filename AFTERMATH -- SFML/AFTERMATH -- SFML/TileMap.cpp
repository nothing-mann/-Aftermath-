#include "stdafx.h"
#include "TileMap.h"

TileMap::TileMap(float gridSize, unsigned width, unsigned height, std::string texture_file)
{
	this->gridSizeF = gridSize;
	this->gridSizeU = static_cast<unsigned>(this->gridSizeF);
	this->maxSize.x = width;
	this->maxSize.y = height;
	this->layers = 1;
	this->textureFile = texture_file;

	this->map.resize(this->maxSize.x, std::vector<std::vector<Tile*> >());
	for (size_t x = 0; x < this->maxSize.x; x++)
	{

		for (size_t y = 0; y < this->maxSize.y; y++)
		{
			this->map[x].resize(this->maxSize.y, std::vector<Tile*>());

			for (size_t z = 0; z < this->layers; z++)
			{
				this->map[x][y].resize(this->layers, nullptr);
			}
		}
	}
	this->tileTextureSheet.loadFromFile("Resources/Images/Tiles/tilesheet1.png");
}


TileMap::~TileMap()
{
	for (size_t x = 0; x < this->maxSize.x; x++)
	{
		for (size_t y = 0; y < this->maxSize.y; y++)
		{
			for (size_t z = 0; z < this->layers; z++)
			{
				delete this->map[x][y][z];
			}
		}
	}
}


//Accessors
const sf::Texture* TileMap::getTileSheet() const
{
	return &this->tileTextureSheet;
}

//Functions
void TileMap::addTile(const unsigned x, const unsigned y, const unsigned z, const sf::IntRect& tex_rect)
{
	//take three indices from the mouse position in the grid and add a tile to that position if the internal tilemap array allows it
	if (x < this->maxSize.x && x >= 0 && y < this->maxSize.y && y >= 0 && z < this->layers && z >= 0)
	{
		if (this->map[x][y][z] == nullptr) //Adds something if it is actually null
		{
			//Ok to add tile
			this->map[x][y][z] = new Tile(x * this->gridSizeF, y * this->gridSizeF, this->gridSizeF, this->tileTextureSheet, tex_rect);
			std::cout << "DEBUG: ADDED TILE!" << "\n";
		}

	}
}

void TileMap::removeTile(const unsigned x, const unsigned y, const unsigned z)
{
	//take three indices from the mouse position in the grid and remove a tile to that position if the internal tilemap array allows it
	if (x < this->maxSize.x && x >= 0 && y < this->maxSize.y && y >= 0 && z < this->layers && z >= 0)
	{
		if (this->map[x][y][z] != nullptr) //Adds something if it is actually null
		{
			//Ok to remove tile
			delete this->map[x][y][z];
			this->map[x][y][z] = nullptr;   //Very IMPORTANT to Set this to NULL POINTER
			std::cout << "Debug: Removed a tile" << "\n";
		}

	}
}

void TileMap::saveToFile(const std::string file_name)
{
	/* saves the entire tilemap to a textfile.
	Format:
	Basic:
	Size x y
	gridSize
	layers
	texturefile

	All tiles:
	gridPos x y, Texture rect x y, type
	*/
	std::ofstream out_file;
	out_file.open(file_name);
	if (out_file.is_open())
	{
		out_file << this->maxSize.x << " " << this->maxSize.y << "\n"
			<< this->gridSizeU << "\n"
			<< this->layers << "\n"
			<< this->textureFile << "\n";
		for (size_t x = 0; x < this->maxSize.x; x++)
		{
			for (size_t y = 0; y < this->maxSize.y; y++)
			{
				for (size_t z = 0; z < this->layers; z++)
				{
					out_file << 1 << 1 << 2 << 3 << 5 << " ";
					//out_file << this->map[x][y][z];
				}
			}
		}
		
	}
	else
	{
		std::cout << "Error::tilemap::could not save to filename:" << file_name << "\n";
	}
	out_file.close();
}

void TileMap::loadFromFile(const std::string file_name)
{

}

void TileMap::update()
{
}

void TileMap::render(sf::RenderTarget& target)
{
	for (auto& x : this->map)
	{
		for (auto& y : x)
		{
			for (auto* z : y)
			{
				if (z != nullptr)
					z->render(target);
			}
		}
	}
}