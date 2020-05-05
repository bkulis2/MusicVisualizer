// Copyright (c) 2020 [Benjamin Kulis]. All rights reserved.
#pragma once
#include <cinder/app/AppBasic.h>
#include <cinder/audio/Output.h>
#include <cinder/audio/Callback.h>
#include <cinder/CinderMath.h>

#include "KissFFT.h"
#include "Visualizer.h"

#ifndef INTERACTIVESINEVISUALIZER_H
#define INTERACTIVESINEVISUALIZER_H

namespace visualizer {
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
		float	max_frequency_;
		float	min_frequency_;
		bool    sine_playing_;
	};
} //namespace visualizer
#endif