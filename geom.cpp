#include "geom.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <vector>

using namespace std; 

/* **************************************** */
/* returns the signed area of triangle abc. The area is positive if c
   is to the left of ab, and negative if c is to the right of ab
 */
double signed_area2D(point2d a, point2d b, point2d c) {
  point2d A; // a to b -- A
  point2d B; // a to c -- B
  B.x = c.x - a.x;
  printf("\nB.x = c.x - a.x;: %f\n",B.x);
  B.y = c.y - a.y;
  printf("\nB.y = c.y - a.y: %f\n", B.y);
  A.x = b.x - a.x;
  printf("\nA.x = b.x - a.x;: %f\n",A.x);
  A.y = b.y - a.y;
  printf("\nA.y = b.y - a.y;: %f\n", A.y);
  double parallelogram_area = B.y * A.x - B.x * A.y;
  printf("\nArea of Parallelogram: %f\n",parallelogram_area);
  return parallelogram_area*0.5; 
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
// compute the angle from point a to point b
// double compute_angle(point2d a, point2d b){
//   point2d zero_point;
//   zero_point.x=0;
//   zero_point.y=0;
//   double mag_x= sqrt(b.x*b.x + b.y*b.y);
//   double mag_y= sqrt(a.x*a.x + a.y*a.y);
//   return asin(2* signed_area2D(zero_point,a,b)/(mag_x*mag_y));
// }


// compute the convex hull of pts, and store the points on the hull in hull
void graham_scan(vector<point2d>& pts, vector<point2d>& hull ) {

  printf("hull2d (graham scan): start\n"); 
  hull.clear(); //should be empty, but clear it to be safe

  point2d p_lowest=pts[0];
  for(int i=1 ; i < pts.size(); i++){
    if (pts[i].y<p_lowest.y){
      p_lowest=pts[i];
    }
  }


  // just for fun: at the moment we set the hull as the bounding box of
  // pts.  erase this and insert your code instead
  // int x1, x2, y1, y2;
  // if (pts.size() > 0) {
  //   x1 = x2 = pts[0].x;
  //   y1 = y2 = pts[0].y;
    
  //   for (int i=1; i< pts.size(); i++) {
  //     if (pts[i].x < x1) x1 = pts[i].x;
  //     if (pts[i].x > x2) x2 = pts[i].x;
  //     if (pts[i].y < y1) y1 = pts[i].y;
  //     if (pts[i].y > y2) y2 = pts[i].y;
  //   }
  //   point2d p1 = {x1,y1}, p2 = {x2, y1}, p3 = {x2, y2}, p4 = {x1, y2}; 
  //   hull.push_back(p1);
  //   hull.push_back(p2);
  //   hull.push_back(p3);
  //   hull.push_back(p4);
  //   }

  
  printf("hull2d (graham scan): end\n"); 
  return; 
}
