// Copyright 2017 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_PUBLIC_BROWSER_OVERLAY_WINDOW_H_
#define CONTENT_PUBLIC_BROWSER_OVERLAY_WINDOW_H_

#include <memory>

#include "ui/gfx/native_widget_types.h"

namespace gfx {
class Rect;
class Size;
}

namespace ui {
class Layer;
}

namespace content {

class PictureInPictureWindowController;

// This window will always float above other windows. The intention is to show
// content perpetually while the user is still interacting with the other
// browser windows.
class OverlayWindow {
 public:
  OverlayWindow() = default;
  virtual ~OverlayWindow() = default;

  // Returns a created OverlayWindow. This is defined in the platform-specific
  // implementation for the class.
  static std::unique_ptr<OverlayWindow> Create(
      PictureInPictureWindowController* controller);

  virtual bool IsActive() const = 0;
  virtual void Close() = 0;
  virtual void Show() = 0;
  virtual void Hide() = 0;
  virtual bool IsVisible() const = 0;
  virtual bool IsAlwaysOnTop() const = 0;
  virtual ui::Layer* GetLayer() = 0;
  // Retrieves the window's current bounds, including its window.
  virtual gfx::Rect GetBounds() const = 0;
  virtual void UpdateVideoSize(const gfx::Size& natural_size) = 0;
  virtual void UpdatePlayPauseControlsIcon(bool is_playing) = 0;

  // Retrieve the ui::Layers corresponding to the video and controls.
  virtual ui::Layer* GetVideoLayer() = 0;
  virtual ui::Layer* GetControlsBackgroundLayer() = 0;
  virtual ui::Layer* GetCloseControlsLayer() = 0;
  virtual ui::Layer* GetPlayPauseControlsLayer() = 0;

  // Retrieves the bounds of the video and media controls.
  virtual gfx::Rect GetVideoBounds() = 0;
  virtual gfx::Rect GetCloseControlsBounds() = 0;
  virtual gfx::Rect GetPlayPauseControlsBounds() = 0;

 private:
  DISALLOW_COPY_AND_ASSIGN(OverlayWindow);
};

}  // namespace content

#endif  // CONTENT_PUBLIC_BROWSER_OVERLAY_WINDOW_H_
