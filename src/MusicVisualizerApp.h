#include <cinder/app/AppBasic.h>
#include <cinder/audio/Output.h>
#include <cinder/audio/Callback.h>
#include <cinder/CinderMath.h>
#include "InteractiveSineVisualizer.h"
#include "SongVisualizer.h"

#ifndef MUSICVISUALIZERAPP_H
#define MUSICVISUALIZERAPP_H

namespace visualizer {
	class MusicVisualizerApp : public ci::app::AppBasic {

	public:
		void setup();
		void update();
		void draw();
		void mouseMove(ci::app::MouseEvent event);
		void mouseDown(ci::app::MouseEvent event);
		void shutdown();

	private:
		void PrintTitle() const;
		void PrintChoose() const;
		void DrawPlayButton() const;
		void DisplayPictures();
		void DrawSelectionRect();

		bool on_visualizer_screen_;
		bool selected_interactive_visualizer_;
		bool selected_song_visualizer_;

		InteractiveSineVisualizer sine_visualizer_;
		SongVisualizer song_visualizer_;
	};

	void PrintText(const std::string& text, const ci::ColorA& color, float font_size,
		const ci::Vec2i& size, const ci::Vec2f& loc);
} //namespace visualizer

#endif