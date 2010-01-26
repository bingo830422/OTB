/* VPFDRAW.H - DRAW FEATURES */

#ifndef __VPFDRAW_H__

#define __VPFDRAW_H__
#ifdef __cplusplus
extern "C" {
#endif

int draw_edge_row( row_type row, vpf_table_type table );
int draw_edge( long int rownum, vpf_table_type table );

int draw_point_row( row_type row, vpf_table_type table );
int draw_point( long int rownum, vpf_table_type table );

int draw_text_row( row_type row, vpf_table_type table );
int draw_text( long int rownum, vpf_table_type table );

void screen_bounds( double x1, double y1, double x2, double y2,
		    int *xmin, int *ymin, int *xmax, int *ymax );

void draw_face_row( row_type row,
		    vpf_table_type facetable,
		    vpf_table_type ringtable,
		    vpf_table_type edgetable,
		    vpf_table_type spx,
		    color_type outline,
		    color_type c1,
		    color_type c2,
		    color_type c3,
		    color_type c4 );
void draw_face( long int face_id,
		vpf_table_type facetable,
		vpf_table_type ringtable,
		vpf_table_type edgetable,
		vpf_table_type spx,
		color_type outline,
		color_type c1,
		color_type c2,
		color_type c3,
		color_type c4 );

long int next_polygon_edge( edge_rec_type *edge_rec,
			    long int *prevnode,
			    long int face_id );

void outline_face( long int face_id,
		   vpf_table_type facetable,
		   vpf_table_type ringtable,
		   vpf_table_type edgetable,
		   color_type outline,
		   int inner );


void outline_face_table( long int face_id,
			 char *fname,
			 int color,
			 int inner );

#ifdef __cplusplus
}
#endif

#endif
