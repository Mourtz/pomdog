//
//  Copyright (C) 2013-2014 mogemimi.
//
//  Distributed under the MIT License.
//  See accompanying file LICENSE.md or copy at
//  http://enginetrouble.net/pomdog/LICENSE.md for details.
//

#ifndef POMDOG_MAIDBEAMGAME_EC7DAEEE_4167_40CD_931D_B8627B24F68E_HPP
#define POMDOG_MAIDBEAMGAME_EC7DAEEE_4167_40CD_931D_B8627B24F68E_HPP

#if (_MSC_VER > 1000)
#	pragma once
#endif

#include <Pomdog/Pomdog.hpp>
#include "SceneEditor/InGameEditor.hpp"
#include "UI/DrawingContext.hpp"
#include "UI/UIElementHierarchy.hpp"
#include "UI/ScenePanel.hpp"
#include "UI/Slider.hpp"
#include "UI/ToggleSwitch.hpp"
#include "Graphics/PolygonBatch.hpp"
#include "Graphics/LineBatch.hpp"

namespace Pomdog {

class SpriteBatch;
class SceneNode;

}// namespace Pomdog

namespace TestApp {

using namespace Pomdog;

class SpriteRenderer;
class FXAA;

class MaidBeamGame: public Game {
public:
	explicit MaidBeamGame(std::shared_ptr<GameHost> const& gameHost);

	~MaidBeamGame();

	void Initialize();
	
	void Update();
	
	void Draw();

private:
	std::shared_ptr<GameHost> gameHost;
	std::shared_ptr<GraphicsContext> graphicsContext;
	
	std::shared_ptr<Texture2D> texture;
	std::unique_ptr<SpriteRenderer> spriteRenderer;

	std::shared_ptr<RenderTarget2D> renderTarget;
	std::unique_ptr<FXAA> fxaa;

	std::unique_ptr<SceneEditor::InGameEditor> gameEditor;
	std::shared_ptr<UI::ScenePanel> scenePanel;
	std::shared_ptr<UI::Slider> slider1;
	std::shared_ptr<UI::Slider> slider2;
	std::shared_ptr<UI::ToggleSwitch> toggleSwitch1;
	std::shared_ptr<UI::ToggleSwitch> toggleSwitch2;
	std::shared_ptr<UI::ToggleSwitch> toggleSwitch3;
	std::shared_ptr<UI::ToggleSwitch> toggleSwitch4;

	GameWorld gameWorld;
	std::shared_ptr<GameObject> mainCamera;
	std::shared_ptr<GameObject> maid;
	std::shared_ptr<GameObject> lightningBeam;
	
	ScopedConnection clientSizeChangedConnection;
	
	std::unique_ptr<PolygonBatch> polygonBatch;
};

}// namespace TestApp

#endif // !defined(POMDOG_MAIDBEAMGAME_EC7DAEEE_4167_40CD_931D_B8627B24F68E_HPP)