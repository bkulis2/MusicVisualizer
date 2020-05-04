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

		if (fft_) {
			float * frequency_data = fft_->getAmplitude();
			float * time_data = fft_->getData();
			int32_t bin_size = fft_->getBinSize();

			float scale = ((float) ci::app::getWindowWidth() - 20.0f) / (float) bin_size;
			float window_height = (float) ci::app::getWindowHeight();

			ci::PolyLine<ci::Vec2f> frequency_line;
			ci::PolyLine<ci::Vec2f> time_line;

			for (int32_t i = 0; i < bin_size; i++) {
				float log_size = ci::math<float>::log((float)bin_size);
				float x = (float)((ci::math<float>::log((float)i) / log_size) * (float)bin_size);
				float y = ci::math<float>::clamp(frequency_data[i] * (x / (float)bin_size)
					* (ci::math<float>::log(((float)bin_size - (float)i))), 0.0f, 2.0f);

				frequency_line.push_back(ci::Vec2f(x * scale + 10.0f, -y
					* (window_height - 20.0f) * 0.25f + (window_height - 10.0f)));
				time_line.push_back(ci::Vec2f((float)i * scale + 10.0f, time_data[i]
					* (window_height - 20.0f) * 0.25f + (window_height * 0.25f + 10.0f)));
			}

			ci::gl::draw(frequency_line);
			ci::gl::draw(time_line);
		}
	}

	void InteractiveSineVisualizer::mouseMove(ci::app::MouseEvent event) {
		amplitude_ = 1.0f - event.getY() / (float) ci::app::getWindowHeight();
		double width = (double) ci::app::getWindowWidth();
		double x = width - (double)event.getX();
		float position = (float)((log(width) - log(x)) / log(width));
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
