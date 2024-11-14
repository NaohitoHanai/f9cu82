#include "Coin.h"
#include "Player.h"
#include "Stage.h"

Coin::Coin()
{
	// �R���X�g���N�^�[�ŊG��Load����
	hImage = LoadGraph("data/image/parts.png");
	got = false;
}

Coin::~Coin()
{
}

void Coin::Update()
{
	if (got) {
		position.y += v;
		v += 1.0f; // �����鑬��
		counter -= 1; 
		if (counter == 0) {
			DestroyMe();
		}
		return;
	}
	// �����蔻��
	Player* p = FindGameObject<Player>(); // ����̃C���X�^���X���擾
	VECTOR2 playerPos = p->position; //����̍��W���擾
	if (CircleHit(playerPos, position, 40)) { // �~�̓����蔻��
		got = true;
		counter = 25;
		v = -15.0f; // ���˂鍂��
	}
}

void Coin::Draw()
{
	Stage* s = FindGameObject<Stage>();

	// �G�̕\��������
	DrawRectGraph(position.x - s->scroll, position.y, 120, 0, 40, 40, hImage, TRUE);
}
