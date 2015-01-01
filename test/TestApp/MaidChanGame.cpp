﻿//
//  Copyright (C) 2013-2015 mogemimi.
//  Distributed under the MIT License. See LICENSE.md or
//  http://enginetrouble.net/pomdog/license for details.
//

#include "MaidChanGame.hpp"
#include "Utilities/SandboxHelper.hpp"
#include "Utilities/LogSkeletalInfo.hpp"
#include <utility>

namespace TestApp {
//-----------------------------------------------------------------------
MaidChanGame::MaidChanGame(std::shared_ptr<GameHost> const& gameHostIn)
	: gameHost(gameHostIn)
	, graphicsContext(gameHostIn->GraphicsContext())
{}
//-----------------------------------------------------------------------
MaidChanGame::~MaidChanGame() = default;
//-----------------------------------------------------------------------
void MaidChanGame::Initialize()
{
	auto window = gameHost->Window();
	window->Title("TestApp - Enjoy Game Dev, Have Fun.");
	window->AllowPlayerResizing(true);
	
	auto graphicsDevice = gameHost->GraphicsDevice();
	auto assets = gameHost->AssetManager();

	{
		samplerPoint = SamplerState::CreateLinearWrap(graphicsDevice);
		
		auto blendState = BlendState::CreateNonPremultiplied(graphicsDevice);
		graphicsContext->SetBlendState(blendState);
		texture = assets->Load<Texture2D>("pomdog.png");
	}
	{
		renderTarget = std::make_shared<RenderTarget2D>(graphicsDevice,
			window->ClientBounds().Width, window->ClientBounds().Height,
			false, SurfaceFormat::R8G8B8A8_UNorm, DepthFormat::None);
	}
	{
		spriteRenderer = std::make_unique<SpriteRenderer>(graphicsContext, graphicsDevice);
		fxaa = std::make_unique<FXAA>(graphicsDevice);
		auto bounds = window->ClientBounds();
		fxaa->SetViewport(bounds.Width, bounds.Height);
		screenQuad = std::make_unique<ScreenQuad>(graphicsDevice);
	}
	{
		gameEditor = std::make_unique<SceneEditor::InGameEditor>(gameHost);
		editorBackground = std::make_unique<SceneEditor::EditorBackground>(gameHost);
	}
	

	{
		mainCamera = gameWorld.CreateObject();
		mainCamera.AddComponent<Transform2D>();
		mainCamera.AddComponent<Camera2D>();
	}
	{
		auto textureAtlas = TexturePacker::TextureAtlasLoader::Load(*assets, "MaidChan/skeleton.atlas");
		auto skeletonDesc = Spine::SkeletonDescLoader::Load(*assets, "MaidChan/skeleton.json");
		
		LogTexturePackerInfo(textureAtlas);
		LogSkeletalInfo(skeletonDesc);
		
		maidSkeleton = std::make_shared<Skeleton>(Spine::CreateSkeleton(skeletonDesc.Bones));
		maidSkeletonPose = std::make_shared<SkeletonPose>(SkeletonPose::CreateBindPose(*maidSkeleton));
		auto animationClip = std::make_shared<AnimationClip>(Spine::CreateAnimationClip(skeletonDesc, "Walk"));
		maidAnimationState = std::make_shared<AnimationState>(animationClip, 1.0f, true);
		
		maidGlobalPose = SkeletonHelper::ToGlobalPose(*maidSkeleton, *maidSkeletonPose);
		
		maidSkin = Spine::CreateSkin(skeletonDesc, textureAtlas, "default");
		maidSpriteAnimationTracks = Spine::CreateSpriteAnimationTrack(skeletonDesc, textureAtlas, "Walk");
		maidTexture = assets->Load<Texture2D>("MaidChan/skeleton.png");
		
		animationSystem.Add(maidAnimationState, maidSkeleton, maidSkeletonPose);
	}
	
	{
		scenePanel = std::make_shared<UI::ScenePanel>(window->ClientBounds().Width, window->ClientBounds().Height);
		scenePanel->cameraObject = mainCamera;
		gameEditor->AddView(scenePanel);
	}
	{
		auto stackPanel = std::make_shared<UI::StackPanel>(124, 170);
		stackPanel->Transform(Matrix3x2::CreateTranslation(Vector2{5, 10}));
		gameEditor->AddView(stackPanel);

		{
			auto navigator = std::make_shared<UI::DebugNavigator>(gameHost->Clock());
			stackPanel->AddChild(navigator);
		}
		{
			slider1 = std::make_shared<UI::Slider>(0.5, 2.0);
			slider1->Value(1.0);
			stackPanel->AddChild(slider1);
		}
		{
			slider2 = std::make_shared<UI::Slider>(-2.0, 2.0);
			slider2->Value(1.0);
			stackPanel->AddChild(slider2);
		}
		{
			toggleSwitch1 = std::make_shared<UI::ToggleSwitch>();
			toggleSwitch1->IsOn(true);
			stackPanel->AddChild(toggleSwitch1);
		}
		{
			toggleSwitch2 = std::make_shared<UI::ToggleSwitch>();
			toggleSwitch2->IsOn(true);
			stackPanel->AddChild(toggleSwitch2);
		}
		{
			toggleSwitch3 = std::make_shared<UI::ToggleSwitch>();
			toggleSwitch3->IsOn(false);
			stackPanel->AddChild(toggleSwitch3);
		}
		{
			toggleSwitch4 = std::make_shared<UI::ToggleSwitch>();
			toggleSwitch4->IsOn(false);
			stackPanel->AddChild(toggleSwitch4);
		}
	}
	
	clientSizeChangedConnection = window->ClientSizeChanged.Connect([this](int width, int height) {
		graphicsContext->Viewport(Viewport{0, 0, width, height});
		graphicsContext->ScissorRectangle(Rectangle{0, 0, width, height});
	
		renderTarget = std::make_shared<RenderTarget2D>(
			gameHost->GraphicsDevice(), width, height,
			false, SurfaceFormat::R8G8B8A8_UNorm, DepthFormat::None);

		fxaa->SetViewport(width, height);
		spriteRenderer->SetProjectionMatrix(Matrix4x4::CreateOrthographicLH(width, height, 1.0f, 100.0f));
	});
}
//-----------------------------------------------------------------------
void MaidChanGame::Update()
{
	auto clock = gameHost->Clock();
	auto mouse = gameHost->Mouse();
	{
		gameEditor->Update();
	}
	{
		maidAnimationState->PlaybackRate(slider2->Value());
	}
	
	if (toggleSwitch1->IsOn()) {
		animationSystem.Update(*clock);
	}
	{
		maidAnimationTimer.Update(clock->FrameDuration() * slider1->Value());
		if (maidAnimationTimer.Time() > maidAnimationState->Length()) {
			maidAnimationTimer.Reset();
		}

		SkeletonHelper::ToGlobalPose(*maidSkeleton, *maidSkeletonPose, maidGlobalPose);
	}
	{
		for (auto & track: maidSpriteAnimationTracks)
		{
			track.Apply(maidSkin, maidAnimationTimer.Time());
		}
	}
}
//-----------------------------------------------------------------------
void MaidChanGame::DrawSprites()
{
	auto transform = mainCamera.Component<Transform2D>();
	auto camera = mainCamera.Component<Camera2D>();
		
	POMDOG_ASSERT(transform && camera);
	auto viewMatrix = SandboxHelper::CreateViewMatrix(*transform, *camera);
	auto projectionMatrix = Matrix4x4::CreateOrthographicLH(
		graphicsContext->Viewport().Width(), graphicsContext->Viewport().Height(), 0.1f, 1000.0f);
	
	editorBackground->SetViewProjection(viewMatrix * projectionMatrix);

	POMDOG_ASSERT(spriteRenderer);
	spriteRenderer->Begin(SpriteSortMode::BackToFront, viewMatrix);
	
	auto const& globalPoses = maidGlobalPose;
	
	if (toggleSwitch3->IsOn())
	{
		for (auto & joint: *maidSkeleton)
		{
			auto & matrix = globalPoses[*joint.Index];
			spriteRenderer->Draw(texture, matrix, Vector2::Zero, {0, 0, 5, 5},
				Color::Red, MathConstants<float>::PiOver4(), {0.5f, 0.5f}, 1.0f, 2/100.0f);
			spriteRenderer->Draw(texture, matrix, Vector2::Zero, {0, 0, 2, 2},
				Color::White, MathConstants<float>::PiOver4(), {0.5f, 0.5f}, 1.0f, 1/100.0f);
			spriteRenderer->Draw(texture, matrix, Vector2::Zero, {0, 0, 32, 2},
				Color::Black, 0.0f, {0.0f, 0.5f}, 1.0f, 4/100.0f);
		}
	}

	if (toggleSwitch2->IsOn())
	{
		for (auto & slot: maidSkin.Slots())
		{
			spriteRenderer->Draw(maidTexture, globalPoses[*slot.JointIndex], slot.Translate, slot.Subrect,
				slot.Color, (slot.TextureRotate ? slot.Rotation - MathConstants<float>::PiOver2(): slot.Rotation),
				slot.Origin, slot.Scale, (maidSkin.Slots().size() - slot.DrawOrder) / maidSkin.Slots().size());
		}
	}
	
	spriteRenderer->End();
	
	if (toggleSwitch4->IsOn())
	{
		RasterizerDescription rasterizerDesc;
		rasterizerDesc.FillMode = FillMode::WireFrame;
		auto rasterizerState = std::make_shared<RasterizerState>(gameHost->GraphicsDevice(), rasterizerDesc);
		
		graphicsContext->SetRasterizerState(rasterizerState);
		spriteRenderer->Begin(SpriteSortMode::BackToFront, viewMatrix);
		
		for (auto & slot: maidSkin.Slots())
		{
			spriteRenderer->Draw(texture, globalPoses[*slot.JointIndex], slot.Translate, slot.Subrect,
				{0, 0, 0, 40},
				(slot.TextureRotate ? slot.Rotation - MathConstants<float>::PiOver2(): slot.Rotation),
				slot.Origin, slot.Scale, (maidSkin.Slots().size() - slot.DrawOrder) / maidSkin.Slots().size());
		}
		
		spriteRenderer->End();

		graphicsContext->SetRasterizerState(RasterizerState::CreateCullCounterClockwise(gameHost->GraphicsDevice()));
	}
}
//-----------------------------------------------------------------------
void MaidChanGame::Draw()
{
	constexpr bool enableFxaa = true;

	if (enableFxaa) {
		graphicsContext->SetRenderTarget(renderTarget);
	}
	
	graphicsContext->Clear(Color::CornflowerBlue);
	editorBackground->Draw(*graphicsContext);
	
	graphicsContext->SetSamplerState(0, samplerPoint);
	DrawSprites();
	
	if (enableFxaa) {
		graphicsContext->SetRenderTarget();
		graphicsContext->Clear(Color::CornflowerBlue);
		fxaa->SetTexture(renderTarget);
		fxaa->Apply(*graphicsContext);
		screenQuad->DrawQuad(*graphicsContext);
	}
	
	gameEditor->DrawGUI(*graphicsContext);
	graphicsContext->Present();
}
//-----------------------------------------------------------------------
}// namespace TestApp
