// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <InteractiveObject.h>
#include <InteractiveTextBox.h>
#include <cinder/app/App.h>

namespace myapp {

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
  std::shared_ptr<InteractiveTextBox> text_box;
};

template <typename C>
void PrintText(const std::string& text, const C& color, float font_size,
               const cinder::ivec2& size, const cinder::vec2& loc);
}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
