// http://codingbat.com/prob/p121193
public int sumNumbers(String str) {
  String item[] = str.split(" ");
  List<String> list = new ArrayList<String>();

  for (String is : item) {
    String i = is.replaceAll("[A-z\\$\\;\\!]", ":");
    String foo[] = i.split(":");
    for (String x : foo) {
      if (x.matches("[A-z]*+"))
        continue;
      list.add(String.valueOf(x));
    }
  }
  
  int ret = 0;
  for (String x : list) {
    ret += Integer.parseInt(x);
  }
  
  return ret;
}
