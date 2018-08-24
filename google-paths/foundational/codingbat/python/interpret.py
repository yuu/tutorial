# http://codingbat.com/prob/p234011
def interpret(value, commands, args):
  ret = 0
  for index, command in enumerate(commands):
    if (command == '+'):
      if (index == 0):
        ret = value + args[index]
      else:
        ret += args[index]
    elif (command == '-'):
      if (index == 0):
        ret = value - args[index]
      else:
        ret -= args[index]
    elif (command == '*'):
      if (index == 0):
        ret = value * args[index]
      else:
        ret *= args[index]
    elif (command == '/'):
      if (index == 0):
        ret = value / args[index]
      else:
        ret /= args[index]
    else:
      return -1
  return ret
