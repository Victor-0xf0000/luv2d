#include <uiSystem.hpp>

UiSystem::UiSystem(luv::Ref<luv::Font> font)
{
  this->renderCount = 0;
  
  this->uiInteracted = false;

  this->currFont = font;
  this->currColor = luv::Color(130, 130, 130, 200);
  this->currColorText = luv::Color(190, 190, 190, 255);

  this->onMenu = false;
}

UiSystem::~UiSystem()
{
}
 
void UiSystem::inputUpdate(luv::Event e)
{
  this->ev = e;
}

bool UiSystem::interacted() const
{
  return this->uiInteracted;
}

void UiSystem::render(luv::Renderer* renderer)
{
  renderer->setRenderViewMode(luv::RenderViewMode::RVM_SCREENVIEW);
  for (int i = 0; i < this->renderCount; i++)
  {
    UiRenderCall call = this->renderqueue[i];
    
    if (call.text)
    {
      if (!call.norect)
      {
        renderer->render_quad_text(
            this->currFont.get(),
            call.rect,
            this->currColor,
            (const char*) call.text,
            this->currColorText
            );
      }
      else
      {
        renderer->render_text(
            this->currFont.get(),
            call.rect.pos,
            (const char*) call.text
        );
      }
    }
    else
    {
      renderer->render_quad(
        call.rect,
        luv::Color(40, 40, 40, 255)
      );
    }
  }
  this->renderCount = 0;
  this->renderqueue.clear();
  renderer->setRenderViewMode(luv::RenderViewMode::RVM_CAMERAVIEW);
  this->uiInteracted = false;
}

void UiSystem::beginMenu(int x, int y, int width, int height)
{
  this->onMenu = true;
  this->menuX = x;
  this->menuY = y;
  this->menuWidth = width;
  this->menuHeight = height;

  this->renderCount++;
  this->renderqueue.push_back({
    static_cast<float>(x),
    static_cast<float>(y),
    width,
    height,
    false,
    nullptr
  });
}
bool UiSystem::uiButton(int x, int y, int width, int height, const char* text)
{
  this->renderCount++;
  int nx, ny;

  if (!this->onMenu)
  {
    nx = x, ny = y;
  }
  else
  {
    nx = this->menuX + x;
    ny = this->menuY + y;
  }

  this->renderqueue.push_back({{
      static_cast<float>(nx),
      static_cast<float>(ny),
      width,
      height
      }, false, (char*) text
      });
  
  int mx = this->ev.mouseEvent.mouse_x, my = this->ev.mouseEvent.mouse_y;
  
  if (this->ev.mouseEvent.get_button(luv::MouseButton::BUTTON_LEFT) ==
      luv::MouseButtonState::MOUSE_BUTTON_RELEASED &&
      mx > nx && mx < nx + width && my > ny && my < ny + height)
  {
    this->uiInteracted = true;
    return true;
  }

  return false;
} 

bool UiSystem::uiText(int x, int y, const char* text)
{
  int nx, ny;
  if (!this->onMenu)
    nx = x, ny = y;
  else
  {
    nx = this->menuX + x;
    ny = this->menuY + y;
  }
  
  this->renderCount++;
  this->renderqueue.push_back({{
    static_cast<float>(nx),
    static_cast<float>(ny),
    this->menuWidth,
    this->menuHeight
    }, true, (char*) text
  });
  return false;
}

void UiSystem::endMenu()
{
  this->onMenu = false;
}
