#include "geom.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <vector>
#include <stack>
#include <format>
#include <iostream>

using namespace std; 
point2d start_point;
double epsilon = pow(10,-15);

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
  double signed_area = signed_area2D(p, q, r);
  return  abs(signed_area) < epsilon ; 
}

/* **************************************** */
/* return 1 if c is  strictly left of ab; 0 otherwise */
// Signed Area should be positive if c is to the left
int left_strictly(point2d a, point2d b, point2d c) {
  double signed_area = signed_area2D(a, b, c);
  if (signed_area > 0){
    return 1;
  }
  return 0; 
}


/* return 1 if c is left of ab or on ab; 0 otherwise */
int left_on(point2d a, point2d b, point2d c) {
  double signed_area = signed_area2D(a, b, c);
  if (signed_area > 0 || signed_area == 0){
    return 1;
  }
  return 0; 
}

/* computing angle of q, with respect to p */
double compute_angle_pq(point2d p, point2d q){
  if (p.x == q.x && p.y == q.y){
    return 0;
  }
  double val;
  if ((q.x - p.x) == 0){
    val = INFINITY;
  }
  else{
    val = (q.y-p.y)/(q.x-p.x);
  }
  double rad = atan(val);
  double degree = rad * 57.2958;
  if (degree < 0){
    degree = degree + 180;
  }
  return degree;
}


/* comparator for sorting points */
bool compare_by_angle(point2d p, point2d q){
  double p_angle = compute_angle_pq(start_point, p);
  double q_angle = compute_angle_pq(start_point, q);
  if(p_angle == q_angle){
    if (p.x == q.x){
      return p.y<q.y;
    }
    return p.x < q.x;
  }
  return p_angle < q_angle;
}

// compute the convex hull of pts, and store the points on the hull in hull
void graham_scan(vector<point2d>& pts, vector<point2d>& hull ) {
  printf("hull2d (graham scan): start\n"); 
  hull.clear(); //should be empty, but clear it to be safe
  stack<point2d> stack;
  start_point = pts[0];

  // Checked! Good.
  for(int i = 0; i < pts.size(); i++){
    if (pts[i].y < start_point.y){
      start_point = pts[i];
    }
    if(pts[i].y==start_point.y){
      if(pts[i].x<start_point.x){
        start_point=pts[i];
      }
    }
  }
  printf("The start point is (%f, %f) \n", start_point.x, start_point.y);

  // Checked! Good.
  string ordered_points;
  sort(pts.begin(), pts.end(), compare_by_angle);
  for (int i = 0; i < pts.size(); i++){
    point2d point = pts[i];
    ordered_points = ordered_points + "(" + to_string(point.x) + ", " + to_string(point.y) + ") ";
  }
  cout << ordered_points << endl;

  stack.push(pts[0]); //p 
  stack.push(pts[1]); // q
  // point2d* first=&pts[0];
  // point2d* second=&pts[1];
  point2d first=pts[0];
  point2d second=pts[1];
  for(int j=2; j < pts.size(); j++){
    if(left_on(first,second,pts[j])){
      if (collinear(first,second,pts[j])){
        stack.pop();
        second=pts[j];
        stack.push(pts[j]);
      }
      else{
        stack.push(pts[j]);
        first=second;
        second=pts[j];
      }
    }
    else{
      while(!left_on(first,second,pts[j])){
        stack.pop();
        second=first;
        stack.pop();
        cout << stack.size() << endl;
        first=stack.top();
        stack.push(second);
      }
      if (collinear(first,second,pts[j])){
        stack.pop();
        second=pts[j];
        stack.push(pts[j]);
      }
      else{
        stack.push(pts[j]);
        first=second;
        second=pts[j];
      }
    }
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
