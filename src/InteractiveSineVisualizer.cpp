// Copyright (c) 2020 [Benjamin Kulis]. All rights reserved.

#include "InteractiveSineVisualizer.h"

namespace visualizer {

	void InteractiveSineVisualizer::setup() {
		amplitude_ = 0.5f;
		frequency_target_ = 0.0f;
		phase_ = 0.0f;
		phase_adjust_ = 0.0f;
		sine_playing_ = false;
	}

	void InteractiveSineVisualizer::draw() {
		if (!sine_playing_) {
			ci::audio::Output::play(
				ci::audio::createCallback(this, &InteractiveSineVisualizer::BuildSine));
			sine_playing_ = true;
		}
		InteractiveSineVisualizer::DrawVisualizerLines();
	}

	void InteractiveSineVisualizer::mouseMove(ci::app::MouseEvent event) {
		amplitude_ = kMaxAmplitude - event.getY() / (float)ci::app::getWindowHeight();
		double x = (double)ci::app::getWindowWidth() - (double)event.getX();
		float position = (float)((log((double)ci::app::getWindowWidth()) - log(x)) /
			log((double)ci::app::getWindowWidth()));
		frequency_target_ = ci::math<float>::clamp(kMaxFrequency * position,
			kMinFrequency, kMaxFrequency);
		amplitude_ = ci::math<float>::clamp(amplitude_ * (kMaxPosition - position),
			kMinPosition, kMaxPosition);
	}

	void InteractiveSineVisualizer::shutdown() {
		if (fft_) {
			fft_->stop();
		}
	}

	void InteractiveSineVisualizer::BuildSine(uint64_t sample_offset,
		uint32_t sample_count,
		ci::audio::Buffer32f *buffer) {
		phase_adjust_ = phase_adjust_ * kPhaseCorrection +
			(frequency_target_ / kSamplingFrequency) * kTimeOffset;
		for (uint32_t i = 0; i < sample_count; i++) {
			phase_ += phase_adjust_;
			phase_ = phase_ - ci::math<float>::floor(phase_);
			float val = ci::math<float>::sin(phase_ * kSinePeriod) * amplitude_;
			buffer->mData[i * buffer->mNumberChannels] = val;
			buffer->mData[i * buffer->mNumberChannels + 1] = val;
		}

		if (!fft_) {
			fft_ = Kiss::create(sample_count);
		}

		fft_->setData(buffer->mData);
	}
}  // namespace visualizer