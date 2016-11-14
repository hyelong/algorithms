import java.util.*;

public class SpaceScore{
  private void rankRacer(Spaceship[] spaceships){
    // sort by start time
    Arrays.sort(spaceships, (a, b)->(a.start < b.start?-1:1));
    for(int i = 0; i<spaceships.length; i++){
        spaceships[i].start_order = i;
    }

    // sort by end time
    Arrays.sort(spaceships, (a, b)->(a.end < b.end?-1:1));

    List<Integer> ranks = new ArrayList<>();
    for(int i = 0; i<spaceships.length; i++){
        spaceships[i].score = computeScore(ranks, spaceships[i].start_order);
    }

  }

  private int computeScore(List<Integer> ranks, int start_order){
      int index = Collections.binarySearch(ranks, start_order);
      index = (index < 0) ? ~index : index;
      int score = ranks.size() - index;
      ranks.add(index, start_order);
      return score;
  }

  public static void main(String[] args){
    Spaceship[] spaceships = {
          new Spaceship(2,100,200,0,0),
          new Spaceship(3,110,190,0,0),
          new Spaceship(4,105,145,0,0),
          new Spaceship(1,90,150,0,0),
          new Spaceship(5,102,198,0,0)
    };
    SpaceScore space = new SpaceScore();
    space.rankRacer(spaceships);
    Arrays.sort(spaceships, (a, b)->(int)(a.score != b.score ? a.score - b.score : a.id - b.id));
    for(Spaceship spaceship : spaceships){
        System.out.println(spaceship.id + " " + spaceship.score);
    }
  }
}

class Spaceship{
  public int id;
  public long start;
  public long end;
  public int score;
  public int start_order;
  public Spaceship(int id, long start, long end, int score, int start_order){
      this.id = id;
      this.start = start;
      this.end = end;
      this.score = score;
      this.start_order = start_order;
  }
}
