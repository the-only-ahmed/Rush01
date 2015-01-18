#ifndef GRAPH_HPP
# define GRAPH_HPP

#include <gtk/gtk.h>
#include <math.h>
#include <cairo.h>
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <vector>

#define WIDTH   640
#define HEIGHT  480

#define ZOOM_X  100.0
#define ZOOM_Y  100.0

class Graph {

private:
	std::vector<gdouble>	pt;
	gfloat	fPer(gfloat a, gfloat x, gfloat b);
	gdouble dx, dy, clip_x1, clip_x2, clip_y1, clip_y2;

	void	draw_graph(cairo_t *cr);
	void	Draw_repere(cairo_t *cr);
	void	Init();
	void	aff(gdouble a, gdouble b, cairo_t *cr, gdouble xxx);

public:
	Graph();
	gboolean	on_expose_event(GtkWidget *widget, GdkEventExpose *event);
	void		setPoint(gdouble p);
	int			getSize();
};


#endif
