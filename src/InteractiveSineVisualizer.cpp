#include <cinder/audio/Output.h>
#include <cinder/audio/Callback.h>
#include <cinder/CinderMath.h>

#include "InteractiveSineVisualizer.h"
#include "KissFFT.h"

namespace visualizer {

	void InteractiveSineVisualizer::setup() {
		amplitude_ = 0.5f;
		max_frequency_ = 20000.0f;
		min_frequency_ = 1.0f;
		frequency_target_ = 0.0f;
		phase_ = 0.0f;
		phase_adjust_ = 0.0f;
		sine_playing_ = false;
	}

	void InteractiveSineVisualizer::draw() {
		if (!sine_playing_) {
			ci::audio::Output::play(ci::audio::createCallback(this, &InteractiveSineVisualizer::BuildSine));
			sine_playing_ = true;
		}
		InteractiveSineVisualizer::DrawVisualizerLines();
	}

	void InteractiveSineVisualizer::mouseMove(ci::app::MouseEvent event) {
		amplitude_ = 1.0f - event.getY() / (float) ci::app::getWindowHeight();
		double x = (double)ci::app::getWindowWidth() - (double)event.getX();
		float position = (float)((log((double)ci::app::getWindowWidth()) - log(x))
			/ log((double)ci::app::getWindowWidth()));
		frequency_target_ = ci::math<float>::clamp(max_frequency_
			* position, min_frequency_, max_frequency_);
		amplitude_ = ci::math<float>::clamp(amplitude_ * (1.0f - position), 0.05f, 1.0f);
	}

	void InteractiveSineVisualizer::shutdown() {
		if (fft_) {
			fft_->stop();
		}
	}

	void InteractiveSineVisualizer::BuildSine(uint64_t sample_offset, uint32_t sample_count, ci::audio::Buffer32f *buffer) {
		phase_adjust_ = phase_adjust_ * 0.95f + (frequency_target_ / 44100.0f) * 0.05f;
		for (uint32_t i = 0; i < sample_count; i++) {
			phase_ += phase_adjust_;
			phase_ = phase_ - ci::math<float>::floor(phase_);
			float val = ci::math<float>::sin(phase_ * 2.0f * (float)M_PI) * amplitude_;
			buffer->mData[i * buffer->mNumberChannels] = val;
			buffer->mData[i * buffer->mNumberChannels + 1] = val;
		}

		if (!fft_) {
			fft_ = Kiss::create(sample_count);
		}

		fft_->setData(buffer->mData);
	}
} //namespace visualizer
