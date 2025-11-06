#include "Stage.h"
#include <assert.h>
#include "Sky.h"
#include <fstream>
#include "Player.h"
#include "Goblin.h"
#include "Bee.h"
#include "Golem.h"
#include "RedGoblin.h"
#include "Needle.h"
#include "StageObject.h"
#include <string>

Stage::Stage(int number)
{
	char filename[16];
	sprintf_s<16>(filename, "Stage%02d", number);
	new StageObject(filename, VGet(0,0,0), VGet(0,0,0), VGet(1,1,1));
	ReadMappingData(filename);
	if (number == 0) {
		new Sky("Stage00_sky");
	}
	new Goblin(VECTOR3(0, 150, -1000), 0);
	new Goblin(VECTOR3(100, 150, -1200), 0);
}

Stage::~Stage()
{
	if (hModel > 0) {
		MV1DeleteModel(hModel);
		hModel = -1;
	}
}

bool Stage::CollideLine(const VECTOR& pos1, const VECTOR& pos2, VECTOR* hit) const
{
	VECTOR pos;
	StageObject* obj = FindGameObject<StageObject>();
	return obj->CollideLine(pos1, pos2, hit);
}

void Stage::ReadMappingData(std::string filename)
{
	const std::string folder = "data/model/Stage/";
	std::ifstream ifs(folder + filename + ".dat", std::ios::binary);
	assert(ifs); // 読めなければエラー

	struct Header {
		char chunk[4];
		int CharaInfoNum;
		int ObjectInfoNum;
		int EventInfoNum;
		VECTOR PlayerPosition;
		float PlayerAngle;
		int RenderType;
		int ClearCondition;
		int killCharaNum;
		int killTargetChara;
	};
	Header header;
	ifs.read((char*)&header, sizeof(header));
	new Player(header.PlayerPosition, header.PlayerAngle);

	// 8体(header.CharaInfoNum)の敵キャラを読む
	for (int i = 0; i < header.CharaInfoNum; i++) {
		struct CharaInfo {
			int id;
			VECTOR position;
			float angle;
		};
		CharaInfo chara;
		ifs.read((char*)&chara, sizeof(chara));
		switch (chara.id) {
		case 1:
			new Goblin(chara.position, chara.angle);
			break;
		case 2:
			new Bee(chara.position, chara.angle);
			break;
		case 3:
			new Golem(chara.position, chara.angle);
			break;
		case 4:
			new RedGoblin(chara.position, chara.angle);
			break;
		}
//		id 1:Goblin
//		   2:Bee
//		   3:Golem
//		   4:RedGoblin
	}
	// 167個(header.ObjectInfoNum)のオブジェクトを読む
	for (int i = 0; i < header.ObjectInfoNum; i++) {
		struct ObjectInfo {
			int id;
			VECTOR position;
			VECTOR rotation;
			VECTOR scale;
		};
		ObjectInfo object;
		ifs.read((char*)&object, sizeof(object));
		char s[256];
		sprintf_s<256>(s, "Stage_Obj%03d", object.id);
		new StageObject(s, object.position,
			object.rotation, object.scale);
	}

	struct EventInfo {
		int type;
		VECTOR position;
		VECTOR area;
		int bgm;
		int objectNum;
		int object[8];
	};
	ifs.close();
//	new Goblin(VECTOR3(0, 350, 1500), DX_PI);
//	new Goblin(VECTOR3(50, 350, 1500), DX_PI);
//	new RedGoblin(VECTOR3(300, 150, 500), 0);
}