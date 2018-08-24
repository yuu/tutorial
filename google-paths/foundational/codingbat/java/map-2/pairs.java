// http://codingbat.com/prob/p126332
public Map<String, String> pairs(String[] strings) {
  Map<String, String> map = new HashMap<String, String>();

  for (String x : strings) {
    if (map.containsKey(x.charAt(0)))
      continue;

    String head = Character.toString(x.charAt(0));
    String tail = Character.toString(x.charAt(x.length() - 1));
    map.put(head, tail);
  }

  return map;
}
