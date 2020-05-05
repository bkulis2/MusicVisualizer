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
		void update();
		std::string GetSongName();

		std::string song_name_;

	private:
		void InitializeSampleCount();

		ci::audio::SourceRef audio_source_file_;
		ci::audio::PcmBuffer32fRef buffer_;
		ci::audio::TrackRef track_;

		bool song_playing_;
	};
} // namespace visualizer
