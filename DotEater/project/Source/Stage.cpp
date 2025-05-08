#include "Stage.h"
#include <assert.h>
#include <vector>
using namespace std;

vector<vector<int>> map = {
	{ 1,1,0,1,1 },
	{ 1,1,1,0,1 },
	{ 1,1,1,0,1 },
};

Stage::Stage()
{
	hModel = MV1LoadModel("data/models/RedBrickBlock.mv1");
	assert(hModel>0);
	position = VGet(0,0,0);
	rotation = VGet(0,0,0);
	SetLightDirection(VGet(0,-1,0));
}

Stage::~Stage()
{
}

void Stage::Draw()
{
	for (int z = 0; z < map.size(); z++)
	{
		for (int x = 0; x < map[z].size(); x++)
		{
			if (map[z][x] == 1)
			{
				MV1SetPosition(hModel, VGet(x * 100.0f, 0, z * -100.0f));
				MV1DrawModel(hModel);
			}
		}
	}
}
