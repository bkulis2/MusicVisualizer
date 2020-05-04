#pragma once
#include "cinder/app/AppBasic.h"
#include "cinder/audio/Output.h"
#include "cinder/audio/Callback.h"
#include "cinder/CinderMath.h"
#include "KissFFT.h"

#ifndef INTERACTIVESINE_H
#define INTERACTIVESINE_H

namespace visualizer {
	class InteractiveSine {
	public:
		void	setup();
		void	draw();
		void	mouseMove(ci::app::MouseEvent event);
		void	shutdown();

	private:
		void	sineWave(uint64_t sample_offset, uint32_t sample_count, ci::audio::Buffer32f *buffer);
		float	amplitude_;
		float	frequency_target_;
		float	phase_;
		float	phase_adjust_;
		float	max_frequency_;
		float	min_frequency_;
		bool    sine_playing_;
		KissRef fft_;
	};
} //namespace visualizer

#endif