#pragma once
// Record.h

// class�̃v���O����
// �f�[�^�́A�ł��邾���Aprivate�ɏ���
// �f�[�^���O�Ɍ���������΁A�֐���ʂ��āA�l�����Ԃ�
// �O���瑀�삳����ꍇ�ł��A���ڕϐ��ɑ�������Ȃ�

// �R���X�g���N�^�[�́A�����������������悤�ɂ���
// �����o�[�ϐ���������

// �f�X�g���N�^�[�́A������������Ƃ��ɁA��Еt��������
// new���Ă�����̂�����΁Adelete����
// ���[�h���Ă���f�ށi�摜�E���f���E���j������΁ADelete����

class Record
{
public:
	Record() { x = 0; life = 500; }
	~Record() {}
	int GetX() { return x; } // �ϐ���������ɂ̓Q�b�^�[�֐�
	bool IsDead() { return life <= 0; } // ���C�t�̕ϐ��͌����Ȃ����ǁA
	                                    // �m�肽������񋟂���
	void LifeMax() { life = 500; } // ���C�t�𑀍삷��֐�
private:
	float x; // �ϐ���private�ɏ����āA�O���珑�������Ȃ��悤�ɂ���
	int life;
};