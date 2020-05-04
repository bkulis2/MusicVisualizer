#pragma once
#include <cinder/audio/Io.h>
#include <cinder/audio/Output.h>
#include <cinder/CinderMath.h>
#include <Resources.h>

#include "KissFFT.h"
#include "Visualizer.h"

namespace visualizer {
	class SongVisualizer : public Visualizer {
		public:
			void setup() override;
			void draw() override;
			void shutdown() override;

		private:
			ci::audio::SourceRef audio_source_file_;
			ci::audio::PcmBuffer32fRef buffer_;
			ci::audio::TrackRef track_;
	};
} // namespace visualizer
