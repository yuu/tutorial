// http://codingbat.com/prob/p117019
public int blackjack(int a, int b) {
  int max = 21;
  if (a > max && b > max)
    return 0;
  if (a > max)
    return b;
  else if (b > max)
    return a;

  if (a == max)
    return a;
  else if (b == max)
    return b;

  if (a > b)
    return a;
  else
    return b;
}
