#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "eps_graph.h"

int main()
{
	Color red   = {60, 0, 0};
	Color green = {0, 60, 0};
	Color blue  = {0, 0, 60};
	Color black = {0, 0, 0};

	//F(x)
	Figure *fig_fx = start_figure(200, 100);
	set_thickness_resolution(fig_fx, 0.5, 5);
	set_color(fig_fx, blue);
	draw_fx(fig_fx, sin, -200.0, 200.0, 0);	
	export_eps(fig_fx, "graph_f(x).eps", 1, 1);

	//Scaled F(x)
	Figure *fig_fx_scaled = start_figure(200, 100);
	set_thickness_resolution(fig_fx_scaled, 0.5, 5);
	set_color(fig_fx_scaled, green);
	draw_fx(fig_fx_scaled, sin, -200.0, 200.0, 0);	
	scale_figure(fig_fx_scaled, 5.0, 5.0);
	export_eps(fig_fx_scaled, "graph_f(x)_scaled.eps", 1, 1);

	//Resized F(x)
	Figure *fig_fx_resized = start_figure(200, 100);
	set_thickness_resolution(fig_fx_resized, 0.5, 5);
	set_color(fig_fx_resized, blue);
	draw_fx(fig_fx_resized, sin, -200.0, 200.0, 0);	
	Point2D *resize = (Point2D*)calloc(2, sizeof(Point2D));
	resize[0].x = 500;
	resize[0].y = 400;
	resize[1].x = 600;
	resize[1].y = 600;
	resize_figure(fig_fx_resized, &resize[0], &resize[1]);
	export_eps(fig_fx_resized, "graph_f(x)_resized.eps", 1, 1);

	//Polyline	
	Figure *fig_polyline = start_figure(200, 100);
	set_thickness_resolution(fig_polyline, 5, 1);
	set_color(fig_polyline, red);
	int n = 20;
	Point2D *poly_line = (Point2D*)calloc(n, sizeof(Point2D));
	for(int i=1; i<n; i++)
	{
		if(i%2 == 0)
		{
			poly_line[i].x     = i*9 + poly_line[i-1].x;
			poly_line[i].y     = i*i*9 + poly_line[i-1].y;
			poly_line[i].blank = 0; 
		}
		if(i%2 == 1)
		{
			poly_line[i].x     = i*9 + poly_line[i-1].x;
			poly_line[i].y     = -i*i*9 + poly_line[i-1].y;
			poly_line[i].blank = 0; 
		}
	}
	draw_polyline(fig_polyline, poly_line, n);
	export_eps(fig_polyline, "graph_polyline.eps", 0, 0);


	//Polygone
	Figure *fig_polygone = start_figure(70, 20);
	set_thickness_resolution(fig_polygone, 0.5, 10);
	set_color(fig_polygone, black);	
	int m = 6;
	Point2D *polygone = (Point2D*)calloc(m+1, sizeof(Point2D));

	polygone[1].y = 120;
	polygone[1].x = 0;

	polygone[2].y = 150;
	polygone[2].x = 100;

	polygone[3].y = 60;
	polygone[3].x = 150;

	polygone[4].y = -30;
	polygone[4].x = 100;

	draw_polygon(fig_polygone, polygone, m);
	export_eps(fig_polygone, "graph_polygone.eps", 0, 0);

	
	//Scaled Polygone
	Figure *fig_polygone_scaled = start_figure(70, 20);
	set_thickness_resolution(fig_polygone_scaled, 0.5, 10);
	set_color(fig_polygone_scaled, black);	
	Point2D *polygone_sc = (Point2D*)calloc(m+1, sizeof(Point2D));

	polygone_sc[1].y = 120;
	polygone_sc[1].x = 0;

	polygone_sc[2].y = 150;
	polygone_sc[2].x = 100;

	polygone_sc[3].y = 60;
	polygone_sc[3].x = 150;

	polygone_sc[4].y = -30;
	polygone_sc[4].x = 100;

	draw_polygon(fig_polygone_scaled, polygone_sc, m);
	scale_figure(fig_polygone_scaled, 3.0, 3.0);
	export_eps(fig_polygone_scaled, "graph_polygone_scaled.eps", 0, 0);


	//appended polygones
	append_figures(fig_polygone_scaled, fig_polygone);
	export_eps(fig_polygone_scaled, "graph_appended.eps", 0, 0);



	//ellipse
	Figure *fig_ellipse = start_figure(70, 20);

	set_thickness_resolution(fig_ellipse, 1.5, 10);
	set_color(fig_ellipse, blue);

	Point2D* center = (Point2D*)malloc(sizeof(Point2D));
	Point2D* width_height = (Point2D*)malloc(sizeof(Point2D));
	
	(*center).x = 62.0; 
	(*center).y = 100.0;
	(*width_height).x = 0.8; 
	(*width_height).y = 0.5; 
	draw_ellipse(fig_ellipse, center, width_height);
	export_eps(fig_ellipse, "graph_ellipse.eps", 0, 0);

	//tree


	return 0;
}