//Clarification:
//All the level should be completely full;
//Confirm does not contain scenario such that: new int[][] {{1}, {1, 1}, {1,1,1,1}, {1,1,1,1,1,1,1}} or new int[][] {{1}, {1, 1}, {1,1,1,1}, {1,1,1,1,1,1}}
//When check available, if root is 1, 2^(level - 1)
//DFS, Recursion: Does not exploit spatial locality. Cache could store current content and content nearby this address. Depends on cache
public class buddyBitmap {
	private static void setBits1(int[][] bitmap, int start, int length) {
		if (bitmap.length == 0) {
			return;
		}
		int bottom = bitmap.length - 1;
		int minimum = Math.min(bitmap[bottom].length, start + length);
		for (int i = start; i < minimum; ++i) {
			bitmap[bottom][i] = 1;
		}
		int level = bottom - 1;
		while (level >= 0) {
			for (int i = 0; i < bitmap[level].length; ++i) {
				if (2 * i >= bitmap[level + 1].length) {
					break;
				}
				if (bitmap[level + 1][2 * i] == 1 && 2 * i + 1 >= bitmap[level + 1].length) {
					bitmap[level][i] = 1;
				}
				else if (bitmap[level + 1][2 * i] == 1 && 2 * i + 1 < bitmap[level + 1].length && bitmap[level + 1][2 * i + 1] == 1) {
					bitmap[level][i] = 1;
				}
				else {
					
				}
			}
			--level;
		}
	}
	private static void setBits2(int[][] bitmap, int start, int length) {
		if (bitmap.length == 0) {
			return;
		}
		int level = bitmap.length - 1;
		int end = Math.min(bitmap[level].length, start + length) - 1;
		while (level >= 0) {
			for (int i = start; i < end + 1; ++i) {
				bitmap[level][i] = 1;
			}
			--level;
			if (start % 2 == 1) {
				start = bitmap[level + 1][start - 1] == 0 ? start + 1 : start;
			}
			if (end % 2 == 0 && end + 1 < bitmap[level + 1].length) {
				end = bitmap[level + 1][end + 1] == 0 ? end - 1 : end;
			}
			start = start/2;
			end = end/2;
		}
	}
	private static void clearBits1(int[][] bitmap, int start, int length) {
		if (bitmap.length == 0) {
			return;
		}
		int bottom = bitmap.length - 1;
		int minimum = Math.min(start + length, bitmap[bottom].length);
		for (int i = start; i < minimum; ++i) {
			bitmap[bottom][i] = 0;
		}
		for (int i = start; i < minimum; ++i) {
			int level = bottom - 1;
			int loc = i/2;
			while (level >= 0) {
				if (bitmap[level][loc] == 0) {
					break;
				}
				bitmap[level--][loc] = 0;
				loc = loc/2;
			}
		}
	}
	private static void clearBits2(int[][] bitmap, int start, int length) {
		if (bitmap.length == 0) {
			return;
		}
		int bottom = bitmap.length - 1;
		int minimum = Math.min(start + length, bitmap[bottom].length);
		for (int i = start; i < minimum; ++i) {
			bitmap[bottom][i] = 0;
		}
		int level = bottom - 1;
		while (level >= 0) {
			for (int i = 0; i < bitmap[level].length; ++i) {
				if (2 * i >= bitmap[level + 1].length) {
					break;
				}
				if (bitmap[level + 1][2*i] == 0 || (2*i + 1 < bitmap[level + 1].length && bitmap[level + 1][2*i + 1] == 0)) {
					bitmap[level][i] = 0;
				}
			}
			--level;
		}
	}
	private static void clearBits3(int[][] bitmap, int start, int length) {
		if (bitmap.length == 0) {
			return;
		}
		int level = bitmap.length - 1;
		int end = Math.min(bitmap[level].length, start + length) -1;
		while (level >= 0) {
			for (int i = start; i < end + 1; ++i) {
				bitmap[level][i] = 0;
			}
			start = start/2;
			end = end/2;
			--level;
		}
	}
	//BFS trick, every parent has been added twice.
	private static void clear(int[][] bitmap, int start, int length) {
		if (bitmap.length == 0) {
			return;
		}
		int bottom = bitmap.length - 1;
		int minimum = Math.min(start + length, bitmap[bottom].length);
		for (int i = start; i < minimum; ++i) {
			bitmap[bottom][i] = 0;
		}
		traverse(bitmap, 0, 0);
	}
	//Debug here!!! different behavior
	private static boolean traverse(int [][]bitmap, int i, int j) {
		if (i == bitmap.length - 1) {
			if (j < bitmap[i].length) {
				return bitmap[i][j] == 1;
			}
			else {
				return true;
			}
		}
		else {
			boolean left = traverse(bitmap, i + 1, 2 * j);
			boolean right = traverse(bitmap, i + 1, 2 * j + 1);
			bitmap[i][j] = left && right ? 1 : 0;
		}
		return bitmap[i][j] == 1;
	}
	private static void clearBits4(int[][] bitmap, int start, int length, int level) {
		if (bitmap.length == 0 || level >= bitmap.length) {
			return;
		}
		int end = Math.min(bitmap[level].length, start + length) -1;
		int original = level;
		int originalE = end;
		int originalS = start;
		while (level >= 0) {
			for (int i = start; i < end + 1; ++i) {
				bitmap[level][i] = 0;
			}
			start = start/2;
			end = end/2;
			--level;
		}
		level = original + 1;
		start = originalS * 2;
		end = originalE * 2;
		while (level < bitmap.length) {
			start = Math.min(start, bitmap[level].length);
			end = Math.min(end, bitmap[level].length);
			for (int i = start; i < end + 1; ++i) {
				bitmap[level][i] = 0;
			}
			start = start * 2;
			end = end * 2;
			++level;
		}
	}
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		int[][] bitmap = new int[][] {{0}, {0, 1}, {0,1,1,1}, {0,1,1,1,1,1,1,1}};
		clearBits1(bitmap, 0, 8);
		for (int i = 0; i < bitmap.length; ++i) {
			for (int j  = 0; j < bitmap[i].length; ++j) {
				System.out.print(bitmap[i][j] + " ");
			}
			System.out.println();
		}
		System.out.println();
		bitmap = new int[][] {{0}, {0, 1}, {0,1,1,1}, {0,1,1,1,1,1,1,1}};
		clearBits2(bitmap, 0, 8);
		for (int i = 0; i < bitmap.length; ++i) {
			for (int j  = 0; j < bitmap[i].length; ++j) {
				System.out.print(bitmap[i][j] + " ");
			}
			System.out.println();
		}
		System.out.println();
		bitmap = new int[][] {{0}, {0, 1}, {0,1,1,1}, {0,1,1,1,1,1,1,1}};
		clearBits3(bitmap, 0, 8);
		for (int i = 0; i < bitmap.length; ++i) {
			for (int j  = 0; j < bitmap[i].length; ++j) {
				System.out.print(bitmap[i][j] + " ");
			}
			System.out.println();
		}
		System.out.println();
		bitmap = new int[][] {{0}, {0, 1}, {0,1,1,1}, {0,1,1,1,1,1,1,1}};
		clear(bitmap, 0, 8);
		for (int i = 0; i < bitmap.length; ++i) {
			for (int j  = 0; j < bitmap[i].length; ++j) {
				System.out.print(bitmap[i][j] + " ");
			}
			System.out.println();
		}
		System.out.println();
		bitmap = new int[][] {{0}, {0, 0}, {0,0,0,0}, {0,0,0,0,0,0,0,0}};
		setBits1(bitmap, 4, 8);
		for (int i = 0; i < bitmap.length; ++i) {
			for (int j  = 0; j < bitmap[i].length; ++j) {
				System.out.print(bitmap[i][j] + " ");
			}
			System.out.println();
		}
		System.out.println();
		bitmap = new int[][] {{0}, {0, 0}, {0,0,0,0}, {0,0,0,0,0,0,0,0}};
		setBits2(bitmap, 4, 8);
		for (int i = 0; i < bitmap.length; ++i) {
			for (int j  = 0; j < bitmap[i].length; ++j) {
				System.out.print(bitmap[i][j] + " ");
			}
			System.out.println();
		}
	}
}
