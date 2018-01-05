// http://codingbat.com/prob/p158767
public boolean canBalance(int[] nums) {
  for (int i=0; i<nums.length; i++) {
    int lhs = 0;
    int rhs = 0;
    for (int j=0; j<i+1; j++) {
      lhs += nums[j];
    }
    for (int k=i+1; k<nums.length; k++) {
      rhs += nums[k];
    }

    if (lhs == rhs)
      return true;
  }
  return false;
}
