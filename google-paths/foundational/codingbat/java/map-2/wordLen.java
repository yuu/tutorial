// http://codingbat.com/prob/p125327
public Map<String, Integer> wordLen(String[] strings) {
  Map<String, Integer> map = new HashMap<String, Integer>();

  for (String x : strings) {
    if (map.containsKey(x))
      continue;
    map.put(x, x.length());
  }

  return map;
}
