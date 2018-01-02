// http://codingbat.com/prob/p117334
public String stringSplosion(String str) {
  String s = "";
  for (int i=0; i<str.length(); i++) {
    s += str.substring(0, i);
  }
  s += str;
  return s;
}
