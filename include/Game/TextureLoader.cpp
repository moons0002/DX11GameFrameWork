#include "TextureLoader.h"

#include "../Asset/AssetManager.h"

bool TextureLoader::Init()
{
	std::shared_ptr<CTextureManager> TextureManager = CAssetManager::GetInstance().GetTextureManager();

    // Kirby
	TextureManager->LoadTexture("Kirby", TEXT("Texture/Kirby.png"), "Kirby");
    TextureManager->PushBackLoadTexture("Kirby", TEXT("Texture/KirbyAir.png"), "KirbyAir");
    TextureManager->PushBackLoadTexture("Kirby", TEXT("Texture/KirbyJump2.png"), "KirbyJump2");
    TextureManager->PushBackLoadTexture("Kirby", TEXT("Texture/KirbyDamage.png"), "KirbyDamage");

    TextureManager->PushBackLoadTexture("Kirby", TEXT("Texture/KirbyBeamIdle.png"), "BeamIdle");
    TextureManager->PushBackLoadTexture("Kirby", TEXT("Texture/KirbyBeamWalk.png"), "BeamWalk");
    TextureManager->PushBackLoadTexture("Kirby", TEXT("Texture/BeamKirby.png"), "BeamKirby");
    TextureManager->PushBackLoadTexture("Kirby", TEXT("Texture/BeamKirby2.png"), "BeamKirby2");
    TextureManager->PushBackLoadTexture("Kirby", TEXT("Texture/BeamKirby3.png"), "BeamKirby3");

    // BeamObject
    TextureManager->LoadTexture("BeamObject", TEXT("Texture/BeamObject.png"), "BeamObject");

    // Enem
    TextureManager->LoadTexture("BrontoBurt", TEXT("Texture/BrontoBurt.png"), "BrontoBurt");
    TextureManager->LoadTexture("Beam", TEXT("Texture/BeamWalk.png"), "Walk");
    TextureManager->PushBackLoadTexture("Beam", TEXT("Texture/BeamDamaged.png"), "Damaged");

    // Prejectile
    TextureManager->LoadTexture("Projectile", TEXT("Texture/TestProjectile.png"), "Test");
    TextureManager->PushBackLoadTexture("Projectile", TEXT("Texture/StarProjectile.png"), "Star");

    // UI
    TextureManager->LoadTexture("KirbyHP", TEXT("Texture/KirbyHP.png"), "KirbyHp");
    TextureManager->LoadTexture("BackGround", TEXT("Texture/BackGround_0.png"), "BackGround_0");
    TextureManager->LoadTexture("BottomScreen", TEXT("Texture/BottomScreen.png"), "BottomScreen");
    TextureManager->LoadTexture("GeneralRips", TEXT("Texture/GeneralRips.png"), "GeneralRips");
    TextureManager->LoadTexture("ScoreLetter", TEXT("Texture/ScoreLetter.png"), "ScoreLetter");
    TextureManager->LoadTexture("StageIcon", TEXT("Texture/StageIcons.png"), "StageIcon");

    // Map
    TextureManager->LoadTexture("Map", TEXT("Texture/Stage_1_1.png"), "Stage_1_1");
    TextureManager->PushBackLoadTexture("Map", TEXT("Texture/Stage_1_1_0.png"), "Stage_1_1_0");

    // Effect
    TextureManager->LoadTexture("Effect", TEXT("Texture/BeamEffect1.png"), "BeamEffect1");

    // Color
    TextureManager->LoadTexture("Color", TEXT("Texture/Black.png"), "Black");

    // PauseScreen
    TextureManager->LoadTexture("PauseScreen", TEXT("Texture/PauseBackGround.png"), "BackGround");
    TextureManager->PushBackLoadTexture("PauseScreen", TEXT("Texture/Pause2.png"), "Pause0");
    TextureManager->PushBackLoadTexture("PauseScreen", TEXT("Texture/Pause3.png"), "Pause1");
    TextureManager->PushBackLoadTexture("PauseScreen", TEXT("Texture/Pause4.png"), "Pause2");
    TextureManager->PushBackLoadTexture("PauseScreen", TEXT("Texture/PrevNextPage.png"), "PrevNextPage");

    return true;
}