// Copyright (c) 2020 [Benjamin Kulis]. All rights reserved.
#pragma once
#include <cinder/app/AppBasic.h>
#include <cinder/audio/Callback.h>

#include "Visualizer.h"

#ifndef INTERACTIVESINEVISUALIZER_H
#define INTERACTIVESINEVISUALIZER_H

namespace visualizer {
	const float kMaxAmplitude = 1.0f;
	const float kMaxPosition = 1.0f;
	const float kMinPosition = 0.05f;
	const float kMaxFrequency = 20000.0f;
	const float kMinFrequency = 1.0f;
	const float kSamplingFrequency = 44100.0f;
	const float kPhaseCorrection = 0.95f;
	const float kTimeOffset = 0.05f;
	const float kSineConst = 2.0f * (float)M_PI;

	class InteractiveSineVisualizer : public Visualizer {
	public:
		void	setup() override;
		void	draw() override;
		void	mouseMove(ci::app::MouseEvent event);
		void	shutdown() override;

	private:
		void	BuildSine(uint64_t sample_offset, uint32_t sample_count, ci::audio::Buffer32f *buffer);
		float	amplitude_;
		float	frequency_target_;
		float	phase_;
		float	phase_adjust_;
		bool    sine_playing_;
	};
} //namespace visualizer
#endif