#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include <vector>
#include <iostream>

class RayCast : public olc::PixelGameEngine
{
public:
	RayCast()
	{
		sAppName = "Ray Cast";
	}

	olc::vf2d vPlayer = { 0,0 };
	olc::vi2d vMapSize = { 32,30 };
	olc::vi2d vCellSize = { 16,16 };
	std::vector<int> vecMap;
	float fRayAngle;

private:
	void DrawBoard() {
		for(int y = 0; y < vMapSize.y; y++)
		{
			for(int x = 0; x < vMapSize.x; x++)
			{
				int cell = vecMap[y * vMapSize.x + x];
				if(cell == 1)
					FillRect(olc::vi2d(x,y) * vCellSize, vCellSize, olc::BLUE);
				DrawRect(olc::vi2d(x,y) * vCellSize, vCellSize, olc::DARK_GREY);
			}
		}
	}

private:
	void DrawRay(float ray2, olc::vf2d vRayStart){
			
		float step_count = 0.0f;
		bool hit = false;
		float max = 20.0f;

		float fEyeX = cos(ray2);
		float fEyeY = sin(ray2);

		while(!hit && step_count < max){
			step_count += vCellSize.x/10;

			int nTestX = (int)(vRayStart.x + fEyeX * step_count);
			int nTestY = (int)(vRayStart.y + fEyeY * step_count);

			int cell = vecMap[nTestY * vMapSize.x + nTestX];
			if(cell == 1){
				hit = true;
			}
			else if(nTestX > 0 || nTestX <= vMapSize.x || nTestY > 0 || nTestY <= vMapSize.y){	
				FillRect(olc::vi2d(nTestX, nTestY) * vCellSize, vCellSize, olc::WHITE);
				continue;
			}
		}
	}

public:
	bool OnUserCreate() override
	{
		vecMap.resize(vMapSize.x * vMapSize.y);
		fRayAngle = 0;
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		olc::vf2d vMouse = { float(GetMouseX()), float(GetMouseY()) };
		olc::vf2d vMouseCell = vMouse / vCellSize;
		olc::vi2d vCell = vMouseCell;

		if(GetMouse(olc::Mouse::LEFT).bHeld) vecMap[vCell.y * vMapSize.x + vCell.x] = 1;
		if(GetMouse(olc::Mouse::RIGHT).bHeld) vecMap[vCell.y * vMapSize.x + vCell.x] = 0;

		if(GetKey(olc::Key::W).bHeld) vPlayer.y -= 25.0f * fElapsedTime;
		if(GetKey(olc::Key::S).bHeld) vPlayer.y += 25.0f * fElapsedTime;
		if(GetKey(olc::Key::A).bHeld) vPlayer.x -= 25.0f * fElapsedTime;
		if(GetKey(olc::Key::D).bHeld) vPlayer.x += 25.0f * fElapsedTime;

		if(GetKey(olc::Key::RIGHT).bHeld) fRayAngle += 10.0f * fElapsedTime;
		if(GetKey(olc::Key::LEFT).bHeld) fRayAngle -= 10.0f * fElapsedTime;

		olc::vf2d vRayStart = vPlayer;

		Clear(olc::BLACK);
		DrawBoard();
		for(float ray = fRayAngle - 2; ray < fRayAngle; ray += 0.01f){
			DrawRay(ray, vRayStart);
		}
		
		FillCircle(vPlayer * vCellSize, 4.0f, olc::RED);
		DrawString({ 20, 20 }, "Angle: " + std::to_string(fRayAngle), olc::WHITE, 2);

		if(fRayAngle >= 360){
			fRayAngle = 0;
		}
		
		return true;
	}
};

int main(){
    RayCast rc;
    if(rc.Construct(512,480,4,4))
        rc.Start();

    return 0;
}