#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "eps_graph.h"

Figure* start_figure             (double width, double height);
void    append_figures           (Figure *fig1, Figure *fig2);
void    set_thickness_resolution (Figure *fig, double thickness, double resolution);
void    set_color                (Figure *fig, Color c);
void    insert_node              (Point2D *head, double x, double y, int blank);
void    draw_fx                  (Figure *fig, double f(double x), double start_x, double end_x, double step_size);
void    draw_polyline            (Figure *fig, Point2D *poly_line, int n);
void    draw_polygon             (Figure *fig, Point2D *poly_line, int n);
void    draw_ellipse             (Figure *fig, Point2D *center, Point2D *width_height);
void    scale_figure             (Figure *fig, double scale_x, double scale_y);
void    resize_figure            (Figure *fig, Point2D *start_roi, Point2D *end_roi);
void    append_figures           (Figure *fig1, Figure *fig2);
void    export_eps               (Figure *fig, char *file_name, int border, int restrict_area);

Figure* start_figure(double width, double height)
{
	Figure* fig = (Figure*)malloc(sizeof(Figure));

	(*fig).width  = width;
	(*fig).height = height;
}

void set_thickness_resolution(Figure *fig, double thickness, double resolution)
{
	(*fig).thickness  = thickness;
	(*fig).resolution = resolution;
}

void set_color(Figure *fig, Color c)
{
	(*fig).color.red   = c.red;
	(*fig).color.blue  = c.blue;
	(*fig).color.green = c.green;
}

void insert_node(Point2D *head, double x, double y, int blank)
{
	Point2D *new = (Point2D*)calloc(1, sizeof(Point2D));
	Point2D *temp;

	if(head == NULL)
		return;

	(*new).x     = x;
	(*new).y     = y;
	(*new).blank = blank;
	(*new).next  = NULL;

	temp = head;

	while((*temp).next != NULL)
		temp = (*temp).next;

	(*temp).next = new;
}

void draw_fx(Figure *fig, double f(double x), double start_x, double end_x, double step_size)
{
	Point2D* head = (Point2D*)malloc(sizeof(Point2D));
	(*head).next = NULL;

	(*head).blank = 0;
	(*head).x     = start_x;
	(*head).y     = f(start_x);

	double res = (1/(*fig).resolution);

	for(double x = start_x/res; x<= end_x; x = x+res)
		insert_node(head, f(x)*10, x, 0);

	(*fig).point = *head;
}

void draw_polyline(Figure *fig, Point2D *poly_line, int n)
{
	Point2D *head = (Point2D*)malloc(sizeof(Point2D));
	Point2D *temp = (Point2D*)malloc(sizeof(Point2D));
	(*head).next = NULL;

	temp = head;
	for(int i=0; i<n; i++)
	{
		(*temp).next = &poly_line[i];
	
		while((*temp).next != NULL)
			temp = (*temp).next;
	
	}

	(*fig).point = *head; 
}

void draw_polygon(Figure *fig, Point2D *poly_line, int n)
{

	Point2D *head = (Point2D*)malloc(sizeof(Point2D));
	Point2D *temp = (Point2D*)malloc(sizeof(Point2D));
	(*head).next = NULL;

	temp = head;
	for(int i=0; i<=n; i++)
	{
		while((*temp).next != NULL)
		{
			temp = (*temp).next;
		}
	
		(*temp).next = &poly_line[i];
	}

	(*fig).point = *head;
}

int ellipse = 0;
void draw_ellipse(Figure *fig, Point2D *center, Point2D *width_height)
{
	ellipse = 1;
	(*fig).center.x = (*center).x;
	(*fig).center.y = (*center).y;
	(*fig).width  = (*width_height).x;
	(*fig).height = (*width_height).y;
}

void scale_figure(Figure *fig, double scale_x, double scale_y)
{
	Point2D *temp = &(*fig).point;

	double max_x = (*temp).x;
	double max_y = (*temp).y;
	double min_x = (*temp).x;
	double min_y = (*temp).y;

	while(temp != NULL)
	{
		if((*temp).x > max_x)	
			max_x = (*temp).x;

		if((*temp).y > max_y)	
			max_y = (*temp).y;
		
		if((*temp).x < min_x)	
			min_x = (*temp).x;
		
		if((*temp).y < min_y)	
			min_y = (*temp).y;

		temp = (*temp).next;
	}


	temp = &(*fig).point;
	while(temp != NULL)
	{
		(*temp).x = (((*temp).x)*scale_x);
		(*temp).y = (((*temp).y)*scale_y);

		temp = (*temp).next;
	}
}

int resize = 0;
void resize_figure(Figure *fig, Point2D *start_roi, Point2D *end_roi)
{
	(*fig).lx = (*start_roi).x;
	(*fig).dy = (*start_roi).y;
	(*fig).uy = (*end_roi).y;
	(*fig).rx = (*end_roi).x;

	resize = 1;
}

void append_figures(Figure *fig1, Figure *fig2)
{
	Point2D *temp = &(*fig1).point;

	insert_node(&(*fig1).point, 0, 0, 1); 

	while((*temp).next != NULL)
	{
		temp = (*temp).next;
	}

	(*temp).next = (*fig2).point.next; 
}

void export_eps(Figure *fig, char *file_name, int border, int restrict_area)
{
	FILE *fp;
	fp = fopen(file_name, "w+");

	int width  = (int)(*fig).width;
	int height = (int)(*fig).height;

	int start_width  = 500-(int)(*fig).width/2.0;
	int start_height = 500-(int)(*fig).height/2.0;

	//done
	if(ellipse == 0)
	{
		fprintf(fp, "%%!PS-Adobe-3.0 EPSF-3.0\n");
		fprintf(fp, "%%%%BoundingBox: 0 0 1000 1000\n");
		if(border == 1)
		{
			fprintf(fp, "0.4 setlinewidth\n");
			if(resize == 1)
			{
				fprintf(fp, "%.1f %.1f moveto\n", (*fig).lx, (*fig).dy);
				fprintf(fp, "%.1f %.1f lineto\n", (*fig).lx, (*fig).uy);
				fprintf(fp, "%.1f %.1f lineto\n", (*fig).rx, (*fig).uy);
				fprintf(fp, "%.1f %.1f lineto\n", (*fig).rx, (*fig).dy);
				start_width = (*fig).lx;
				width = (*fig).rx - (*fig).lx;	
				start_height = (*fig).dy;
				height = (*fig).uy - (*fig).dy;
			}
			else
			{
				fprintf(fp, "%d %d moveto\n", start_width, start_height);
				fprintf(fp, "%d %d lineto\n", start_width, start_height+height);
				fprintf(fp, "%d %d lineto\n", start_width+width, start_height+height);
				fprintf(fp, "%d %d lineto\n", start_width+width, start_height);	
			}
			fprintf(fp, "closepath\n");
			fprintf(fp, "stroke\n");		
		}

		fprintf(fp, "%f %f moveto\n", start_width+(width/2.0), start_height+(height/2.0));
		fprintf(fp, "%.1f setlinewidth\n", (*fig).thickness);
		fprintf(fp, "%.1f %.1f %.1f setrgbcolor\n", (*fig).color.red, (*fig).color.blue, (*fig).color.green);
	}

	if(ellipse == 0)
	{
		Point2D *temp = (*fig).point.next;
		temp = (*temp).next;

		double x; 
		double y;
		while((*temp).next != NULL)
		{
			x = (start_width+(width/2.0)+(*temp).y);
			y = (start_height+(height/2.0)+(*temp).x);

			if(restrict_area == 1)
			{
				if(x < start_width)
				{
					x = start_width;
					(*temp).blank = 1;					
				}
				else if(x > start_width+width)
				{
					x = start_width + width;
					(*temp).blank = 1;					
				}

				if(y < start_height)
				{
					y = start_height;
					(*temp).blank = 1;					
				}
				else if(y > start_height+height)
				{
					y = start_height + height;
					(*temp).blank = 1;					
				}
			}
			fprintf(fp,"%.1f %.1f ", x, y);

			if((*temp).blank == 1)
				fprintf(fp,"moveto\n");
			else
				fprintf(fp,"lineto\n");
			
			temp = (*temp).next;

		}
	}
	else if(ellipse == 1)
	{
		fprintf(fp, "%%!PS-Adobe-3.0 EPSF-3.0\n");
		fprintf(fp, "%%%%BoundingBox: 0 0 100 100\n");
		fprintf(fp, "%.1f setlinewidth\n", (*fig).thickness);
		fprintf(fp, "%.1f %.1f %.1f setrgbcolor\n", (*fig).color.red, (*fig).color.blue, (*fig).color.green);
		fprintf(fp, "%.1f %.1f scale\n", (*fig).width, (*fig).height);
		fprintf(fp, "%.1f %.1f 50 0 360 arc\n", (*fig).center.x, (*fig).center.y );
	}
	fprintf(fp, "stroke\n");

	fclose(fp);
}

