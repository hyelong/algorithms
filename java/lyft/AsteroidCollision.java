import java.util.*;

/*

#Assume you’re in a space station close to an asteroid belt. 
In this particular asteroid belt there are N asteroids of varying sizes 
(no two asteroids have the same size). 
All of the asteroids move at the same speed, 
but their direction is either towards you or away from you.

#When two asteroids collide, the larger asteroid completely destroys the smaller asteroid 
and continues moving in the same direction. Your task is to write a function to find the 
number of asteroids that will hit your space station.

#Your function will be given a list of Asteroid objects with .mass and .direction properties. 
.mass will be between 1 and Integer.MAX_VALUE. Direction will be -1 for leftwards (away from you) 
or +1 for rightwards (towards you). The position in the list represents the asteroid’s position in 
space and your space station’s position is past the end of the list, as illustrated below:
#               .   O     〇      o     #=#  <- space station
#               →   ←     →       ←
#
# mass          1   5     7       3
# direction     1  -1     1      -1
#
# answer: 1

#               .   o   O   〇   #=#
#               →   →   →   ←
#
# mass          1   3   5   7
# direction     1   1   1  -1
#
# answer: 0

#               O   .   o   #=#
#               →   →   ←
#
# mass          5   1   4
# direction     1   1  -1
#
# answer: 1

#               .   O   o   #=#
#               →   →   ←
#
# mass          1   5   4
# direction     1   1  -1
#
# answer: 2
*/
public class AsteroidCollision {
    public static void main(String[] args) {
        Asteroid asteroid1 = new Asteroid(6, 1);
        Asteroid asteroid2 = new Asteroid(2, -1);
        Asteroid asteroid3 = new Asteroid(5, -1);
        Asteroid asteroid4 = new Asteroid(2, -1);
        List<Asteroid> asteroids = Arrays.asList(asteroid1, asteroid2, asteroid3, asteroid4);
        int res = collision2(asteroids); 
        System.out.println(res);
    }

    public static int collision(List<Asteroid> asteroids) {
        Stack<Asteroid> st = new Stack<>();
        for (Asteroid asteroid : asteroids) {
            while(!st.isEmpty() && st.peek().direction == 1 && asteroid.direction == -1 ) {
                if (asteroid.mass > st.peek().mass) {
                    st.pop();
                    continue;
                } else if (asteroid.mass == st.peek().mass) {
                    st.pop();
                    break;
                } else {
                    break;
                }
            }
            if (asteroid.direction == 1)
                st.add(asteroid);
        }
        return st.size();
    }

    public static int collision2(List<Asteroid> asteroids) {
        int r = 0, l = 1, n = asteroids.size();
        if (n == 1) return asteroids.get(0).direction == 0 ? 1 : 0;
        while(l < n) {
            if (r == -1) {
                r = 0;
                asteroids.set(r, asteroids.get(l));
                l++;
            } else if (asteroids.get(r).direction == 1 && asteroids.get(l).direction == -1) {
                if (asteroids.get(r).mass < asteroids.get(l).mass) {
                    r--;
                } else if (asteroids.get(r).mass == asteroids.get(l).mass) {
                    r--;
                    l++;
                } else {
                    l++;
                }
            } else {
                // there is no collision, both r and l survive.
                // set asteroid l to position r.
                r++;
                asteroids.set(r, asteroids.get(l));
                l++;
            }
        }
        int res = 0;
        for (int i = 0; i <= r; i++) {
            if (asteroids.get(i).direction == 1) res++;
        }
        return res;
    }
    static class Asteroid {
        int mass;
        int direction;
        public Asteroid(int _mass, int _direction) {
            mass = _mass;
            direction = _direction;
        }
    } 
}