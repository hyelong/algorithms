#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
 
struct Point {
    double pt[2];
};
 
 
struct compareX {
    bool operator ()(const Point& left, const Point& right) const {
        return left.pt[0] < right.pt[0];
    }
};
struct compareY {
    bool operator ()(const Point& left, const Point& right) const {
        return left.pt[1] < right.pt[1];
    }
};
 
struct kdNode {
    Point point;
    kdNode *left;
    kdNode *right;
    kdNode(vector<Point>::iterator begin, vector<Point>::iterator end,int depth);
};
 
kdNode::kdNode( vector<Point>::iterator begin, vector<Point>::iterator end, int depth = 0) {
    left = right = 0;
    if (begin == end){
        return ;
    }
    
    if(depth & 1)
        std::sort( begin, end, compareY());
    else
        std::sort( begin, end, compareX());
 
    auto median = (end - begin) / 2;
    point = *(begin + median );
    if ( begin != ( begin + median ))
        left  = new kdNode(begin , begin + median , depth + 1);
    if ( (begin + median + 1 ) != end )
        right = new kdNode(begin + median + 1, end, depth + 1);
}

double dist(Point &p1, Point &p2){
	double res = 0;
	for(int i=0;i<2;i++){
		res += (p1.pt[i]-p2.pt[i])*(p1.pt[i]-p2.pt[i]);
	}
	return res;
}

Point nearest(kdNode *node, Point &point, Point &min, int depth = 0) {
    if ( node ) {
        int axis = depth % 2;
        double d = point.pt[axis] - min.pt[axis];
        kdNode *near = d <= 0 ? node->left  : node->right;
        kdNode *far  = d <= 0 ? node->right : node->left;
        min = nearest(near, point, min, depth + 1);
        if ((d * d) < dist(point, min)){
            min = nearest(far, point, min, depth + 1);
        }    
        if (dist(point,node->point) < dist(point, min)) {
            min = node->point;
        }
    }
    return min;
}

int main(){
	vector<Point> p_list = {{25, 40}, {51,75}, {70, 70}, {25,20}};
	kdNode kd_node(p_list.begin(), p_list.end());
	Point point = {30,30};
	Point near={51, 75};
	
	Point p = nearest(&kd_node, point, near);
	cout<<p.pt[0]<<","<<p.pt[1]<<endl;
	return 0;
}
