#ifndef TILE_H_INCLUDED
#define TILE_H_INCLUDED

class Tile
{
public:
	Tile();
	Tile(char cSymbol, bool bPassable); 
	char getSymbol();
	void setSymbol(char cSymbol);
	bool getPassable();
	void setPassable(bool bPassable);
	void setContent(char cSymbol, bool bPassable);
	void setRevealed(bool bRevealed);
	bool getRevealed();
private:
	char m_cSymbol;
	bool m_bPassable;
	bool m_bRevealed;
};

#endif
