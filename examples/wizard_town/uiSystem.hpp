#pragma once

#include <luv2d.hpp>

struct UiRenderCall
{
  luv::Rect rect;
  bool norect;
  char* text;
};

struct UiSystem
{
private:
  std::vector<UiRenderCall> renderqueue;
  int renderCount;

  luv::Ref<luv::Font> currFont;
  luv::Color currColor;
  luv::Color currColorText;

  luv::Event ev;
  bool uiInteracted;
  
  // Was begin menu called?
  bool onMenu;
  int menuX, menuY, menuWidth, menuHeight;
public:
  UiSystem(luv::Ref<luv::Font> font);
  ~UiSystem();
  
  bool interacted() const;

  void inputUpdate(luv::Event e);
  void render(luv::Renderer* renderer);
  
  void beginMenu(int x, int y, int width, int height);
  bool uiButton(int x, int y, int width, int height, const char* text);
  bool uiText(int x, int y, const char* text);
  void endMenu();
};
