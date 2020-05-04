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
		KissRef fft_;
	};
} //namespace visualizer
#endif