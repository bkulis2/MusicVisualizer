// Copyright (c) 2020 Benjamin Kulis. All rights reserved.

#include "my_app.h"

#include <choreograph/Choreograph.h>
#include <cinder/Rand.h>

#include <memory>
#include <string>

namespace myapp {

using cinder::Color;
using cinder::ColorA;
using cinder::Rectf;
using cinder::TextBox;
using cinder::app::KeyEvent;

MyApp::MyApp() {}

void MyApp::setup() {
  cinder::gl::enableDepthWrite();
  Rectf rect(100.0f, 400.0f, 650.0f, 450.0f);
  text_box_ = std::make_shared<InteractiveTextBox>(rect);
  go_to_visualizer_ = false;
  cinder::audio::SourceFileRef sourceFile =
      cinder::audio::load(cinder::app::loadAsset("lofi.mp3"));
  song_voice_ = cinder::audio::Voice::create(sourceFile);
}

void MyApp::update() {}

void MyApp::draw() {
  if (!go_to_visualizer_) {
    cinder::gl::enableAlphaBlending();
    cinder::gl::clear(Color(0, 0, 0));
    text_box_->draw();
    PrintTitle();
    PrintChoose();
    DrawPlayButton();
    DisplayPicture();
  } else {
    cinder::gl::clear(Color(1, 0, 0));
    song_voice_->start();
  }
}

void MyApp::PrintTitle() const {
  cinder::gl::color(cinder::Rand::randFloat(), cinder::Rand::randFloat(),
                    cinder::Rand::randFloat());
  cinder::gl::drawStrokedRect(Rectf(getWindowWidth() / 2 - 200.0f, 50,
                                    getWindowWidth() / 2 + 200.0f, 250));
  PrintText("Music\nVisualizer", Color::white(), 80, cinder::ivec2{500, 150},
            cinder::vec2{getWindowWidth() / 2, 150});
}

void MyApp::PrintChoose() const {
  cinder::gl::color(0, 0, 0);
  float font_size = 40;
  PrintText("Choose Your Song: ", Color::white(), font_size,
            cinder::ivec2{1000, 150},
            cinder::vec2{170, getWindowHeight() / 2 - 50});
  PrintText("Choose Your Pattern: ", Color::white(), font_size,
            cinder::ivec2{1000, 150},
            cinder::vec2{180, getWindowHeight() / 2 + 150});
}

void MyApp::DrawPlayButton() const {
  cinder::gl::color(0, 1, 0);
  Rectf rect(650.0f, 700.0f, 770.0f, 750.0f);
  cinder::gl::drawSolidRect(rect);
  PrintText("Play Pattern", Color::white(), 20, cinder::ivec2{100, 150},
            cinder::vec2{710, 725});
}

void MyApp::DisplayPicture() {
  cinder::gl::Texture2dRef texture =
      cinder::gl::Texture2d::create(loadImage(loadAsset("spiral.jpg")));
  const cinder::vec2 locp = {100, 600};
  cinder::gl::draw(texture, locp);
}

void MyApp::keyDown(KeyEvent event) { text_box_->keyDown(event); }

void MyApp::mouseDown(cinder::app::MouseEvent event) {
  if (event.isLeft() && (event.getX() >= 650 && event.getX() <= 770) &&
      (event.getY() >= 700 && event.getY() <= 750)) {
    go_to_visualizer_ = true;
  }
  //  if (event.isLeft()) {
  //    cinder::gl::color(cinder::Color::white());
  //    cinder::gl::drawStrokedRect()
  //  }
  text_box_->mouseDown(event);
}

void MyApp::mouseUp(cinder::app::MouseEvent event) {
  text_box_->mouseUp(event);
}

void MyApp::mouseDrag(cinder::app::MouseEvent event) {
  text_box_->mouseDrag(event);
}

void MyApp::mouseMove(cinder::app::MouseEvent event) {
  text_box_->mouseMove(event);
}

template <typename C>
void PrintText(const std::string& text, const C& color, float font_size,
               const cinder::ivec2& size, const cinder::vec2& loc) {
  cinder::gl::color(color);

  auto box = TextBox()
                 .alignment(TextBox::CENTER)
                 .font(cinder::Font("Arial", font_size))
                 .size(size)
                 .color(color)
                 .backgroundColor(ColorA(0, 0, 0, 0))
                 .text(text);

  const auto box_size = box.getSize();
  const cinder::vec2 locp = {loc.x - box_size.x / 2, loc.y - box_size.y / 2};
  const auto surface = box.render();
  const auto texture = cinder::gl::Texture::create(surface);
  cinder::gl::draw(texture, locp);
}
}  // namespace myapp
