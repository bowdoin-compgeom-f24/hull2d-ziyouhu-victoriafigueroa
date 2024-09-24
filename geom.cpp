#include "geom.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include <vector>

using namespace std; 

/* **************************************** */
/* returns the signed area of triangle abc. The area is positive if c
   is to the left of ab, and negative if c is to the right of ab
 */
int signed_area2D(point2d a, point2d b, point2d c) {
  point2d A; // a to b -- A
  point2d B; // a to c -- B
  B.x = c.x - a.x;
  B.y = c.y - a.y;
  A.x = b.x - a.x;
  A.y = b.y - a.y;
  double parallelogram_area = B.y * A.x - B.x * A.y;
  return parallelogram_area / 2; 
}



/* **************************************** */
/* return 1 if p,q,r collinear, and 0 otherwise */
int collinear(point2d p, point2d q, point2d r) {
  return signed_area2D(p, q, r) == 0; 
}



/* **************************************** */
/* return 1 if c is  strictly left of ab; 0 otherwise */
// Signed Area should be positive if c is to the left
int left_strictly(point2d a, point2d b, point2d c) {
  int signed_area = signed_area2D(a, b, c);
  if (signed_area > 0){
    return 1;
  }
  return 0; 
}


/* return 1 if c is left of ab or on ab; 0 otherwise */
int left_on(point2d a, point2d b, point2d c) {
  int signed_area = signed_area2D(a, b, c);
  if (signed_area > 0 || signed_area == 0){
    return 1;
  }
  return 0; 
}



// compute the convex hull of pts, and store the points on the hull in hull
void graham_scan(vector<point2d>& pts, vector<point2d>& hull ) {

  printf("hull2d (graham scan): start\n"); 
  hull.clear(); //should be empty, but clear it to be safe

  //just for fun: at the moment we set the hull as the bounding box of
  //pts.  erase this and insert your code instead
  int x1, x2, y1, y2;
  if (pts.size() > 0) {
    x1 = x2 = pts[0].x;
    y1 = y2 = pts[0].y;
    
    for (int i=1; i< pts.size(); i++) {
      if (pts[i].x < x1) x1 = pts[i].x;
      if (pts[i].x > x2) x2 = pts[i].x;
      if (pts[i].y < y1) y1 = pts[i].y;
      if (pts[i].y > y2) y2 = pts[i].y;
    }
    point2d p1 = {x1,y1}, p2 = {x2, y1}, p3 = {x2, y2}, p4 = {x1, y2}; 
    hull.push_back(p1);
    hull.push_back(p2);
    hull.push_back(p3);
    hull.push_back(p4);
  }
  
  printf("hull2d (graham scan): end\n"); 
  return; 
}

