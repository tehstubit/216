#include <vector>
#include "Tile.h"

using namespace std;

char Tile::getSymbol()
{
	return m_cSymbol;
}

void Tile::setContent(char cSymbol, bool bPassable)
{
	m_cSymbol = cSymbol;
	m_bPassable = bPassable;
}

void Tile::setSymbol(char cSymbol)
{
	m_cSymbol = cSymbol;
}

void Tile::setPassable(bool bPassable)
{
	m_bPassable = bPassable;
}

bool Tile::getPassable()
{
	return m_bPassable;
}

Tile::Tile() : m_cSymbol(' '), m_bPassable(false) {}

Tile::Tile(char cSymbol, bool bPassable) : m_cSymbol(cSymbol), m_bPassable(bPassable), m_bRevealed(false) {}

void Tile::setRevealed(bool bRevealed)
{
	m_bRevealed = bRevealed;
}

bool Tile::getRevealed()
{
	return m_bRevealed;
}
