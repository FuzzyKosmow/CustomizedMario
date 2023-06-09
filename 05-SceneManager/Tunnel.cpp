#include "Tunnel.h"

void CTunnel::Render()
{
	if (height <= 0) return;
	
	float xx = x;
	float yy = y;
	CSprites* s = CSprites::GetInstance();
	
	
		s->Get(idSpriteTopBlockLeft)->Draw(x, y);
		s->Get(idSpriteTopBlockRight)->Draw(x + TUNNEL_TOP_BLOCK_WIDTH , y );
		for (int i = 1; i < height; i++)
		{
			s->Get(idSpriteBottomBlockLeft)->Draw(x, y + TUNNEL_TOP_BLOCK_HEIGHT + (i - 1) * TUNNEL_BOTTOM_BLOCK_HEIGHT);
			s->Get(idSpriteBottomBlockRight)->Draw(x + TUNNEL_TOP_BLOCK_WIDTH, y + TUNNEL_TOP_BLOCK_HEIGHT + (i - 1) * TUNNEL_BOTTOM_BLOCK_HEIGHT);
		}
		
	
	
}

void CTunnel::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - TUNNEL_TOP_BLOCK_WIDTH / 2;
	t = y - TUNNEL_TOP_BLOCK_HEIGHT / 2;
	r = l + TUNNEL_TOP_BLOCK_WIDTH * 2;
	b = t + TUNNEL_TOP_BLOCK_HEIGHT + (height - 1) * TUNNEL_BOTTOM_BLOCK_HEIGHT;
}