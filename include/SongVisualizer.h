// Copyright (c) 2020 [Benjamin Kulis]. All rights reserved.

#include "Visualizer.h"

#ifndef SONGVISUALIZER_H
#define SONGVISUALIZER_H

namespace visualizer {
	class SongVisualizer : public Visualizer {
	public:
		/**
		* This method is used to setup the logic to play the song file from
		* from the assets folder.
		*/
		void setup() override;

		/**
		* This method calls the DrawVisualizerLines method and plays the
		* song file if it isn't playing already (accounted for with a boolean).
		*/
		void draw() override;

		/**
		* This is used to stop the KissFFt library from analyzing the song
		* only if it currently is. In addition, it stops the the audio file
		* from playing.
		*/
		void shutdown() override;

		/**
		* This method has logic that updates the buffer and fft objects
		* to with new data so that the visualizer can be printed accurately.
		*/
		void update();

		/**
		* This method sets the song name to the second commandline arg.
		*/
		void SetSongName(const std::string &name);

	private:
		/**
		* This method updates the fft object with a new sample count
		* in addition to new data pulled from the buffer.
		*/
		void UpdateFft();

		ci::audio::SourceRef audio_source_file_;
		ci::audio::PcmBuffer32fRef buffer_;
		ci::audio::TrackRef track_;

		bool song_playing_;
		std::string song_name_;
	};
}  // namespace visualizer
#endif