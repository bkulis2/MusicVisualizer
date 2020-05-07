// Copyright (c) 2020 [Benjamin Kulis]. All rights reserved.
#include "MusicVisualizerApp.h"

#include <cinder/ImageIo.h>
#include <cinder/Rand.h>
#include <cinder/Text.h>
#include <cinder/gl/Texture.h>

using ci::app::App;
using ci::app::RendererGl;

namespace visualizer {

	void MusicVisualizerApp::setup() {
		setFrameRate(kFrameRate);
		setWindowSize(kWidth, kHeight);

		on_visualizer_screen_ = false;
		selected_sine_visualizer_ = false;
		selected_song_visualizer_ = false;

		ci::gl::enable(GL_LINE_SMOOTH);
		glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
		ci::gl::color(ci::ColorAf::white());

		sine_visualizer_.setup();
		song_visualizer_.SetSongName(MusicVisualizerApp::getArgs()[1]);
		song_visualizer_.setup();
	}

	void MusicVisualizerApp::update() {
		if (selected_song_visualizer_) {
			song_visualizer_.update();
		}
	}

	void MusicVisualizerApp::draw() {
		ci::gl::enableAlphaBlending();
		if (!on_visualizer_screen_) {
			ci::gl::clear(ci::ColorAf(0.5, 0, 0.5));
			PrintTitle();
			PrintChoose();
			DisplayImages();
			DrawSelectionRect();
		}
		else if (selected_sine_visualizer_) {
			ci::gl::clear(ci::ColorAf::black());
			sine_visualizer_.draw();
		}
		else if (selected_song_visualizer_) {
			ci::gl::clear(ci::ColorAf::black());
			song_visualizer_.draw();
		}
	}

	void MusicVisualizerApp::mouseMove(ci::app::MouseEvent event) {
		if (selected_sine_visualizer_) {
			sine_visualizer_.mouseMove(event);
		}
	}

	void MusicVisualizerApp::mouseDown(ci::app::MouseEvent event) {
		if (event.isLeft() &&
			(event.getX() >= kBtnImgLoc.x &&
				event.getX() <= kBtnImgLoc.x + kImgDimension) &&
				(event.getY() >= kBtnImgLoc.y &&
					event.getY() <= kBtnImgLoc.y + kBtnHeightDimension)) {
			on_visualizer_screen_ = true;
		}
		else if (event.isLeft() &&
			(event.getX() >= kSineImgLoc.x &&
				event.getX() <= kSineImgLoc.x + kImgDimension) &&
				(event.getY() >= kSineImgLoc.y &&
					event.getY() <= kSineImgLoc.y + kImgDimension)) {
			selected_sine_visualizer_ = true;
			selected_song_visualizer_ = false;
		}
		else if (event.isLeft() &&
			(event.getX() >= kNoteImgLoc.x &&
				event.getX() <= kNoteImgLoc.x + kImgDimension) &&
				(event.getY() >= kNoteImgLoc.y &&
					event.getY() <= kNoteImgLoc.y + kImgDimension)) {
			selected_sine_visualizer_ = false;
			selected_song_visualizer_ = true;
		}
	}

	void MusicVisualizerApp::shutdown() {
		if (selected_sine_visualizer_) {
			sine_visualizer_.shutdown();
		}
		else {
			song_visualizer_.shutdown();
		}
	}

	void MusicVisualizerApp::PrintTitle() const {
		ci::gl::color(ci::Rand::randFloat(), ci::Rand::randFloat(),
			ci::Rand::randFloat());
		ci::gl::drawStrokedRect(
			ci::Rectf(getWindowWidth() / 2 - 170.0f, getWindowHeight() / 2 - 330.0f,
				getWindowWidth() / 2 + 170.0f, getWindowHeight() / 2 - 170.0f));
		PrintText(
			"Music\nVisualizer", ci::ColorAf::black(), 80.0f, ci::Vec2i(500, 150),
			ci::Vec2f((float)getWindowWidth() / 2, getWindowHeight() / 2 - 250.0f));
	}

	void MusicVisualizerApp::PrintChoose() const {
		float font_size = 50.0f;
		PrintText(
			"Song File You Chose:", ci::ColorAf::white(), font_size,
			ci::Vec2i(500, 150),
			ci::Vec2f(getWindowWidth() / 2 - 200.0f, getWindowHeight() / 2 - 50.0f));
		PrintText(
			MusicVisualizerApp::getArgs()[1], ci::ColorAf(0, 0.7, 0), font_size,
			ci::Vec2i(500, 150),
			ci::Vec2f(getWindowWidth() / 2 + 125.0f, getWindowHeight() / 2 - 50.0f));
		PrintText(
			"Choose Your Mode:", ci::ColorAf::white(), font_size, ci::Vec2i(500, 150),
			ci::Vec2f(getWindowWidth() / 2 - 215.0f, getWindowHeight() / 2 + 75.0f));
	}

	void MusicVisualizerApp::DisplayImages() const {
		auto texture_one =
			ci::gl::Texture(ci::loadImage(ci::app::loadAsset("sine.png")));
		ci::gl::draw(texture_one, kSineImgLoc);
		auto texture_two =
			ci::gl::Texture(ci::loadImage(ci::app::loadAsset("notes.png")));
		ci::gl::draw(texture_two, kNoteImgLoc);
		auto texture_three =
			ci::gl::Texture(ci::loadImage(ci::app::loadAsset("playbutton.png")));
		ci::gl::draw(texture_three, kBtnImgLoc);
	}

	void MusicVisualizerApp::DrawSelectionRect() {
		if (selected_sine_visualizer_) {
			cinder::gl::color(cinder::Color::white());
			ci::Rectf rect(kSineImgLoc.x - kImgBorderSize,
				kSineImgLoc.y - kImgBorderSize,
				kSineImgLoc.x + kImgDimension + kImgBorderSize,
				kSineImgLoc.y + kImgDimension + kImgBorderSize);
			cinder::gl::drawStrokedRect(rect);
		}
		else if (selected_song_visualizer_) {
			cinder::gl::color(cinder::Color::white());
			ci::Rectf rect(kNoteImgLoc.x - kImgBorderSize,
				kNoteImgLoc.y - kImgBorderSize,
				kNoteImgLoc.x + kImgDimension + kImgBorderSize,
				kNoteImgLoc.y + kImgDimension + kImgBorderSize);
			cinder::gl::drawStrokedRect(rect);
		}
	}

	void PrintText(const std::string& text, const ci::ColorA& color,
		float font_size, const ci::Vec2i& size, const ci::Vec2f& loc) {
		ci::gl::color(color);
		auto box = ci::TextBox()
			.alignment(ci::TextBox::CENTER)
			.font(ci::Font("Roboto", font_size))
			.size(size)
			.color(color)
			.backgroundColor(ci::ColorA(0, 0, 0, 0))
			.text(text);

		const auto box_size = box.getSize();
		const ci::Vec2f location(loc.x - box_size.x / 2, loc.y - box_size.y / 2);
		auto texture = ci::gl::Texture(box.render());
		ci::gl::draw(texture, location);
	}

}  // namespace visualizer

   // Start application
CINDER_APP_BASIC(visualizer::MusicVisualizerApp, RendererGl)