#include "geom.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <vector>
#include <stack>
using namespace std; 
point2d start_point;

/* **************************************** */
/* returns the signed area of triangle abc. The area is positive if c
   is to the left of ab, and negative if c is to the right of ab
 */
double signed_area2D(point2d a, point2d b, point2d c) {
  point2d A; // a to b -- A
  point2d B; // a to c -- B
  B.x = c.x - a.x;
  B.y = c.y - a.y;
  A.x = b.x - a.x;
  A.y = b.y - a.y;
  double parallelogram_area = B.y * A.x - B.x * A.y;
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

/* computing angle of q, with respect to p */
double compute_angle_pq(point2d p, point2d q){
  return atan((q.y-p.y)/(q.x-p.x));
}


/* comparator for sorting points */
bool compare_by_angle(point2d p, point2d q){
  double p_angle=compute_angle_pq(start_point,p);
  double q_angle=compute_angle_pq(start_point,q);
  return p_angle<q_angle;
}


// compute the convex hull of pts, and store the points on the hull in hull
void graham_scan(vector<point2d>& pts, vector<point2d>& hull ) {

  printf("hull2d (graham scan): start\n"); 
  hull.clear(); //should be empty, but clear it to be safe
  stack<point2d> stack;
  start_point=pts[0];
  for(int i=1 ; i < pts.size(); i++){
    if (pts[i].y<start_point.y){
      start_point=pts[i];
    }
  }
  printf("LINE %d:\n", 83);
  sort(pts.begin(),pts.end(),compare_by_angle);
  stack.push(pts[1]);
  stack.push(pts[2]);
  point2d* first=&pts[1];
  point2d* second=&pts[2];
  printf("LINE %d:\n", 89);
  for(int j=3; j < pts.size(); j++){
    if(left_strictly(*first,*second,pts[j])){
      stack.push(pts[j]);
      first=second;
      second=&pts[j];
    }
    else{
      while(!left_strictly(*first,*second,pts[j])){
        stack.pop();
        second=first;
        point2d* temporary=&stack.top();
        stack.pop();
        first=&stack.top();
        stack.push(*temporary);
      }
      first=second;
      stack.push(pts[j]);
      second=&pts[j];
    }
  printf("LINE %d:\n", 109);
  }
  printf("Stack Size: %lu",stack.size());
  while(!stack.empty()){
    point2d point = stack.top();
    printf("\nThe point we are adding to hull is (%f, %f)\n", point.x, point.y);
    hull.push_back(point);
    stack.pop();
  }

  
  printf("hull2d (graham scan): end\n"); 
  return; 
}
