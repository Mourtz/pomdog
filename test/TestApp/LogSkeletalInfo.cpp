﻿//
//  Copyright (C) 2013-2014 mogemimi.
//
//  Distributed under the MIT License.
//  See accompanying file LICENSE.md or copy at
//  http://enginetrouble.net/pomdog/LICENSE.md for details.
//

#include "LogSkeletalInfo.hpp"

namespace TestApp {

using namespace Pomdog;

void LogSkeletalInfo(Details::TexturePacker::TextureAtlas const& textureAtlas,
	Details::Skeletal2D::SkeletonDesc const& skeletonDesc)
{
	Log::Info(StringFormat("TextureAtlas.Pages = %ld", textureAtlas.pages.size()));
	Log::Info(StringFormat("TextureAtlas.Regions = %ld", textureAtlas.regions.size()));
	
	for (auto page: textureAtlas.pages)
	{
		Log::Info(StringFormat("Page.Name = %s", page.Name.c_str()));
	}
	
	for (auto region: textureAtlas.regions)
	{
		Log::Info(StringFormat("Region.Name = %s", region.Name.c_str()));
		Log::Info(StringFormat("  Region.Page = %d", region.TexturePage));
		Log::Info(StringFormat("  Region.Rotate = %d", region.Region.Rotate?1:0));
		Log::Info(StringFormat("  Region.Flip = %d", region.Region.Flip?1:0));
		Log::Info(StringFormat("  Region.XY = %d, %d", (int)region.Region.Subrect.X, (int)region.Region.Subrect.Y));
		Log::Info(StringFormat("  Region.Size = %d, %d", (int)region.Region.Subrect.Width, (int)region.Region.Subrect.Height));
		Log::Info(StringFormat("  Region.Offset = %d %d", (int)region.Region.XOffset, (int)region.Region.YOffset));
		Log::Info(StringFormat("  Region.OriginalSize = %d %d", (int)region.Region.Width, (int)region.Region.Height));
	}

	Log::Info("-------------------------");
	for (auto & bone: skeletonDesc.Bones)
	{
		Log::Info(StringFormat("MaidChan/%s", bone.Name.c_str()));
		Log::Info(StringFormat("  Bone.Translate = %f, %f", bone.Pose.Translate.X, bone.Pose.Translate.Y));
		Log::Info(StringFormat("  Bone.Rotation = %f", bone.Pose.Rotation.value));
		Log::Info(StringFormat("  Bone.Scale = %f", bone.Pose.Scale));
	}
	
	Log::Info("-------------------------");
	for (auto & animationClip: skeletonDesc.AnimationClips)
	{
		for (auto & track: animationClip.BoneTracks)
		{
			Log::Info(StringFormat("AnimationClip/%s/Bones/%s", animationClip.Name.c_str(), track.BoneName.c_str()));
			for (auto & sample: track.TranslateSamples)
			{
				Log::Info(StringFormat("  {time: %f, x: %f, y: %f},",
					sample.Time.count(),
					sample.TranslateX.ToFloat(),
					sample.TranslateY.ToFloat()));
			}
			for (auto & sample: track.RotateSamples)
			{
				Log::Info(StringFormat("  {time: %f, rotate: %f},",
					sample.Time.count(),
					sample.Rotation.ToFloat()));
			}
			for (auto & sample: track.ScaleSamples)
			{
				Log::Info(StringFormat("  {time: %f, rotate: %f},",
					sample.Time.count(),
					sample.Scale.ToFloat()));
			}
		}
		for (auto & track: animationClip.SlotTracks)
		{
			Log::Info(StringFormat("AnimationClip/%s/Slots/%s", animationClip.Name.c_str(), track.SlotName.c_str()));
			for (auto & sample: track.AttachmentSamples)
			{
				Log::Info(StringFormat("  {time: %f, name: %s},",
					sample.Time.count(),
					sample.AttachmentName.c_str()));
			}
		}
	}
}

}// namespace TestApp