## Degenerate Inputs
1. Collinear points (>=3) on the convex hull
    - Only keep the first and the last points in that set of collinear points in the order we encounter them
2. Generated less than 3 distinct points
    - Only draw hull if there is at least 2 points in hull (the data structure that stores the points constituting the convex hull)
3. All generated points are collinear (e.g. vertical_line, horizontal_line)
    - Because of how we handle case 1, the hull data structure will only hold 2 points. So, this case eventually falls back to case 2.

## Image of OUR customized initializers
`initialize_points_vertical_line()`
![vertical line](c_vertical.png)
`initialize_points_two_vertical()`

![two vertical lines](c_two_vertical.png)

## Image of CLASSMATES' initializers
`initialize_points_wave()`

![wave](c_wave.png)

`intialize_points_1()`
![one](c_one.png)

## Convex Hulls Images:

`initialize_points_circle(points, NPOINTS) `
![circle](c_circle.png)

`initialize_points_cross(points, NPOINTS)`
![cross](c_cross.png)

`initialize_points_horizontal_line(points, NPOINTS)`
![horizontal line](c_horizontail.png)

`initialize_points_random(points, NPOINTS)`
![random](c_box.png)

`initialize_points_vertical_line(points, NPOINTS)`
![vertical line](c_vertical.png)

`initialize_points_two_vertical(points, NPOINTS)`
![two vertical lines](c_two_vertical.png)

`initialize_points_heart(points, NPOINTS)`
![heart](c_heart.png)

`initialize_points_1(points, NPOINTS)`
`intialize_points_1()`
![one](c_one.png)

`initialize_points_2(points,NPOINTS)`
`intialize_points_2()`
![one](c_two.png)

`initialize_points_thin_cross(points,NPOINTS)`
![thin_cross](c_thin_cross.png)

`initialize_points_triangle(points, NPOINTS)`
![triangle](c_triangle.png)

`initialize_points_hexagon(points, NPOINTS)`
![hexagon](c_hexagon.png)

`initialize_points_wave(points, NPOINTS)`
![wave](c_wave.png)

## Known Bugs:
N/A

## Extra Features:
N/A 

## Time Allocation:

### Thinking: 
4 hours

### Programming: 
8 hours

### Testing: 
4 hours

### Documenting: 
4 hours

### Total: 
20 hours

## Reflection:
### How challenging did you find this project? 
Medium hard. (Reasonable)

### Learning outcomes:
Increased proficiency in C++;
int / int returns int
Familiarize with C++ stack and vector structure;
How to calculate angles between 2 points;
Technique: use episilon to solve double overflow issues.

### Team Work Reflection:
Great. Learned a lot!

### Future Work:
Change the color of the convex hull.
Truely randomize of the points.
Allow non-distinct points to be generated.
Extend the problem to 3d.
