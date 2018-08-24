// http://codingbat.com/prob/p198700
public boolean evenlySpaced(int a, int b, int c) {
  int[] list = {a, b, c};
  Arrays.sort(list);

  int space = list[2] - list[1];
  int space2 = list[1] - list[0];
  if (space == space2)
    return true;

  return false;
}
