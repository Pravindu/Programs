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
    
    //String Comparison
    
    class MyClass {
    public static void main(String[ ] args) {
        String str="ve9?r?r?19";
        int pair=0;
        int num=0;
        int bet=0;
        int len=str.length();
        char [] strarr= new char[len];
    
        for (int x=0;x<len;x++){
            strarr[x]=str.charAt(x);
        }
        for (int y=0;y<len;y++){
            int current=Character.getNumericValue(strarr[y]);
            if ((current>=0) && (current<=9)){
                bet=0;
                int num1=Character.getNumericValue(strarr[y]);
                for(int z=y+1;z<len;z++){
                    int num2=Character.getNumericValue(strarr[z]);
                    if ((num1+num2)==10){
                        pair+=1;
                        for(int c=y+1;c<z;c++){
                            String qus=Character.toString(strarr[c]);
                            if (qus.equals("?")){
                                bet+=1;
                                System.out.println(bet);
                                if (bet==3){
                                    num+=1;
                                }
                            }
                        }
                    }    
                }   
            }
        }
        System.out.println(num);
        System.out.println(pair);
        if (pair==num && pair!=0){
            System.out.println("true");
        }else{
            System.out.println("false");
        }
    }
}
