## Degenerate Inputs
1. Collinear points (>=3) on the convex hull
    - Only keep the first and the last points in that set of collinear points in the order we encounter them
2. Generated less than 3 distinct points
    - Only draw hull if there is at least 2 points in hull (the data structure that stores the points constituting the convex hull)
3. All generated points are collinear (e.g. vertical_line, horizontal_line)
    - Because of how we handle case 1, the hull data structure will only hold 2 points. So, this case eventually falls back to case 2.

## Image of OUR customized initializers

`initialize_points_vertical_line()`
![alt text](image.png)

`initialize_points_two_vertical()`
![alt text](image-1.png)

(2) pictures of the two initializers you created
(2) pictures of the other initializers you used;
(3) pictures of the convex hulls computed for each initial configuration of points — for all these choose a reasonable value of n
(4) if your code does not work in all cases, explain.
(5) any extra features.
(6) Time you spent in: Thinking; Programming; Testing; Documenting; Total.
(7) Brief reflection prompts (you don’t need to address all): how challenging did you find this project? what did you learn by doing this project? What did you wish you did differently? If you worked as a team, how did that go? What would you like to explore further?