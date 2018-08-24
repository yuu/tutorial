// http://codingbat.com/prob/p294185
public int interpret(int value, String[] commands, int[] args) {
  int result = 0;
  int argIndex = 0;
  for (String c : commands) {
    switch (c) {
      case "+":
        if (argIndex == 0)
          result = value + args[argIndex];
        else
          result += args[argIndex];
        break;
      case "-":
        if (argIndex == 0)
          result = value - args[argIndex];
        else
          result -= args[argIndex];
        break;
      case "*":
        if (argIndex == 0)
          result = value * args[argIndex];
        else
          result *= args[argIndex];
        break;
      default:
        return -1;
    }
    argIndex++;
  }

  return result;
}
