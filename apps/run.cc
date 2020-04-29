// Copyright (c) 2020 [Benjamin Kulis]. All rights reserved.

#include <string>
#include <vector>

#include <cinder/app/App.h>
#include <cinder/app/RendererGl.h>
#include <gflags/gflags.h>

#include "music_visualizer.h"

using cinder::app::App;
using cinder::app::RendererGl;

using std::vector;
using std::string;

namespace visualizer {

DEFINE_string(song, "lofi.mp3", "the name of the audio file for the visualizer");

const int kSamples = 8;
const int kWidth = 800;
const int kHeight = 800;

void ParseArgs(vector<string>* args) {
  gflags::SetUsageMessage(
      "View a music visualizer. Pass --helpshort for options.");
  int argc = static_cast<int>(args->size());

  vector<char*> argvs;
  for (string& str : *args) {
    argvs.push_back(&str[0]);
  }

  char** argv = argvs.data();
  gflags::ParseCommandLineFlags(&argc, &argv, true);
}

void SetUp(App::Settings* settings) {
  vector<string> args = settings->getCommandLineArgs();
  ParseArgs(&args);

  settings->setWindowSize(kWidth, kHeight);
  settings->setTitle("Music Visualizer");
}

}  // namespace visualizer


// This is a macro that runs the application.
CINDER_APP(visualizer::MyApp,
           RendererGl(RendererGl::Options().msaa(visualizer::kSamples)),
           visualizer::SetUp)
