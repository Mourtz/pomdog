﻿//
//  Copyright (C) 2013-2014 mogemimi.
//
//  Distributed under the MIT License.
//  See accompanying file LICENSE.md or copy at
//  http://enginetrouble.net/pomdog/LICENSE.md for details.
//

#include "SkinnedMeshCommand.hpp"

namespace Pomdog {
namespace Details {
namespace Rendering {
//-----------------------------------------------------------------------
void SkinnedMeshCommand::Execute(std::shared_ptr<GraphicsContext> const& graphicsContext)
{
	//auto transform = gameObject->Component<Transform2D>();
	//renderer->DrawSkeleton(polygonBatch, modelViewProjection);

	skinningEffect->Parameters("Constants")->SetValue(Matrix4x4::Transpose(modelViewProjection));
	{
		graphicsContext->SetTexture(0, texture);
		graphicsContext->SetInputLayout(inputLayout);
		graphicsContext->SetVertexBuffer(mesh->VertexBuffer);
		skinningEffect->Apply();
		graphicsContext->DrawIndexed(PrimitiveTopology::TriangleList,
			mesh->IndexBuffer, mesh->IndexBuffer->IndexCount());
	}
//	{
//		RasterizerDescription rasterizerDesc;
//		rasterizerDesc.FillMode = FillMode::WireFrame;
//		auto rasterizerState = std::make_shared<RasterizerState>(gameHost->GraphicsDevice(), rasterizerDesc);
//		
//		graphicsContext->SetRasterizerState(rasterizerState);
//		
//		graphicsContext->SetTexture(0, dummyTexture);
//		graphicsContext->SetInputLayout(inputLayout);
//		graphicsContext->SetVertexBuffer(mesh.VertexBuffer);
//		maidSkinningEffect->Apply();
//		graphicsContext->DrawIndexed(PrimitiveTopology::TriangleList,
//									 mesh.IndexBuffer, mesh.IndexBuffer->IndexCount());
//		
//		
//		graphicsContext->SetRasterizerState(RasterizerState::CreateCullCounterClockwise(gameHost->GraphicsDevice()));
//	}
}
//-----------------------------------------------------------------------
void SkinnedMeshCommand::SetMatrixPalette(Skeleton const& skeleton, SkeletonTransform const& skeletonTransform)
{
	std::array<Matrix3x2, 64> matrices;

	for (auto & joint: skeleton)
	{
		POMDOG_ASSERT(joint.Index);
		POMDOG_ASSERT(*joint.Index < matrices.size());
		POMDOG_ASSERT(*joint.Index < skeletonTransform.GlobalPose.size());
		matrices[*joint.Index] = joint.InverseBindPose * skeletonTransform.GlobalPose[*joint.Index];
	}

	auto const minMatrixCount = std::min(matrices.size(), skeletonTransform.GlobalPose.size());

	struct MatrixPalette {
		std::array<Vector4, 64> matrixPalette1;
		std::array<Vector4, 64> matrixPalette2;
	};
	
	MatrixPalette matrixPalette;
	
	for (std::size_t i = 0; i < minMatrixCount; ++i) {
		matrixPalette.matrixPalette1[i].X = matrices[i](0, 0);
		matrixPalette.matrixPalette1[i].Y = matrices[i](0, 1);
		matrixPalette.matrixPalette1[i].Z = matrices[i](1, 0);
		matrixPalette.matrixPalette1[i].W = matrices[i](1, 1);
		matrixPalette.matrixPalette2[i].X = matrices[i](2, 0);
		matrixPalette.matrixPalette2[i].Y = matrices[i](2, 1);
	}

	skinningEffect->Parameters("SkinningConstants")->SetValue(matrixPalette);
}
//-----------------------------------------------------------------------
}// namespace Rendering
}// namespace Details
}// namespace Pomdog