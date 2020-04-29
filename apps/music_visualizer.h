// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>
#include <cinder/audio/audio.h>

#include <choreograph/Choreograph.h>
#include <choreograph/Output.hpp>

namespace visualizer {

class MyApp : public cinder::app::App {
 public:
  MyApp();
  void setup() override;
  void update() override;
  void draw() override;
  void keyDown(cinder::app::KeyEvent) override;
  void mouseDown(cinder::app::MouseEvent event) override;
  void mouseUp(cinder::app::MouseEvent event) override;
  void mouseDrag(cinder::app::MouseEvent event) override;
  void mouseMove(cinder::app::MouseEvent event) override;

 private:
  void PrintTitle() const;
  void PrintChoose() const;
  void DrawPlayButton() const;
  void DisplayPicture();
  cinder::audio::VoiceRef song_voice_;
  bool go_to_visualizer_;
  std::string song_;
  ch::Output<ci::vec2> _position_a;
  ch::Output<ci::vec2> _position_b;
  ch::Output<ci::vec2> _reference_bounce;
  ch::Output<ci::vec2> _reference_slide;
  ci::Timer timer_;
};

template <typename C>
void PrintText(const std::string& text, const C& color, float font_size,
               const cinder::ivec2& size, const cinder::vec2& loc);
}  // namespace visualizer

#endif  // FINALPROJECT_APPS_MYAPP_H_
