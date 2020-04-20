// Copyright (c) 2020 [Benjamin Kulis]. All rights reserved.

#include "my_app.h"

#include <cinder/Font.h>
#include <cinder/Rand.h>
#include <cinder/Text.h>
#include <cinder/app/App.h>
#include <cinder/gl/draw.h>
#include <cinder/gl/gl.h>

#include <string>

namespace myapp {

using cinder::Color;
using cinder::ColorA;
using cinder::Rectf;
using cinder::TextBox;
using cinder::app::KeyEvent;

MyApp::MyApp() {}

void MyApp::setup() { cinder::gl::enableDepthWrite(); }

void MyApp::update() {}

void MyApp::draw() {
  cinder::gl::color(cinder::Rand::randFloat(), cinder::Rand::randFloat(),
                    cinder::Rand::randFloat());
  cinder::gl::drawStrokedRect(Rectf(getWindowWidth() / 2 - 200.0f, 50,
                                    getWindowWidth() / 2 + 200.0f, 250));
  drawTitle();
}

void MyApp::drawTitle() const {
  PrintText("Music\nVisualizer", Color::white(), cinder::ivec2{500, 150},
            cinder::vec2{getWindowWidth() / 2, 150});
}

template <typename C>
void PrintText(const std::string& text, const C& color,
               const cinder::ivec2& size, const cinder::vec2& loc) {
  cinder::gl::color(color);

  auto box = TextBox()
                 .alignment(TextBox::CENTER)
                 .font(cinder::Font("Arial", 80))
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

void MyApp::keyDown(KeyEvent event) {}

}  // namespace myapp