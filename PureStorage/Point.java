public class Point{
		int x;
		int y;
		Point(int[] input) {
			this.x = input[0];
			this.y = input[1];
		}
		Point() {
			this.x = 0;
			this.y = 0;
		}
        @Override
        public boolean equals(Object o) {
            if (this == o) return true;
            if (!(o instanceof Point)) return false;

            Point point = (Point) o;
            return x == point.x && y == point.y;
        }

        @Override
        public int hashCode() {
        	int result = x + y << 5 - y;
            return result;
        }
	}