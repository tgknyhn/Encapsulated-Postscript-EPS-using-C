#ifndef EPS_GRAPH_H
#define EPS_GRAPH_H

struct Point2D
{
	int    blank;
	double x, y;
	struct Point2D *next;
};
typedef struct Point2D Point2D;

struct Color
{
	double red, blue, green;
};
typedef struct Color Color;

struct Figure
{
	double lx, rx, uy, dy;
	double width, height;
	double resolution;
	double thickness;

	Color color;
	Point2D point;
	Point2D center;
};
typedef struct Figure Figure;

Figure* start_figure             (double width, double height);
void    append_figures           (Figure *fig1, Figure *fig2);
void    set_thickness_resolution (Figure *fig, double thickness, double resolution);
void    set_color                (Figure *fig, Color c);
void    insert_node              (Point2D *head, double x, double y, int blank);
void    draw_fx                  (Figure *fig, double f(double x), double start_x, double end_x, double step_size);
void    draw_polyline            (Figure *fig, Point2D *poly_line, int n);
void    draw_polygon             (Figure *fig, Point2D *poly_line, int n);
void    draw_ellipse             (Figure *fig, Point2D * center, Point2D * width_height);
void    scale_figure             (Figure *fig, double scale_x, double scale_y);
void    resize_figure            (Figure *fig, Point2D *start_roi, Point2D *end_roi);
void    append_figures           (Figure *fig1, Figure *fig2);
void    export_eps               (Figure *fig, char *file_name, int border, int restrict_area);

#endif