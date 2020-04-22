// Copyright (c) 2020 Benjamin Kulis. All rights reserved.

#ifndef FINALPROJECT_INTERACTIVETEXTBOX_H
#define FINALPROJECT_INTERACTIVETEXTBOX_H

#pragma once
#include <InteractiveObject.h>
#include <cinder/Text.h>
#include <cinder/app/KeyEvent.h>
#include <cinder/gl/Texture.h>

namespace myapp {
class InteractiveTextBox : public InteractiveObject {
 public:
  explicit InteractiveTextBox(const ci::Rectf& rect);
  void draw() override;
  void pressed() override;
  void releasedOutside() override;
  void keyDown(ci::app::KeyEvent& event);

 protected:
  ci::TextBox mTextBox;
  std::string mText;
  bool mActive;
  bool mFirstText;
};

}  // namespace myapp

#endif  // FINALPROJECT_INTERACTIVETEXTBOX_H
