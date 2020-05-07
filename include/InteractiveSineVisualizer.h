// Copyright (c) 2020 [Benjamin Kulis]. All rights reserved.
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
	const float kSinePeriod = 2.0f * (float)M_PI;

	class InteractiveSineVisualizer : public Visualizer {
	public:
		/**
		* This method sets all the variables that are going be modified
		* while the sine is being played and when the mouse is moved.
		*/
		void setup() override;

		/**
		* This method calls the DrawVisualizerLines method and plays the
		* sine wave if it isn't playing already (accounted for with a boolean).
		*/
		void draw() override;

		/**
		* This method takes in a MouseEvent and changes the frequency and
		* amplitude depending on the vertical and horizontal mouse
		* position. The position is scaled logarithmically to match up to
		* the logorithmic drawing of the frequency line.
		*/
		void mouseMove(ci::app::MouseEvent event);

		/**
		* This is used to stop the KissFFt library from analyzing the sine
		* only if it currently is.
		*/
		void shutdown() override;

	private:
		/**
		* This method fills the buffer with the same sine wave for all the samples
		*and then initializes the fft with the sample count. Followed by setting the
		*fft data with the data from the buffer.
		* @param sample_offset The time offset of the sample (not used because
		*creating my own sample aka sine, needed for Callback).
		* @param sample_count The number of samples contianed in our data set.
		* @param buffer A pointer to the buffer object to create the sine wave.
		*/
		void BuildSine(uint64_t sample_offset, uint32_t sample_count,
			ci::audio::Buffer32f *buffer);

		float amplitude_;
		float frequency_target_;
		float phase_;
		float phase_adjust_;
		bool sine_playing_;
	};
}  // namespace visualizer
#endif