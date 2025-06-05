#include "TitleScene.h"
#include "Record.h"

Record* rp;

class Base { // 基底クラス
public:
	Base() { OutputDebugString("BASE\n");}
	virtual ~Base() { OutputDebugString("~BASE\n");}
	virtual void F1() { OutputDebugString("Base::F1\n"); }
	virtual void F2() { OutputDebugString("Base::F2\n"); }
	void F3() { OutputDebugString("Base::F3\n"); }
private:
};

class Sub : public Base { // 派生クラス
public:
	Sub() { OutputDebugString("SUB\n");}
	~Sub() /*overrideは書かない*/ { OutputDebugString("~SUB\n");}
	void F1() override { OutputDebugString("Sub::F1\n"); };
	void F3() { OutputDebugString("Sub::F3\n"); }
	void Update() { F1(); F3();}
};

Sub* sub;
Base* base;
TitleScene::TitleScene()
{
	sub = new Sub();
	sub->F1();
	sub->F2();
	sub->F3();

	base = new Sub();
	base->F1();
	base->F2();
	base->F3();

	// インスタンスは、クラスの実体
	// 実体を複数作ることもできる
	Record r;
	Record r2; // 不要になったら、自動で消えるインスタンス

	rp = new Record(); // ヒープに作られるインスタンス
}

TitleScene::~TitleScene()
{
	delete rp; // ヒープメモリーを開放する

	delete sub;
	delete base;
}

void TitleScene::Update()
{
	if (CheckHitKey(KEY_INPUT_P)) {
		SceneManager::ChangeScene("PLAY");
	}
	if (CheckHitKey(KEY_INPUT_ESCAPE)) {
		SceneManager::Exit();
	}
}


void TitleScene::Draw()
{
	extern const char* Version();
	DrawString(0, 20, Version(), GetColor(255,255,255));
	DrawString(0, 0, "TITLE SCENE", GetColor(255,255,255));
	DrawString(100, 400, "Push [P]Key To Play", GetColor(255, 255, 255));
}
