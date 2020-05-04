#include <cinder/app/AppBasic.h>
#include <cinder/audio/Io.h>
#include <cinder/audio/Output.h>
#include <cinder/CinderMath.h>
#include <Resources.h>

#include "SongVisualizer.h"
#include "KissFFT.h"

namespace visualizer {
	void SongVisualizer::setup() {
		audio_source_file_ = ci::audio::load(ci::app::loadResource(SONG_FILE));
		track_ = ci::audio::Output::addTrack(audio_source_file_, false);
		track_->enablePcmBuffering(true);
		//fix to play only once with boolean
		//mTrack->play();
	}
}
