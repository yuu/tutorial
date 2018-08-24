// http://codingbat.com/prob/p117630
public Map<String, Integer> wordCount(String[] strings) {
  Map<String, Integer> map = new HashMap<String, Integer>();
  for (String x : strings) {
    if (map.containsKey(x)) {
      Integer c = map.get(x);
      c += 1;
      map.replace(x, c);
    } else {
      map.put(x, 1);
    }
  }

  return map;
}
