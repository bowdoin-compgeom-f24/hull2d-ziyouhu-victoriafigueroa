#include "geom.h"
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <vector>
#include <stack>

using namespace std;
point2d start_point;
double epsilon = pow(10,-6);

/* **************************************** */
/* returns the signed area of triangle abc. The area is positive if c
   is to the left of ab, and negative if c is to the right of ab
 */
double signed_area2D(point2d a, point2d b, point2d c) {
  point2d A; // Use point2d structure to represent a vector from a to b.
  point2d B; // Use point2d structure to represent a vector from a to c.
  B.x = c.x - a.x;
  B.y = c.y - a.y;
  A.x = b.x - a.x;
  A.y = b.y - a.y;
  double parallelogram_area = B.y * A.x - B.x * A.y;
  return parallelogram_area * 0.5; 
}

/* **************************************** */
/* return 1 if p,q,r collinear, and 0 otherwise */
int collinear(point2d p, point2d q, point2d r) {
  double signed_area = signed_area2D(p, q, r);
  return abs(signed_area) < epsilon ; 
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
  if (signed_area >= 0){
    return 1;
  }
  return 0; 
}

/* computing angle of q, with respect to p */
double compute_angle_pq(point2d p, point2d q){
  // Avoid computing angle of a point with itself
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
  // angle size in radians
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

  // Use lexigraphical ordering in case of a tie
  if (p_angle == q_angle){
    if (p.x == q.x){
      return p.y < q.y;
    }
    return p.x < q.x;
  }

  return p_angle < q_angle;
}

// compute the convex hull of pts, and store the points on the hull in hull
void graham_scan(vector<point2d>& pts, vector<point2d>& hull) {
  printf("hull2d (graham scan): start\n"); 
  hull.clear(); //should be empty, but clear it to be safe

  stack<point2d> stack;
  start_point = pts[0];

  // Select the point with the lowest y to be the start
  for(int i = 0; i < pts.size(); i++){
    if (pts[i].y < start_point.y){
      start_point = pts[i];
    }
    // If there are multiple lowest point, choose the leftmost point to be the start
    if (pts[i].y == start_point.y){
      if (pts[i].x < start_point.x){
        start_point = pts[i];
      }
    }
  }
  sort(pts.begin(), pts.end(), compare_by_angle);

  stack.push(pts[0]);
  stack.push(pts[1]);
  point2d first = pts[0]; // first always stores the point pushed before second on stack.
  point2d second = pts[1]; // second always stores the latest point we pushed onto the stack.
  for (int j = 2; j < pts.size(); j++){
    if (left_on(first, second, pts[j])){

      // To avoid collinear points on convex hull,
      // we only keep the first and last points we encountered in that set of collinear points.
      if (collinear(first, second, pts[j])){
        stack.pop();
        stack.push(pts[j]);
      }
      else{
        stack.push(pts[j]);
        first = second;
      }
      second = pts[j];
    }
    else{
      // Pop the stack until pts[j] is to the left or on the line of first-second.
      while (!left_on(first, second, pts[j])){
        stack.pop();
        second = first;
        stack.pop();
        first = stack.top();
        stack.push(second);
      }
      // Avoid having >= 3 collinear points on the convex hull.
      if (collinear(first,second,pts[j])){
        stack.pop();
        second = pts[j];
        stack.push(pts[j]);
      }
      else{
        stack.push(pts[j]);
        first = second;
        second = pts[j];
      }
    }
  }

  // Push all the points in the stack to the hull
  // Note: the points in stack are already IN (counter-clockwise) ORDER of the hull.
  while(!stack.empty()){
    point2d point = stack.top();
    hull.push_back(point);
    stack.pop();
  }
  printf("hull2d (graham scan): end\n"); 
  return; 
}
