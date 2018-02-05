#include "gfx.h"
#include "math.h"
#include "ssd1331.h"

#define abs(x) (((x)<0)?((-1)*(x)):(x))
#define sign(x) (((x)>=0)?1:-1)

// algorithm taken from
// https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
void GFX_drawLine(int x0, int y0, int x1, int y1, unsigned short color)
{

      double deltax = x1 - x0;
      double deltay = y1 - y0;
      double deltaerr = abs(deltay / deltax);    // Assume deltax != 0 (line is not vertical),
            // note that this division needs to be done in a way that preserves the fractional part
      double error = 0.0; // No error at start
      int y = y0;
      for (int x = x0; x < x1; x++)
      {
          SSD1331_draw_point(x, y, color);
          error = error + deltaerr;
          while (error >= 0.5)
          {
              y = y + sign(deltay) * 1;
              
              error = error - 1.0;
          }
      }
}
