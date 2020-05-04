#include <cinder/app/AppBasic.h>
#include <cinder/audio/Io.h>
#include <cinder/audio/Output.h>
#include <cinder/CinderMath.h>
#include <Resources.h>

#include "SongVisualizer.h"
#include "KissFFT.h"

namespace visualizer {
	void SongVisualizer::setup() {
		audio_source_file_ = ci::audio::load(ci::app::loadAsset("80s_soul.mp3"));
		track_ = ci::audio::Output::addTrack(audio_source_file_, false);
		track_->enablePcmBuffering(true);
		song_playing_ = false;
	}

	void SongVisualizer::draw() {
		if (!song_playing_) {
			track_->play();
			song_playing_ = true;
		}
		SongVisualizer::DrawVisualizerLines();
	}

	void SongVisualizer::shutdown() {
		track_->enablePcmBuffering(false);
		track_->stop();
		if (fft_) {
			fft_->stop();
		}
	}
}
