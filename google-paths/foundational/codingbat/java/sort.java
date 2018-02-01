// http://codingbat.com/prob/p262890
int[] sort(int[] a) {
  if (a.length == 0)
    return a;

  List<Integer> val = new ArrayList<>();
  val.add(a[0]);
  for (int i = 1; i < a.length; i++) {
    if (!val.contains(a[i]))
      val.add(a[i]);
  }

  int[] array = val.stream().mapToInt(i->i).toArray();
  return array;
}
