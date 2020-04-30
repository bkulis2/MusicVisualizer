// Copyright (c) 2020 Benjamin Kulis. All rights reserved.

#include "music_visualizer.h"

#include <cinder/Rand.h>
#include <cinder/Text.h>
#include <cinder/gl/draw.h>
#include <cinder/gl/scoped.h>
#include <gflags/gflags.h>

namespace visualizer {

using ci::Color;
using ci::ColorA;
using ci::Rectf;
using ci::app::KeyEvent;

DECLARE_string(song);

MyApp::MyApp() : song_{FLAGS_song} {}

void MyApp::setup() {
  on_visualizer_screen_ = false;
  selected_spiral_pattern_ = false;
  selected_frequency_pattern_ = false;
  cinder::audio::SourceFileRef sourceFile =
      cinder::audio::load(cinder::app::loadAsset(song_));
  song_voice_ = cinder::audio::Voice::create(sourceFile);
}

void MyApp::update() {}

void MyApp::draw() {
  ci::gl::enableAlphaBlending();
  if (!on_visualizer_screen_) {
    ci::gl::clear(Color(0.5, 0, 0.5));
    PrintTitle();
    PrintChoose();
    DrawPlayButton();
    DisplayPictures();
    DrawSelectionRect();
  } else {
    ci::gl::clear(Color(0, 0, 0));
    song_voice_->start();
  }
}

void MyApp::PrintTitle() const {
  ci::gl::color(ci::Rand::randFloat(), ci::Rand::randFloat(),
                ci::Rand::randFloat());
  ci::gl::drawStrokedRect(Rectf(getWindowWidth() / 2 - 170.0f, 70,
                                getWindowWidth() / 2 + 170.0f, 230));
  PrintText("Music\nVisualizer", Color::black(), 80, ci::ivec2{500, 150},
            ci::vec2{getWindowWidth() / 2, 150});
}

void MyApp::PrintChoose() const {
  ci::gl::color(0, 0, 0);
  float font_size = 40;
  PrintText("Song File You Chose:", Color::white(), font_size,
            ci::ivec2{1000, 150}, ci::vec2{170, getWindowHeight() / 2 - 50});
  PrintText(song_, Color(1, 0, 0), font_size, ci::ivec2{1000, 150},
            ci::vec2{getWindowWidth() / 2 + 25, getWindowHeight() / 2 - 50});
  PrintText("Choose Your Pattern: ", Color::white(), font_size,
            ci::ivec2{1000, 150}, ci::vec2{170, getWindowHeight() / 2 +50});
}

void MyApp::DrawPlayButton() const {
  ci::gl::color(0.0f, 0.0f, 0.7f);
  ci::gl::lineWidth(3);
  Rectf rect(650.0f, 700.0f, 770.0f, 750.0f);
  ci::gl::drawSolidRect(rect);
  PrintText("Play Pattern", Color::white(), 20, ci::ivec2{70, 50},
            ci::vec2{710, 725});
}

void MyApp::DisplayPictures() {
  ci::gl::Texture2dRef texture_one =
      ci::gl::Texture2d::create(loadImage(loadAsset("spiral.png")));
  const ci::vec2 loc1 = {100, 500};
  ci::gl::draw(texture_one, loc1);

  ci::gl::Texture2dRef texture_two =
      ci::gl::Texture2d::create(loadImage(loadAsset("frequency.png")));
  const ci::vec2 loc2 = {400, 500};
  ci::gl::draw(texture_two, loc2);
}

void MyApp::DrawSelectionRect() {
  if (selected_spiral_pattern_) {
    cinder::gl::color(cinder::Color::white());
    Rectf rect(90.0f, 490.0f, 310.0f, 710.0f);
    cinder::gl::drawStrokedRect(rect);
  } else if (selected_frequency_pattern_) {
    cinder::gl::color(cinder::Color::white());
    Rectf rect(390.0f, 490.0f, 610.0f, 710.0f);
    cinder::gl::drawStrokedRect(rect);
  }
}

void MyApp::keyDown(KeyEvent event) {
  auto current_volume = song_voice_->getVolume();
  switch (event.getCode()) {
    case KeyEvent::KEY_UP:
      if (current_volume < 1.0f) {
        song_voice_->setVolume(current_volume + .01f);
      }
    case KeyEvent::KEY_DOWN:
      if (current_volume > 0) {
        song_voice_->setVolume(current_volume - .01f);
      }
  }
}

void MyApp::mouseDown(ci::app::MouseEvent event) {
  if (event.isLeft() && (event.getX() >= 650 && event.getX() <= 770) &&
      (event.getY() >= 700 && event.getY() <= 750)) {
    on_visualizer_screen_ = true;
  } else if (event.isLeft() && (event.getX() >= 100 && event.getX() <= 300) &&
             (event.getY() >= 500 && event.getY() <= 700)) {
    selected_spiral_pattern_ = true;
    selected_frequency_pattern_ = false;
  } else if (event.isLeft() && (event.getX() >= 400 && event.getX() <= 600) &&
           (event.getY() >= 500 && event.getY() <= 700)) {
    selected_spiral_pattern_ = false;
    selected_frequency_pattern_ = true;
  }
}

void MyApp::mouseUp(ci::app::MouseEvent event) {}

void MyApp::mouseDrag(ci::app::MouseEvent event) {}

void MyApp::mouseMove(ci::app::MouseEvent event) {}

template <typename C>
void PrintText(const std::string& text, const C& color, float font_size,
               const ci::ivec2& size, const ci::vec2& loc) {
  ci::gl::color(color);

  auto box = ci::TextBox()
                 .alignment(ci::TextBox::CENTER)
                 .font(ci::Font("Roboto", font_size))
                 .size(size)
                 .color(color)
                 .backgroundColor(ColorA(0, 0, 0, 0))
                 .text(text);

  const auto box_size = box.getSize();
  const ci::vec2 locp = {loc.x - box_size.x / 2, loc.y - box_size.y / 2};
  const auto surface = box.render();
  const auto texture = ci::gl::Texture::create(surface);
  ci::gl::draw(texture, locp);
}

}  // namespace visualizer
