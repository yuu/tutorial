// http://codingbat.com/prob/p148813
public Map<String, String> mapShare(Map<String, String> map) {
  Map<String, String> val = map;
  val.remove("c");
  String a = val.get("a");
  if (a != null)
    val.replace("b", a);

  if (!val.containsKey("b"))
    val.put("b", "aaa");

  return val;
}
