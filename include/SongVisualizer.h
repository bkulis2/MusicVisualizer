// Copyright (c) 2020 [Benjamin Kulis]. All rights reserved.
#include <cinder/audio/Io.h>
#include <cinder/audio/Output.h>
#include <cinder/CinderMath.h>

#include "KissFFT.h"
#include "Visualizer.h"

namespace visualizer {
	class SongVisualizer : public Visualizer {

	public:
		void setup() override;
		void draw() override;
		void shutdown() override;
		void update();
		void SetSongName(const std::string &name);

	private:
		void InitializeSampleCount();

		ci::audio::SourceRef audio_source_file_;
		ci::audio::PcmBuffer32fRef buffer_;
		ci::audio::TrackRef track_;

		bool song_playing_;
		std::string song_name_;
	};
} // namespace visualizer
