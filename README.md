# Programs
//Pentagonal Numbers
class Main {  
  public static int PentagonalNumber(int num) {
    int tot=1;
    for (int x=1;x<num;x++){
        tot=tot+(5*(x));
    }       
    return tot;    
  }   
}
//KaprekarsConstant
class Main {  
  public static int KaprekarsConstant(int num) {
    int[] numArray = {num / 1000, num % 1000 / 100, num % 1000 % 100 / 10, num % 1000 % 100 % 10};
    int t=1000;
    int t1=1;
    int max=0;
    int min=0;
    for (int x=9;x>0;x--){
        for (int y=0;y<4;y++){
            if (numArray[y]==x){
                max=max+(x*t);
                min=min+(x*t1);
                t=t/10;
                t1=t1*10;
            }
        }
    }
    int constant=max-min;
    if (constant==6174){
        return 1;
    }else{
        return 1+KaprekarsConstant(constant);
    }
