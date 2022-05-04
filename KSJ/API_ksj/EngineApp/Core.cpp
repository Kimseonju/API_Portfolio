#include "Core.h"
#include <EngineDirectory.h>
#include <EngineFile.h>
#include <EngineWindowResMgr.h>
#include <EngineInput.h>

#include "TitleScene.h"
#include "SelectScene.h"
#include "PlayScene.h"
#include "RoomEditor.h"
#include <EngineSound.h>
#include "EndScene.h"
// Static Var
// Static Func

EngineSceneManager Core::SceneManager;
// member Var
Core::Core()
{

}

Core::~Core()
{

}
// member Func
void Core::Start()
{
	EngineDirectory Dir;
	Dir.MoveParent(L"API_ksj");
	Dir.MoveChild(L"Res");
	Dir.MoveChild(L"Texture");
	Dir.MoveChild(L"Title");

	std::vector<EngineFile> AllImageFile = Dir.DirectoryAllFileToVector(L"*.Bmp");

	for (size_t i = 0; i < AllImageFile.size(); i++)
	{
		EngineWindowResMgr::Inst().ImageLoad(AllImageFile[i].GetPath());
	}

	Dir.MoveParent(L"Texture");
	Dir.MoveChild(L"Player");

	AllImageFile = Dir.DirectoryAllFileToVector(L"*.Bmp");

	for (size_t i = 0; i < AllImageFile.size(); i++)
	{
		EngineWindowResMgr::Inst().ImageLoad(AllImageFile[i].GetPath());
	}

	Dir.MoveChild(L"Costume");

	AllImageFile = Dir.DirectoryAllFileToVector(L"*.Bmp");

	for (size_t i = 0; i < AllImageFile.size(); i++)
	{
		EngineWindowResMgr::Inst().ImageLoad(AllImageFile[i].GetPath());
	}
	Dir.MoveParent(L"Texture");
	Dir.MoveChild(L"Map");

	AllImageFile = Dir.DirectoryAllFileToVector(L"*.Bmp");

	for (size_t i = 0; i < AllImageFile.size(); i++)
	{
		EngineWindowResMgr::Inst().ImageLoad(AllImageFile[i].GetPath());
	}

	Dir.MoveParent(L"Texture");
	Dir.MoveChild(L"Item");
	Dir.MoveChild(L"Colliect");

	AllImageFile = Dir.DirectoryAllFileToVector(L"*.Bmp");

	for (size_t i = 0; i < AllImageFile.size(); i++)
	{
		EngineWindowResMgr::Inst().ImageLoad(AllImageFile[i].GetPath());
	}

	Dir.MoveParent(L"Texture");
	Dir.MoveChild(L"MapObject");

	AllImageFile = Dir.DirectoryAllFileToVector(L"*.Bmp");

	for (size_t i = 0; i < AllImageFile.size(); i++)
	{
		EngineWindowResMgr::Inst().ImageLoad(AllImageFile[i].GetPath());
	}


	Dir.MoveChild(L"BossDoor");

	AllImageFile = Dir.DirectoryAllFileToVector(L"*.Bmp");

	for (size_t i = 0; i < AllImageFile.size(); i++)
	{
		EngineWindowResMgr::Inst().ImageLoad(AllImageFile[i].GetPath());
	}

	Dir.MoveParent(L"MapObject");
	Dir.MoveChild(L"NormalDoor");

	AllImageFile = Dir.DirectoryAllFileToVector(L"*.Bmp");

	for (size_t i = 0; i < AllImageFile.size(); i++)
	{
		EngineWindowResMgr::Inst().ImageLoad(AllImageFile[i].GetPath());
	}
	Dir.MoveParent(L"MapObject");
	Dir.MoveChild(L"Treasure");

	AllImageFile = Dir.DirectoryAllFileToVector(L"*.Bmp");

	for (size_t i = 0; i < AllImageFile.size(); i++)
	{
		EngineWindowResMgr::Inst().ImageLoad(AllImageFile[i].GetPath());
	}
	Dir.MoveParent(L"Texture");
	Dir.MoveChild(L"Select");

	AllImageFile = Dir.DirectoryAllFileToVector(L"*.Bmp");

	for (size_t i = 0; i < AllImageFile.size(); i++)
	{
		EngineWindowResMgr::Inst().ImageLoad(AllImageFile[i].GetPath());
	}


	Dir.MoveParent(L"Texture");
	Dir.MoveChild(L"Effect");

	AllImageFile = Dir.DirectoryAllFileToVector(L"*.Bmp");

	for (size_t i = 0; i < AllImageFile.size(); i++)
	{
		EngineWindowResMgr::Inst().ImageLoad(AllImageFile[i].GetPath());
	}


	Dir.MoveParent(L"Texture");
	Dir.MoveChild(L"Monster");

	AllImageFile = Dir.DirectoryAllFileToVector(L"*.Bmp");

	for (size_t i = 0; i < AllImageFile.size(); i++)
	{
		EngineWindowResMgr::Inst().ImageLoad(AllImageFile[i].GetPath());
	}

	Dir.MoveChild(L"Boss");

	AllImageFile = Dir.DirectoryAllFileToVector(L"*.Bmp");

	for (size_t i = 0; i < AllImageFile.size(); i++)
	{
		EngineWindowResMgr::Inst().ImageLoad(AllImageFile[i].GetPath());
	}

	Dir.MoveParent(L"Texture");
	Dir.MoveChild(L"UI");
	Dir.MoveChild(L"BossAni");

	AllImageFile = Dir.DirectoryAllFileToVector(L"*.Bmp");

	for (size_t i = 0; i < AllImageFile.size(); i++)
	{
		EngineWindowResMgr::Inst().ImageLoad(AllImageFile[i].GetPath());
	}

	Dir.MoveParent(L"Texture");
	Dir.MoveChild(L"UI");
	Dir.MoveChild(L"MiniMap");

	AllImageFile = Dir.DirectoryAllFileToVector(L"*.Bmp");

	for (size_t i = 0; i < AllImageFile.size(); i++)
	{
		EngineWindowResMgr::Inst().ImageLoad(AllImageFile[i].GetPath());
	}

	Dir.MoveParent(L"Texture");
	Dir.MoveChild(L"UI");
	Dir.MoveChild(L"HP");

	AllImageFile = Dir.DirectoryAllFileToVector(L"*.Bmp");

	for (size_t i = 0; i < AllImageFile.size(); i++)
	{
		EngineWindowResMgr::Inst().ImageLoad(AllImageFile[i].GetPath());
	}

	Dir.MoveParent(L"Texture");
	Dir.MoveChild(L"UI");
	Dir.MoveChild(L"LoadImage");

	AllImageFile = Dir.DirectoryAllFileToVector(L"*.Bmp");

	for (size_t i = 0; i < AllImageFile.size(); i++)
	{
		EngineWindowResMgr::Inst().ImageLoad(AllImageFile[i].GetPath());
	}

	Dir.MoveParent(L"Texture");
	Dir.MoveChild(L"UI");
	Dir.MoveChild(L"Item");

	AllImageFile = Dir.DirectoryAllFileToVector(L"*.Bmp");

	for (size_t i = 0; i < AllImageFile.size(); i++)
	{
		EngineWindowResMgr::Inst().ImageLoad(AllImageFile[i].GetPath());
	}


	Dir.MoveParent(L"Texture");
	Dir.MoveChild(L"Map");
	Dir.MoveChild(L"Grid");

	AllImageFile = Dir.DirectoryAllFileToVector(L"*.Bmp");

	for (size_t i = 0; i < AllImageFile.size(); i++)
	{
		EngineWindowResMgr::Inst().ImageLoad(AllImageFile[i].GetPath());
	}


	Dir.MoveParent(L"Texture");
	Dir.MoveChild(L"Item");
	Dir.MoveChild(L"PickUp");

	AllImageFile = Dir.DirectoryAllFileToVector(L"*.Bmp");

	for (size_t i = 0; i < AllImageFile.size(); i++)
	{
		EngineWindowResMgr::Inst().ImageLoad(AllImageFile[i].GetPath());
	}
	Dir.MoveParent(L"Texture");
	Dir.MoveChild(L"Familiar");

	AllImageFile = Dir.DirectoryAllFileToVector(L"*.Bmp");

	for (size_t i = 0; i < AllImageFile.size(); i++)
	{
		EngineWindowResMgr::Inst().ImageLoad(AllImageFile[i].GetPath());
	}
	Dir.MoveParent(L"Texture");
	Dir.MoveChild(L"UI");
	Dir.MoveChild(L"Die");

	AllImageFile = Dir.DirectoryAllFileToVector(L"*.Bmp");

	for (size_t i = 0; i < AllImageFile.size(); i++)
	{
		EngineWindowResMgr::Inst().ImageLoad(AllImageFile[i].GetPath());
	}

	Dir.MoveParent(L"Texture");
	Dir.MoveChild(L"MapObject");
	Dir.MoveChild(L"SecretDoor");

	AllImageFile = Dir.DirectoryAllFileToVector(L"*.Bmp");

	for (size_t i = 0; i < AllImageFile.size(); i++)
	{
		EngineWindowResMgr::Inst().ImageLoad(AllImageFile[i].GetPath());
	}
	////////////////////////////////////////////////////////sound
	Dir.MoveParent(L"Res");
	Dir.MoveChild(L"Sound");
	AllImageFile = Dir.DirectoryAllFileToVector(L"*.mp3");

	for (size_t i = 0; i < AllImageFile.size(); i++)
	{
		EngineSound::Load(AllImageFile[i].GetPath());
	}
	Dir.MoveParent(L"Res");
	Dir.MoveChild(L"Sound");
	Dir.MoveChild(L"SFX");
	AllImageFile = Dir.DirectoryAllFileToVector(L"*.mp3");

	for (size_t i = 0; i < AllImageFile.size(); i++)
	{
		EngineSound::Load(AllImageFile[i].GetPath());
	}
	Dir.MoveParent(L"Res");
	Dir.MoveChild(L"Sound");
	Dir.MoveChild(L"SFX");
	Dir.MoveChild(L"boss");
	AllImageFile = Dir.DirectoryAllFileToVector(L"*.mp3");

	for (size_t i = 0; i < AllImageFile.size(); i++)
	{
		EngineSound::Load(AllImageFile[i].GetPath());
	}
	Dir.MoveParent(L"Res");
	Dir.MoveChild(L"Sound");
	Dir.MoveChild(L"SFX");
	Dir.MoveChild(L"enemy");
	AllImageFile = Dir.DirectoryAllFileToVector(L"*.mp3");

	for (size_t i = 0; i < AllImageFile.size(); i++)
	{
		EngineSound::Load(AllImageFile[i].GetPath());
	}
	Dir.MoveParent(L"Res");
	Dir.MoveChild(L"Sound");
	Dir.MoveChild(L"SFX");
	Dir.MoveChild(L"Object");
	AllImageFile = Dir.DirectoryAllFileToVector(L"*.mp3");

	for (size_t i = 0; i < AllImageFile.size(); i++)
	{
		EngineSound::Load(AllImageFile[i].GetPath());
	}
	Dir.MoveParent(L"Res");
	Dir.MoveChild(L"Video");
	AllImageFile = Dir.DirectoryAllFileToVector(L"*.mp3");

	for (size_t i = 0; i < AllImageFile.size(); i++)
	{
		EngineSound::Load(AllImageFile[i].GetPath());
	}


	ImageCut();


	SceneManager.CreateScene<TitleScene>(L"TitleScene");
	SceneManager.CreateScene<PlayScene>(L"PlayScene");
	SceneManager.CreateScene<SelectScene>(L"SelectScene");
	SceneManager.CreateScene<RoomEditor>(L"RoomEditor");
	SceneManager.CreateScene<EndScene>(L"EndScene");
	// 현재 씬을 지정.
	SceneManager.ChangeScene(L"TitleScene");

	KeyInput();
}

void Core::Update()
{
	SceneManager.ChangeCheck();
	SceneManager.GetCurScene()->Progress();
}

void Core::KeyInput() //모든키 생성은 여기서만 (중복생성시 충돌)
{
	EngineInput::CreateKey(L"SoundTestPlay", 'T');
	EngineInput::CreateKey(L"SoundTestStop", 'Y');


	EngineInput::CreateKey(L"L", 'A');
	EngineInput::CreateKey(L"R", 'D');
	EngineInput::CreateKey(L"U", 'W');
	EngineInput::CreateKey(L"D", 'S');
	EngineInput::CreateKey(L"Bomb", 'E');
	EngineInput::CreateKey(L"Kill", 'K');
	EngineInput::CreateKey(L"Item", 'I');


	EngineInput::CreateKey(L"Debug", 'Z');
	EngineInput::CreateKey(L"Debug2", 'X');


	EngineInput::CreateKey(L"Enter", VK_RETURN);
	EngineInput::CreateKey(L"ESC", VK_ESCAPE);
	EngineInput::CreateKey(L"LFire", VK_LEFT);
	EngineInput::CreateKey(L"RFire", VK_RIGHT);
	EngineInput::CreateKey(L"UFire", VK_UP);
	EngineInput::CreateKey(L"DFire", VK_DOWN);
	EngineInput::CreateKey(L"ActiveItem", VK_SPACE);

	//에디터용
	EngineInput::CreateKey(L"Save", VK_CONTROL, 'S');
	EngineInput::CreateKey(L"Load", VK_CONTROL, 'L');
	EngineInput::CreateKey(L"Create", VK_LBUTTON);
	EngineInput::CreateKey(L"Remove", VK_RBUTTON);
	EngineInput::CreateKey(L"Prev", 'Z');
	EngineInput::CreateKey(L"Next", 'C');
	EngineInput::CreateKey(L"RoomPrev", 'A');
	EngineInput::CreateKey(L"RoomNext", 'D');
}

void Core::ImageCut()
{
	EngineWindowResMgr::Inst().FindImage(L"shadow.bmp")->ImageCut(1, 1);

	//타이틀

	EngineWindowResMgr::Inst().FindImage(L"titleStart.bmp")->ImageCut(2, 1);

	//배경

	EngineWindowResMgr::Inst().FindImage(L"Baseboss.bmp")->ImageCut(1, 1);
	EngineWindowResMgr::Inst().FindImage(L"Basement1.bmp")->ImageCut(1, 1);
	EngineWindowResMgr::Inst().FindImage(L"BaseSecret.bmp")->ImageCut(1, 1);
	EngineWindowResMgr::Inst().FindImage(L"Basement2.bmp")->ImageCut(1, 1);
	EngineWindowResMgr::Inst().FindImage(L"Basement3.bmp")->ImageCut(1, 1);
	EngineWindowResMgr::Inst().FindImage(L"Basement4.bmp")->ImageCut(1, 1);
	EngineWindowResMgr::Inst().FindImage(L"Basement5.bmp")->ImageCut(1, 1);
	EngineWindowResMgr::Inst().FindImage(L"BaseMomBoss.bmp")->ImageCut(1, 1);
	EngineWindowResMgr::Inst().FindImage(L"controls.bmp")->ImageCut(1, 1);
	EngineWindowResMgr::Inst().FindImage(L"Treasure.bmp")->ImageCut(1, 1);
	//UI
	EngineWindowResMgr::Inst().FindImage(L"UI_hearts.bmp")->ImageCut(5, 2);
	EngineWindowResMgr::Inst().FindImage(L"MiniMapIcon.bmp")->ImageCut(4, 3);
	EngineWindowResMgr::Inst().FindImage(L"HUD_PickUp.bmp")->ImageCut(3, 2);
	EngineWindowResMgr::Inst().FindImage(L"NumberFont.bmp")->ImageCut(5, 2);
	EngineWindowResMgr::Inst().FindImage(L"UI_bosshealthbar.bmp")->ImageCut(1, 2);
	EngineWindowResMgr::Inst().FindImage(L"DieBackground.bmp")->ImageCut(1, 1);
	EngineWindowResMgr::Inst().FindImage(L"death_enemies.bmp")->ImageCut(7, 3);

	//플레이어
	EngineWindowResMgr::Inst().FindImage(L"Player_down.bmp")->ImageCut(10, 1);
	EngineWindowResMgr::Inst().FindImage(L"Player_right.bmp")->ImageCut(10, 1);
	EngineWindowResMgr::Inst().FindImage(L"Player_left.bmp")->ImageCut(10, 1);
	EngineWindowResMgr::Inst().FindImage(L"Player_up.bmp")->ImageCut(10, 1);
	EngineWindowResMgr::Inst().FindImage(L"PlayerEmotion.bmp")->ImageCut(4, 3);
	EngineWindowResMgr::Inst().FindImage(L"Player_head.bmp")->ImageCut(8, 1);

	//적
	EngineWindowResMgr::Inst().FindImage(L"flyidle.bmp")->ImageCut(5, 2);
	EngineWindowResMgr::Inst().FindImage(L"fiyDie.bmp")->ImageCut(4, 3);
	EngineWindowResMgr::Inst().FindImage(L"duke.bmp")->ImageCut(2, 2);
	EngineWindowResMgr::Inst().FindImage(L"Pooter.bmp")->ImageCut(4, 4);
	EngineWindowResMgr::Inst().FindImage(L"Horf.bmp")->ImageCut(2, 2);
	EngineWindowResMgr::Inst().FindImage(L"Boomfly.bmp")->ImageCut(2, 1);
	EngineWindowResMgr::Inst().FindImage(L"Deathshead.bmp")->ImageCut(5, 3);
	EngineWindowResMgr::Inst().FindImage(L"full_fly.bmp")->ImageCut(2, 1);
	EngineWindowResMgr::Inst().FindImage(L"Nerveending.bmp")->ImageCut(6, 1);
	EngineWindowResMgr::Inst().FindImage(L"Onetooth.bmp")->ImageCut(4, 2);
	EngineWindowResMgr::Inst().FindImage(L"Psychic_horf.bmp")->ImageCut(3, 1);
	EngineWindowResMgr::Inst().FindImage(L"PsychicEffect.bmp")->ImageCut(4, 2);
	EngineWindowResMgr::Inst().FindImage(L"Psychicmaw.bmp")->ImageCut(1, 1);
	EngineWindowResMgr::Inst().FindImage(L"Redboomfly.bmp")->ImageCut(2, 1);
	EngineWindowResMgr::Inst().FindImage(L"Dinga.bmp")->ImageCut(4, 1);
	EngineWindowResMgr::Inst().FindImage(L"Dip.bmp")->ImageCut(5, 1);
	EngineWindowResMgr::Inst().FindImage(L"Host.bmp")->ImageCut(3, 1);
	EngineWindowResMgr::Inst().FindImage(L"Moms_hand.bmp")->ImageCut(5, 2);
	EngineWindowResMgr::Inst().FindImage(L"Redmaw.bmp")->ImageCut(1, 1);
	EngineWindowResMgr::Inst().FindImage(L"Squirt.bmp")->ImageCut(3, 4);
	EngineWindowResMgr::Inst().FindImage(L"Sucker.bmp")->ImageCut(2, 1);
	EngineWindowResMgr::Inst().FindImage(L"Turret.bmp")->ImageCut(4, 4);



	EngineWindowResMgr::Inst().FindImage(L"flyidleHit.bmp")->ImageCut(5, 2);
	
	EngineWindowResMgr::Inst().FindImage(L"dukeHit.bmp")->ImageCut(2, 2);
	EngineWindowResMgr::Inst().FindImage(L"PooterHit.bmp")->ImageCut(4, 4);
	EngineWindowResMgr::Inst().FindImage(L"HorfHit.bmp")->ImageCut(2, 2);
	EngineWindowResMgr::Inst().FindImage(L"BoomflyHit.bmp")->ImageCut(2, 1);
	EngineWindowResMgr::Inst().FindImage(L"full_flyHit.bmp")->ImageCut(2, 1);
	EngineWindowResMgr::Inst().FindImage(L"NerveendingHit.bmp")->ImageCut(6, 1);
	EngineWindowResMgr::Inst().FindImage(L"OnetoothHit.bmp")->ImageCut(4, 2);
	EngineWindowResMgr::Inst().FindImage(L"Psychic_horfHit.bmp")->ImageCut(3, 1);
	EngineWindowResMgr::Inst().FindImage(L"PsychicmawHit.bmp")->ImageCut(1, 1);
	EngineWindowResMgr::Inst().FindImage(L"RedboomflyHit.bmp")->ImageCut(2, 1);
	EngineWindowResMgr::Inst().FindImage(L"DingaHit.bmp")->ImageCut(4, 1);
	EngineWindowResMgr::Inst().FindImage(L"DipHit.bmp")->ImageCut(5, 1);
	EngineWindowResMgr::Inst().FindImage(L"HostHit.bmp")->ImageCut(3, 1);
	EngineWindowResMgr::Inst().FindImage(L"Moms_handHit.bmp")->ImageCut(5, 2);
	EngineWindowResMgr::Inst().FindImage(L"RedmawHit.bmp")->ImageCut(1, 1);
	EngineWindowResMgr::Inst().FindImage(L"SquirtHit.bmp")->ImageCut(3, 4);
	EngineWindowResMgr::Inst().FindImage(L"SuckerHit.bmp")->ImageCut(2, 1);
	//엄마보스

	EngineWindowResMgr::Inst().FindImage(L"MomBodyDown.bmp")->ImageCut(3, 1);
	EngineWindowResMgr::Inst().FindImage(L"MomBodyLeft.bmp")->ImageCut(3, 1);
	EngineWindowResMgr::Inst().FindImage(L"MomBodyRight.bmp")->ImageCut(3, 1);
	EngineWindowResMgr::Inst().FindImage(L"MomBodyUp.bmp")->ImageCut(3, 1);
	EngineWindowResMgr::Inst().FindImage(L"MomHandDown.bmp")->ImageCut(3, 1);
	EngineWindowResMgr::Inst().FindImage(L"MomHandLeft.bmp")->ImageCut(3, 1);
	EngineWindowResMgr::Inst().FindImage(L"MomHandRight.bmp")->ImageCut(3, 1);
	EngineWindowResMgr::Inst().FindImage(L"MomHandUp.bmp")->ImageCut(3, 1);
	EngineWindowResMgr::Inst().FindImage(L"MomLeg.bmp")->ImageCut(1, 1);



	EngineWindowResMgr::Inst().FindImage(L"MomBodyDownHit.bmp")->ImageCut(3, 1);
	EngineWindowResMgr::Inst().FindImage(L"MomBodyLeftHit.bmp")->ImageCut(3, 1);
	EngineWindowResMgr::Inst().FindImage(L"MomBodyRightHit.bmp")->ImageCut(3, 1);
	EngineWindowResMgr::Inst().FindImage(L"MomBodyUpHit.bmp")->ImageCut(3, 1);
	EngineWindowResMgr::Inst().FindImage(L"MomHandDownHit.bmp")->ImageCut(3, 1);
	EngineWindowResMgr::Inst().FindImage(L"MomHandLeftHit.bmp")->ImageCut(3, 1);
	EngineWindowResMgr::Inst().FindImage(L"MomHandRightHit.bmp")->ImageCut(3, 1);
	EngineWindowResMgr::Inst().FindImage(L"MomHandUpHit.bmp")->ImageCut(3, 1);
	EngineWindowResMgr::Inst().FindImage(L"MomLegHit.bmp")->ImageCut(1, 1);


	EngineWindowResMgr::Inst().FindImage(L"MomBossAni.bmp")->ImageCut(1, 1);

	EngineWindowResMgr::Inst().FindImage(L"MomTitle.bmp")->ImageCut(1, 1);

	//눈물
	
	EngineWindowResMgr::Inst().FindImage(L"PlayerTear.bmp")->ImageCut(4, 4);
	EngineWindowResMgr::Inst().FindImage(L"EnemyTear.bmp")->ImageCut(4, 4);
	EngineWindowResMgr::Inst().FindImage(L"Brimstone_tears_Die_Down.bmp")->ImageCut(1, 1);
	EngineWindowResMgr::Inst().FindImage(L"Brimstone_tears_Die_Left.bmp")->ImageCut(1, 1);
	EngineWindowResMgr::Inst().FindImage(L"Brimstone_tears_Die_Right.bmp")->ImageCut(1, 1);
	EngineWindowResMgr::Inst().FindImage(L"Brimstone_tears_Die_Up.bmp")->ImageCut(1, 1);
	EngineWindowResMgr::Inst().FindImage(L"Brimstone_tears_LeftRight.bmp")->ImageCut(1, 1);
	EngineWindowResMgr::Inst().FindImage(L"Brimstone_tears_UpDowm.bmp")->ImageCut(1, 1);
	//오브젝트
	EngineWindowResMgr::Inst().FindImage(L"FireAni_down.bmp")->ImageCut(4, 1);
	EngineWindowResMgr::Inst().FindImage(L"fireAni_up.bmp")->ImageCut(6, 1);
	EngineWindowResMgr::Inst().FindImage(L"fireAni_up.bmp")->SetTransColor(RGB(255, 255, 255));
	EngineWindowResMgr::Inst().FindImage(L"poop.bmp")->ImageCut(5, 1);
	EngineWindowResMgr::Inst().FindImage(L"Pit.bmp")->ImageCut(4, 3);
	EngineWindowResMgr::Inst().FindImage(L"Spikes.bmp")->ImageCut(4, 2);
	EngineWindowResMgr::Inst().FindImage(L"rocks_basement.bmp")->ImageCut(4, 8);



	//이펙트
	EngineWindowResMgr::Inst().FindImage(L"Poof.bmp")->ImageCut(5, 4);
	EngineWindowResMgr::Inst().FindImage(L"EnemyDie.bmp")->ImageCut(3, 4);
	EngineWindowResMgr::Inst().FindImage(L"EnemyDiepoop.bmp")->ImageCut(3, 4);
	EngineWindowResMgr::Inst().FindImage(L"Explosion.bmp")->ImageCut(4, 4);
	EngineWindowResMgr::Inst().FindImage(L"ExplosionLayer.bmp")->ImageCut(3, 3);
	EngineWindowResMgr::Inst().FindImage(L"bombs.bmp")->ImageCut(5, 6);
	EngineWindowResMgr::Inst().FindImage(L"bombLayer.bmp")->ImageCut(4, 1);

	EngineWindowResMgr::Inst().FindImage(L"Hearteffect.bmp")->ImageCut(4, 4);
	EngineWindowResMgr::Inst().FindImage(L"giantbook_necronomicon.bmp")->ImageCut(1, 1);
	//아이템

	EngineWindowResMgr::Inst().FindImage(L"costume_drfetus.bmp")->ImageCut(8, 1);
	EngineWindowResMgr::Inst().FindImage(L"Costume_Sadonion.bmp")->ImageCut(3, 4);
	EngineWindowResMgr::Inst().FindImage(L"costume_wirehanger.bmp")->ImageCut(8, 1);
	EngineWindowResMgr::Inst().FindImage(L"costume_Momslipstick.bmp")->ImageCut(8, 1);
	EngineWindowResMgr::Inst().FindImage(L"costume_mutantspider.bmp")->ImageCut(8, 1);
	EngineWindowResMgr::Inst().FindImage(L"costume_catoninetails.bmp")->ImageCut(8, 1);
	EngineWindowResMgr::Inst().FindImage(L"costume_spoonbender.bmp")->ImageCut(8, 1);
	EngineWindowResMgr::Inst().FindImage(L"Costume_Sadonion.bmp")->ImageCut(3, 4);
	EngineWindowResMgr::Inst().FindImage(L"costume_HolyGrail_Body.bmp")->ImageCut(7, 4);
	EngineWindowResMgr::Inst().FindImage(L"costume_HolyGrail.bmp")->ImageCut(1, 1);
	EngineWindowResMgr::Inst().FindImage(L"ItemEffect.bmp")->ImageCut(4, 3);
	EngineWindowResMgr::Inst().FindImage(L"PickUp_heart.bmp")->ImageCut(3, 3);
	EngineWindowResMgr::Inst().FindImage(L"PickUp_Coin.bmp")->ImageCut(8, 3);
	EngineWindowResMgr::Inst().FindImage(L"pickup_chests.bmp")->ImageCut(6, 3);
	EngineWindowResMgr::Inst().FindImage(L"BombAttackBox.bmp")->ImageCut(2, 1);


	
	//패밀리어(펫)

	EngineWindowResMgr::Inst().FindImage(L"familiar_brotherbobby.bmp")->ImageCut(8, 1);
	EngineWindowResMgr::Inst().FindImage(L"familiar_littlechad.bmp")->ImageCut(4, 1);
	EngineWindowResMgr::Inst().FindImage(L"familiar_sackofpennies.bmp")->ImageCut(8, 1);
	EngineWindowResMgr::Inst().FindImage(L"familiar_sistermaggie.bmp")->ImageCut(8, 1);


	
	//문자르기
	EngineWindowResMgr::Inst().FindImage(L"LeftDoorAni_Down.bmp")->ImageCut(3, 1);
	EngineWindowResMgr::Inst().FindImage(L"LeftDoorAni_Left.bmp")->ImageCut(3, 1);
	EngineWindowResMgr::Inst().FindImage(L"LeftDoorAni_Right.bmp")->ImageCut(3, 1);
	EngineWindowResMgr::Inst().FindImage(L"LeftDoorAni_Up.bmp")->ImageCut(3, 1);

	EngineWindowResMgr::Inst().FindImage(L"NormalDoor_Right.bmp")->ImageCut(3, 1);
	EngineWindowResMgr::Inst().FindImage(L"NormalDoor_Down.bmp")->ImageCut(3, 1);
	EngineWindowResMgr::Inst().FindImage(L"NormalDoor_Left.bmp")->ImageCut(3, 1);
	EngineWindowResMgr::Inst().FindImage(L"NormalDoor_Up.bmp")->ImageCut(3, 1);


	EngineWindowResMgr::Inst().FindImage(L"RightDoorAni_Down.bmp")->ImageCut(3, 1);
	EngineWindowResMgr::Inst().FindImage(L"RightDoorAni_Left.bmp")->ImageCut(3, 1);
	EngineWindowResMgr::Inst().FindImage(L"RightDoorAni_Right.bmp")->ImageCut(3, 1);
	EngineWindowResMgr::Inst().FindImage(L"RightDoorAni_Up.bmp")->ImageCut(3, 1);


	EngineWindowResMgr::Inst().FindImage(L"BossDoor_Down.bmp")->ImageCut(3, 1);
	EngineWindowResMgr::Inst().FindImage(L"BossDoor_Left.bmp")->ImageCut(3, 1);
	EngineWindowResMgr::Inst().FindImage(L"BossDoor_Right.bmp")->ImageCut(3, 1);
	EngineWindowResMgr::Inst().FindImage(L"BossDoor_Up.bmp")->ImageCut(3, 1);
	EngineWindowResMgr::Inst().FindImage(L"LeftDoorAni_Boss_Down.bmp")->ImageCut(3, 1);
	EngineWindowResMgr::Inst().FindImage(L"LeftDoorAni_Boss_Left.bmp")->ImageCut(3, 1);
	EngineWindowResMgr::Inst().FindImage(L"LeftDoorAni_Boss_Right.bmp")->ImageCut(3, 1);
	EngineWindowResMgr::Inst().FindImage(L"LeftDoorAni_Boss_Up.bmp")->ImageCut(3, 1);
	EngineWindowResMgr::Inst().FindImage(L"RightDoorAni_Boss_Up.bmp")->ImageCut(3, 1);
	EngineWindowResMgr::Inst().FindImage(L"RightDoorAni_Boss_Down.bmp")->ImageCut(3, 1);
	EngineWindowResMgr::Inst().FindImage(L"RightDoorAni_Boss_Left.bmp")->ImageCut(3, 1);
	EngineWindowResMgr::Inst().FindImage(L"RightDoorAni_Boss_Right.bmp")->ImageCut(3, 1);
	EngineWindowResMgr::Inst().FindImage(L"TreasureDoor_Down.bmp")->ImageCut(3, 1);
	EngineWindowResMgr::Inst().FindImage(L"TreasureDoor_Left.bmp")->ImageCut(3, 1);
	EngineWindowResMgr::Inst().FindImage(L"TreasureDoor_Right.bmp")->ImageCut(3, 1);
	EngineWindowResMgr::Inst().FindImage(L"TreasureDoor_Up.bmp")->ImageCut(3, 1);


	EngineWindowResMgr::Inst().FindImage(L"LeftAni_Down.bmp")->ImageCut(3, 1);
	EngineWindowResMgr::Inst().FindImage(L"LeftAni_Left.bmp")->ImageCut(3, 1);
	EngineWindowResMgr::Inst().FindImage(L"LeftAni_Right.bmp")->ImageCut(3, 1);
	EngineWindowResMgr::Inst().FindImage(L"LeftAni_Up.bmp")->ImageCut(3, 1);
	EngineWindowResMgr::Inst().FindImage(L"SecretDoor_Right.bmp")->ImageCut(3, 1);
	EngineWindowResMgr::Inst().FindImage(L"SecretDoor_Down.bmp")->ImageCut(3, 1);
	EngineWindowResMgr::Inst().FindImage(L"SecretDoor_Left.bmp")->ImageCut(3, 1);
	EngineWindowResMgr::Inst().FindImage(L"SecretDoor_Up.bmp")->ImageCut(3, 1);
	EngineWindowResMgr::Inst().FindImage(L"RightAni_Down.bmp")->ImageCut(3, 1);
	EngineWindowResMgr::Inst().FindImage(L"RightAni_Left.bmp")->ImageCut(3, 1);
	EngineWindowResMgr::Inst().FindImage(L"RightAni_Right.bmp")->ImageCut(3, 1);
	EngineWindowResMgr::Inst().FindImage(L"RightAni_Up.bmp")->ImageCut(3, 1);
}

void Core::End()
{
	EngineSound::Release();

}