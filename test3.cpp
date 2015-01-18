/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test3.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/17 21:18:04 by ael-kadh          #+#    #+#             */
/*   Updated: 2015/01/18 07:47:22 by ael-kadh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Graph.hpp"

Graph::Graph() {}

void	Graph::Draw_repere(cairo_t *cr) {

	gdouble i;

	/* Draws x and y axis */
	cairo_set_source_rgb (cr, 0.0, 1.0, 0.0);
	cairo_move_to (cr, this->clip_x1, 0.0);
	cairo_line_to (cr, this->clip_x2, 0.0);
	cairo_move_to (cr, 0.0, this->clip_y1);
	cairo_line_to (cr, 0.0, this->clip_y2);
	cairo_stroke (cr);

	/* Link each data point */
//	std::cout << "clip_x2 = " << this->clip_x2 << "	|	dx = " << this->dx << std::endl;
	for (gdouble x = 0; x < this->clip_x2; x += (this->dx * 10))
	{
		if (x == 0)
			continue;
		for (i = 0; i < this->clip_x2; i += this->dx)
			cairo_line_to (cr, fPer(0, i, x), i);
		cairo_set_source_rgba(cr, 0.8, 0.8, 0.8, 0.5);
		cairo_stroke (cr);
	}

	gdouble z = this->clip_y2 / (10 * this->dy);
	for (gdouble y = 0; y < this->clip_y2; y += (this->dy * z))
	{
		if (y == 0)
			continue;
		for (i = 0; i < this->clip_x2; i += this->dx) {
			cairo_line_to (cr, i, fPer(0, i, y));
		}
		cairo_set_source_rgba(cr, 0.8, 0.8, 0.8, 0.5);
		cairo_stroke (cr);
	}

	this->draw_graph(cr);

}

void		Graph::Init() {

	dx = 1.0;
	dy = 1.0;
	clip_x1 = 0.0;
	clip_x2 = 0.0;
	clip_y1 = 0.0;
	clip_y2 = 0.0;
}

gfloat		Graph::fPer(gfloat a, gfloat x, gfloat b) {return ((a*x) + b);}

gboolean		Graph::on_expose_event(GtkWidget *widget, GdkEventExpose *event) {

	this->Init();

	GdkWindow *window = gtk_widget_get_window(widget);
	cairo_t *cr = gdk_cairo_create(window);
	GdkRectangle da;			/* GtkDrawingArea size */

	/* Define a clipping zone to improve performance */
	cairo_rectangle(cr, event->area.x, event->area.y, event->area.width, event->area.height);
	cairo_clip(cr);
	cairo_reset_clip(cr);

		/* Determine GtkDrawingArea dimensions */
	gdk_window_get_geometry(window, &da.x, &da.y, &da.width, &da.height);

		/* Draw on a black background */
	cairo_set_source_rgb (cr, 0.0, 0.0, 0.0);
	cairo_paint (cr);

	/* Change the transformation matrix */
	cairo_translate (cr, 10.0, da.height - 10.0);
	cairo_scale (cr, ZOOM_X, -ZOOM_Y);

			/* Determine the data points to calculate (ie. those in the clipping zone */
	cairo_device_to_user_distance (cr, &(dx), &(dy));
	cairo_clip_extents (cr, &(clip_x1), &(clip_y1), &(clip_x2), &(clip_y2));
	cairo_set_line_width (cr, this->dx);

	this->Draw_repere(cr);

	cairo_destroy (cr);

	return FALSE;
}

void		Graph::aff(gdouble y1, gdouble y2, cairo_t *cr, gdouble x1) {

	gdouble x2 = x1 + (dx * 10);
	gdouble a = (y2 - y1) / (x2 - x1);
	gdouble b = ((x2 * y1) - (x1 * y2)) / (x2 - x1);

	while (x1 < x2)
	{
		gdouble y = fPer(a, x1, b);
		cairo_line_to(cr, x1, y);
		cairo_line_to(cr, x1, 0);
		x1 += 0.001;
	}
}

void	Graph::draw_graph(cairo_t *cr) {

	if (!(pt.size() > 0))
		return;

	if ((((pt.size() - 1) * (dx * 10))) > clip_x2)
	{
		for (unsigned int i = 0; i < pt.size() - 1; i++)
			pt[i] = pt[i + 1];
		pt.pop_back();
	}

	gdouble ds = 0;
	for (unsigned int i = 0; i < pt.size(); i++)
	{
		gdouble z = (clip_y2 * pt[i]) / 100;
		cairo_line_to(cr, ds, z);

		ds += (dx * 10);
	}
	cairo_set_source_rgba(cr, 1.0, 0.0, 0.0, 0.8);
	cairo_stroke (cr);

	ds = 0;
	gdouble z1 = (clip_y2 * pt[0]) / 100;;
	for (unsigned int i = 1; i < pt.size(); i++)
	{
		gdouble z = (clip_y2 * pt[i]) / 100;

		this->aff(z1, z, cr, ds);
		z1 = z;

		cairo_set_source_rgba(cr, 0.0, 1.0, 1.0, 0.8);
		cairo_stroke (cr);

		ds += (dx * 10);
	}

}

void	Graph::setPoint(gdouble p) {this->pt.push_back(p);}
int		Graph::getSize() {return this->pt.size();}
//////

/////
/*
gboolean	Fred_memberFn_wrapper(GtkWidget *widget, GdkEventExpose *event, gpointer user_data) {

	(void)user_data;

	gdouble rd;
	rd = rand() % 100;
	a.setPoint(rd);
	a.on_expose_event(widget, event);

	return FALSE;
}
/
int		main() {

	srand(time(NULL));

	GtkWidget *window;
	GtkWidget *da;

	gtk_init(NULL, NULL);

	gdouble s;
	gdouble b;
	gdouble c;
	gdouble d;
	gdouble e;
	gdouble f;
	gdouble g;
	gdouble h;
	s = 3.0;
	b = 35.0;
	c = 42.0;
	d = 12.0;
	e = 54.0;
	f = 43.0;
	g = 23.0;
	h = 12.0;
	a.setPoint(s);
	a.setPoint(b);
	a.setPoint(c);
	a.setPoint(d);
	a.setPoint(e);
	a.setPoint(f);
	a.setPoint(g);
	a.setPoint(h);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_default_size(GTK_WINDOW (window), WIDTH, HEIGHT);
	gtk_window_set_title (GTK_WINDOW (window), "Graph drawing");

	g_signal_connect(window, "destroy", gtk_main_quit, NULL);

	da = gtk_drawing_area_new();
	gtk_container_add(GTK_CONTAINER (window), da);

	g_signal_connect(da, "draw", G_CALLBACK(Fred_memberFn_wrapper), NULL);
	gtk_widget_show_all(window);
	gtk_main();

	return 0;
}
*/
