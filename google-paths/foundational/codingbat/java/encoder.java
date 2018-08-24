// http://codingbat.com/prob/p238573
public String[] encoder(String[] raw, String[] code_words) {
  Map<String, String> map = new HashMap<>();

  for (int i = 0; i < raw.length; i++) {
    if (map.containsKey(raw[i])) {
      raw[i] = map.get(raw[i]);
    } else {
      map.put(raw[i], code_words[i]);
      raw[i] = code_words[i];
    }
  }

  return raw;
}
