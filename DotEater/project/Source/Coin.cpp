#include "Coin.h"
#include "Player.h"

Coin::Coin(VECTOR pos)
{
	hModel = MV1LoadModel("data/models/Coin.mv1");
	position = pos;
	gotten = false;
}

Coin::~Coin()
{
}

void Coin::Update()
{
	Player* pl = FindGameObject<Player>();
	VECTOR pPos = pl->GetPosition(); // �v���C���[�̑����̍��W
	pPos += VGet(0,50,0); // �R�C���Ɠ��������ɂ���

	if (gotten) {
		// ���ꂽ�̂ŁA�v���C���[�ɋ߂Â�
		// �P�D�R�C������v���C���[�Ɍ������x�N�g�������
		VECTOR v = pPos - position;
		// �Q�D���̃x�N�g���̒�����5�̂��̂����i�R�C���̈ړ��x�N�g���j
		v = VNorm(v) * 5.0f; // VNorm()�̓x�N�g���̒������P�ɂ���֐�
		// �R�D�R�C���̍��W�ɉ�����
		position += v;
		// �S�D�R�C���ƃv���C���[�̋�����10�ȉ��ɂȂ�����DestroyMe()
		float diff = VSize(pPos - position);
		if (diff < 10.0f) {
			DestroyMe();
		}
	} else {
		float diff = VSize(pPos - position);
		if (diff < 120.0f) { // �R�C���ɓ������Ă�
			gotten = true;
		}
	}
}
