// Remove , and @ from input
LL answer1 = 0, answer2 = 0;
//double testMin = 7, testMax = 27;
double testMin = 200000000000000, testMax = 400000000000000;

struct Point3D {
  double x, y, z;
  Point3D() {}
  Point3D(const Point3D &p) {
    x = p.x; y = p.y; z = p.z;
  }
  Point3D(double X, double Y, double Z) {
    x=X; y=Y; z=Z;
  }
};

struct Hail {
  Point3D p, v;
  Hail() {}
  Hail(const Hail &h) {
    p = h.p;
    v = h.v;
  }
  Hail(LL px, LL py, LL pz, LL vx, LL vy, LL vz) {
    p = Point3D(px, py, pz);
    v = Point3D(vx, vy, vz);
  }
};

ostream& operator<<(ostream &os, const Point3D& p) {
  os << p.x << ", " << p.y << ", " << p.z;
  return os;
}

ostream& operator<<(ostream &os, const Hail& h) {
  os << h.p << " @ " << h.v;
  return os;
}

Point3D getIntersectionXY(const Point3D &p0, const Point3D &p1, const Point3D &p2, const Point3D &p3) {
  Point3D s1, s2;
  s1.x = p1.x - p0.x;
  s1.y = p1.y - p0.y;
  s2.x = p3.x - p2.x;
  s2.y = p3.y - p2.y;
  
  double det = -s2.x * s1.y + s1.x * s2.y;
  if(abs(det) <= 1e-7) {
    return Point3D(0, 0, -1); // No intersection
  }
  double t = ( s2.x * (p0.y - p2.y) - s2.y * (p0.x - p2.x)) / det;
  if(t < 0) {
    return Point3D(0, 0, -1); // Intersected in the past
  }
  double det2 = -s1.x * s2.y + s2.x * s1.y;
  double t2 = ( s1.x * (p2.y - p0.y) - s1.y * (p2.x - p0.x)) / det2;
  if(t2 < 0) {
    return Point3D(0, 0, -1); // Intersected in the past
  }
  
  return Point3D(p0.x + (t * s1.x), p0.y + (t * s1.y), 0);
}

Point3D getIntersectionXY(const Hail &a, const Hail &b) {
  Point3D p1(a.p.x + a.v.x, a.p.y + a.v.y, a.p.z + a.v.z);
  Point3D p3(b.p.x + b.v.x, b.p.y + b.v.y, b.p.z + b.v.z);
  return getIntersectionXY(a.p, p1, b.p, p3);
}

int main() {
  vector<Hail> V;
  LL px, py, pz, vx, vy, vz;
  while(cin >> px >> py >> pz >> vx >> vy >> vz) {
    V.push_back(Hail(px, py, pz, vx, vy, vz));
  }
  cout << V.size() << " hails read:" << endl;
  FORIT(vector<Hail>, V) {
    cout << *it << endl;
  }

  for(int i = 0; i < (int)V.size(); i++) {
    for(int j = i+1; j < (int)V.size(); j++) {
      cout << "Hailstone A: " << V[i] << endl;
      cout << "Hailstone B: " << V[j] << endl;
      
      Point3D p = getIntersectionXY(V[i], V[j]);
      if(p.z != -1.0) {	
	if(p.x >= testMin && p.x <= testMax && p.y >= testMin && p.y <= testMax) {
	  answer1++;
	  cout << "Intersecting inside: " << p.x << ", " << p.y << endl;
	}
	else {
	  cout << "Intersecting OUTSIDE: " << p.x << ", " << p.y << endl;
	}
      }
      else {
	cout << "Not intersecting" << endl;
      }
      cout << endl;
    }
  }
  cout << "Answer1: " << answer1 << endl;

  /*
    Part 2:
    p + t0 * v = p0 + t0 * v0
    p + t1 * v = p1 + t1 * v1
    p + t2 * v = p2 + t2 * v2
    =>
    3 Equations, 6 variables (p, v) = ((px, py, pz), (vx, vy, vz)). Simply use z3:
    
    pip install z3-solver
    Fill in the first 3 lines of the sample data (p0, v0, p1, v1, p2, v2) into the following python code:

    #!/usr/bin/env python3

from z3 import *

px, py, pz = Ints('px py pz')
vx, vy, vz = Ints('vx vy vz')
t0, t1, t2 = Ints('t0 t1 t2')
answer2 = Int('answer2')

solve(
    px + t0 * vx == p0x + t0 * v0x,
    py + t0 * vy == p0y + t0 * v0y,
    pz + t0 * vz == p0z + t0 * v0z,

    px + t1 * vx == p1x + t1 * v1x,
    py + t1 * vy == p1y + t1 * v1y,
    pz + t1 * vz == p1z + t1 * v1z,

    px + t2 * vx == p2x + t2 * v2x,
    py + t2 * vy == p2y + t2 * v2y,
    pz + t2 * vz == p2z + t2 * v2z,

    answer2 == px + py + pz,
)
   */
  
  cout << "Answer2: Please use Z3 as shown in the source code." << endl;
}
