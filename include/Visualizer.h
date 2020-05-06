// Copyright (c) 2020 [Benjamin Kulis]. All rights reserved.
#pragma once
#include "KissFFT.h"

#ifndef VISUALIZER_H
#define VISUALIZER_H

namespace visualizer {
	class Visualizer {
	public:
		virtual void shutdown() = 0;
		virtual void setup() = 0;
		virtual void draw() = 0;

	protected:
		void DrawVisualizerLines() {
			if (fft_) {
				float * frequency_data = fft_->getAmplitude();
				float * time_data = fft_->getData();
				int32_t bin_size = fft_->getBinSize();

				float scale = ((float)ci::app::getWindowWidth() - 20.0f) / (float)bin_size;
				float window_height = (float)ci::app::getWindowHeight();

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
				ci::gl::color(ci::ColorAf(0.5f, 0.0f, 0.5f));
				ci::gl::draw(frequency_line);
				ci::gl::color(ci::ColorAf(0.0f, 0.2f, 0.5f));
				ci::gl::draw(time_line);
			}
		}
		KissRef fft_;
	};
} //namespace visualizer
#endif