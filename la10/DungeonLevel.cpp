#include <iostream>
#include <random>

#include "DungeonLevel.h"

using namespace std;


DungeonLevel::DungeonLevel(int iWidth, int iHeight, std::mt19937 & mt)
{
	// Initialize the blank vector
	m_vvTiles.resize(iHeight);

	for(auto it = m_vvTiles.begin();
		it != m_vvTiles.end();
		it++ )
	{
		(*it).resize(iWidth, ' ');
	}

	// We're going to divide the level into 4x2 chunks
	int iChunkWidth = iWidth / 4;
	int iChunkHeight = iHeight / 2;


	// The strategy here is to first draw a loop of tunnels on
	// the level, and then draw rooms on top of them.

	// Taking the easy way out, and generating
	// a loop of tunnels first to drop rooms on to
	for( int x = (iChunkWidth/2); x <= ((3 * iChunkWidth) + (iChunkWidth/2)); x++ )
	{
		m_vvTiles[iChunkHeight/2][x] = '#';
		m_vvTiles[iChunkHeight + (iChunkHeight/2)][x] = '#';
	}

	for( int y = (iChunkHeight/2); y <= (iChunkHeight + (iChunkHeight/2)); y++ )
	{
		m_vvTiles[y][iChunkWidth/2] = '#';
		m_vvTiles[y][(3 * iChunkWidth) + (iChunkWidth/2)] = '#';
	}

	// Pick rooms for the up and down stairs
	int iUpXChunk = mt() % 4;
	int iUpYChunk = mt() % 2;

	int iDownXChunk = mt() % 4;
	int iDownYChunk = mt() % 2;

	// Put them in different rooms...

	while( iUpXChunk == iDownXChunk && iUpYChunk == iDownYChunk )
	{
		iDownXChunk = mt() % 4;
		iDownYChunk = mt() % 2;
	}


	// So then we iterate through the chunks, and we
	// have individual blocks of the level which don't
	// overlap, so we're going to drop a room on each one.

	for( int iXChunk = 0; iXChunk < 4; iXChunk++ )
	{
		int iXStart = iXChunk * iChunkWidth;

		for( int iYChunk = 0; iYChunk < 2; iYChunk++ )
		{
			int iYStart = iYChunk * iChunkHeight;

			// Ok, so here we get a bit shifty.
			// We have 8 chunks.  We need to have 
			// at minimum 200 room tiles.  200/8 is
			// 25.  sqrt(25) is 5.  So we're going
			// to generate rooms of minimum size 5x5.

			int iRoomWidth = (mt() % (iChunkWidth - 5)) + 5;
			int iRoomHeight = (mt() % (iChunkHeight - 5)) + 5;

			// Randomly calculate the offset of the randomly
			// sized rood

			int iXOffset = mt() % (iChunkWidth - iRoomWidth);
			int iYOffset = mt() % (iChunkHeight - iRoomHeight);

			// Make sure this room lines up with the pre-generated
			// tunnels

			int iTunnelY = iYStart + (iChunkHeight/2);


			// Verify that the room matches the tunnel in the Y direction
			if( iYOffset + iYStart > iTunnelY )
			{
				iYOffset = iTunnelY - iYStart;
			}
			else if( iYOffset + iYStart + iRoomHeight <= iTunnelY )
			{
				iYOffset = 1 + iTunnelY - (iYStart + iRoomHeight);
			}

			// And check for the X direction (although this only matters for
			// rooms in the first or last chunk, X-wise)

			if( iXChunk == 0 || iXChunk == 3 )
			{
				int iTunnelX = iXStart + (iChunkWidth/2);

				if( iXOffset + iXStart > iTunnelX )
				{
//					iXOffset = iTunnelX - iXStart;
				}
				else if( iXOffset + iXStart + iRoomWidth <= iTunnelX )
				{
					iXOffset = 1 + iTunnelX - (iXStart + iRoomWidth);
				}

			}

			// And then put the generated room on the level

			for( int x = 0; x < iRoomWidth; x++ )
			{
				for( int y = 0; y < iRoomHeight; y++ )
				{
					m_vvTiles[y + iYOffset + iYStart][x + iXOffset + iXStart] = '.';
				}
			}

			// Check to see if we picked this room for up/down stairs, and
			// if so, randomly place the stairs

			if( iXChunk == iUpXChunk && iYChunk == iUpYChunk )
			{
				m_vvTiles[iYOffset + iYStart + (mt() % iRoomHeight)][iXOffset + iXStart + (mt() % iRoomWidth)] = '<';
			}

			if( iXChunk == iDownXChunk && iYChunk == iDownYChunk )
			{
				m_vvTiles[iYOffset + iYStart + (mt() % iRoomHeight)][iXOffset + iXStart + (mt() % iRoomWidth)] = '>';
			}

		}
	}

}


DungeonLevel::~DungeonLevel(void)
{
}


void DungeonLevel::dump()
{
	for( auto itOuter = m_vvTiles.begin();
		itOuter != m_vvTiles.end();
		itOuter++ )
	{
		for( auto itInner = (*itOuter).begin();
			itInner != (*itOuter).end();
			itInner++ )
		{
			cout << *itInner;
		}

		cout << endl;
	}
}

char DungeonLevel::at(int x, int y)
{
	return m_vvTiles[y][x];
}

int DungeonLevel::getWidth()
{
	return m_vvTiles[0].size();
}

int DungeonLevel::getHeight()
{
	return m_vvTiles.size();
}


