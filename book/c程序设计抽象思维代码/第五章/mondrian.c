/*
 * File: mondrian.c
 * ----------------
 * This program creates a random line drawing in a style reminiscent
 * of the Dutch painter Piet Mondrian.  The picture is generated by
 * recursively subdividing the canvas into successively smaller
 * rectangles with randomly chosen horizontal and vertical lines.
 */

#include <stdio.h>
#include "genlib.h"
#include "random.h"
#include "graphics.h"

/*
 * Constants
 * ---------
 * MinArea -- Smallest square that will be split
 * MinEdge -- Minimum fraction on each side of dividing line
 */

#define MinArea  0.5
#define MinEdge  0.15

/* Private function prototypes */

static void SubdivideCanvas(double x, double y,
                            double width, double height);

/* Main program */

main()
{
    InitGraphics();
    Randomize();
    SubdivideCanvas(0, 0, GetWindowWidth(), GetWindowHeight());
}

/*
 * Function: SubdivideCanvas
 * Usage: SubdivideCanvas(x, y, width, height);
 * --------------------------------------------
 * This function decomposes a canvas by recursive subdivision.  The
 * lower left corner of the canvas is the point (x, y), and the
 * dimensions are given by the width and height parameters.  The
 * function first checks for the simple case, which is obtained
 * when the size of the rectangular canvas is too small to subdivide
 * (area < MinArea).  In the simple case, the function does nothing.
 * If the area is larger than the minimum, the function first
 * decides whether to split the canvas horizontally or vertically,
 * choosing the larger dimension.  The function then chooses a
 * random dividing line, making sure to leave at least MinEdge on
 * each side.  The program then uses a divide-and-conquer strategy
 * to subdivide the two new rectangles.
 */

static void SubdivideCanvas(double x, double y,
                            double width, double height)
{
    double divider;

    if (width * height >= MinArea) {
        if (width > height) {
            divider = width * RandomReal(MinEdge, 1 - MinEdge);
            MovePen(x + divider, y);
            DrawLine(0, height);
            SubdivideCanvas(x, y, divider, height);
            SubdivideCanvas(x + divider, y, width - divider, height);
        } else {
            divider = height * RandomReal(MinEdge, 1 - MinEdge);
            MovePen(x, y + divider);
            DrawLine(width, 0);
            SubdivideCanvas(x, y, width, divider);
            SubdivideCanvas(x, y + divider, width, height - divider);
        }
    }
}

