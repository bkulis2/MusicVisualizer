#include <cinder/app/AppBasic.h>
#include <cinder/audio/Io.h>
#include <cinder/audio/Output.h>
#include <cinder/CinderMath.h>
#include <Resources.h>

#include "SongVisualizer.h"
#include "KissFFT.h"

namespace visualizer {
	void SongVisualizer::setup() {
		song_name_ = "80s_soul.mp3";
		audio_source_file_ = ci::audio::load(ci::app::loadAsset(song_name_));
		track_ = ci::audio::Output::addTrack(audio_source_file_, false);
		track_->enablePcmBuffering(true);
		song_playing_ = false;
	}
	
	void SongVisualizer::update() {
		if (track_->isPlaying() && track_->isPcmBuffering()) {
			buffer_ = track_->getPcmBuffer();
			if (buffer_ && buffer_->getInterleavedData()) {
				SongVisualizer::InitializeSampleCount();
			}
		}
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

	std::string SongVisualizer::GetSongName() {
		return song_name_;
	}

	void SongVisualizer::InitializeSampleCount() {
		uint32_t sampleCount = buffer_->getInterleavedData()->mSampleCount;
		if (sampleCount > 0) {
			if (!fft_) {
				fft_ = Kiss::create(sampleCount);
			}

			if (buffer_->getInterleavedData()->mData != 0) {
				fft_->setData(buffer_->getInterleavedData()->mData);
			}
		}
	}
}
