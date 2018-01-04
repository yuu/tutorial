// http://codingbat.com/prob/p192570

public String withoutString(String base, String remove) {
  String s = "";

  int begin = 0;
  int end = 0;
  for (int i=0; i<base.length(); i++) {
    int f = base.toLowerCase().indexOf(remove.toLowerCase(), begin);
    if (f == -1) {
      if (begin <= base.length()) {
        s += base.substring(begin, base.length());
      }
      break;
    }

    end = f;
    s += base.substring(begin, end);
    begin = f+remove.length();
  }

  return s;
}
