#include <c++/cstdint>
#include <graphx.h>
#include <keypadc.h>
#include <sys/timers.h>
#include <sys/util.h>

#define TILE_WIDTH 10
#define TILE_HEIGHT 10

#define BG_COLOR 0xFF

void gfxa_createText(const char *string, uint8_t color, int x, int y);
void gfxa_createText_Int(const char *string, uint8_t color, int x, int y, int addonInt, uint8_t addonColor, uint8_t length = 2);
void gfxa_createFillRectangle(int x, int y, int width, int height, uint8_t color);
void gfxa_createFillCircle(int x, int y, int radius, uint8_t color);
void setLayer(int layerX, uint8_t color);

struct DynamicObject_t
{
  int x;
  int y;
  int oldX;
  int oldY;
  uint8_t color;
  void Draw(void)
  {
    gfxa_createFillRectangle((oldX - 1) * TILE_WIDTH, (oldY - 1) * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT, BG_COLOR);
    gfxa_createFillRectangle((x - 1) * TILE_WIDTH, (y - 1) * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT, color);
    oldX = x;
    oldY = y;
  }
  void Init(int initX, int initY, uint8_t initColor)
  {
    x = initX;
    oldX = initX;
    y = initY;
    oldY = initY;
    color = initColor;
  }
};

int main(void)
{
  /* Key variable */
  kb_key_t key;

  DynamicObject_t Player;
  Player.Init(1, 1, 0x00);

  bool redraw = true;

  gfx_Begin();
  gfx_SetDrawBuffer();
  gfx_BlitScreen();
  gfx_FillScreen(BG_COLOR);

  Player.Draw();

  /* Loop until 2nd is pressed */
  do
  {
    gfx_BlitScreen();

    /* Update kb_Data */
    kb_Scan();

    key = kb_Data[7];

    switch (key)
    {
    case kb_Up:
      Player.y--;
      redraw = true;
      break;

    case kb_Left:
      Player.x--;
      redraw = true;
      break;

    case kb_Down:
      Player.y++;
      redraw = true;
      break;

    case kb_Right:
      Player.x++;
      redraw = true;
      break;

    default:
      break;
    }

    if (redraw)
    {
      Player.Draw();
      redraw = false;
    }
    setLayer(4, 0xAF);

    gfx_SwapDraw();
    msleep(50);
  } while (kb_Data[1] != kb_2nd);

  gfx_End();
  return 0;
}

/* Print colored text to the screen */
void gfxa_createText(const char *string, uint8_t color, int x, int y)
{
  gfx_SetTextFGColor(color);
  gfx_SetTextXY(x, y);
  gfx_PrintString(string);
}

/* Print colored text to the screen followed by a colored integer */
void gfxa_createText_Int(const char *string, uint8_t color, int x, int y, int addonInt, uint8_t addonColor, uint8_t length)
{
  gfx_SetTextFGColor(color);
  gfx_SetTextXY(x, y);
  gfx_PrintString(string);
  gfx_SetTextXY(gfx_GetStringWidth(string) + x - 1, y);
  gfx_SetTextFGColor(addonColor);
  gfx_PrintInt(addonInt, length);
}

/* Print a full colored rectangle to the screen */
void gfxa_createFillRectangle(int x, int y, int width, int height, uint8_t color)
{
  gfx_SetColor(color);
  gfx_FillRectangle(x, y, width, height);
}

/* Print a full colored circle to the screen */
void gfxa_createFillCircle(int x, int y, int radius, uint8_t color)
{
  gfx_SetColor(color);
  gfx_FillCircle(x, y, radius);
}

void setLayer(int layerX, uint8_t color)
{
  for (int i = 0; i <= GFX_LCD_HEIGHT / TILE_HEIGHT; i++)
  {
    gfxa_createFillRectangle(layerX * TILE_WIDTH, i * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT, color);
  }
}

uint32_t srandomInt(int min, int max, int seed)
{
  srandom(seed);

  return (random() % ((max) - (min) + 1) + (min));
}