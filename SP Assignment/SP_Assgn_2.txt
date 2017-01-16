import java.util.*;
public class intial{   
   
   
    static String convertToHexa(String s)
    {
        System.out.println(s.length());
        String hexadecnum="";
         HashMap<String, String> hex=new HashMap<String, String>();
         hex.put("0000","0");
         hex.put("0001","1");
         hex.put("0010","2");
         hex.put("0011","3");
         hex.put("0100","4");
         hex.put("0101","5");
         hex.put("0110","6");
         hex.put("0111","7");
         hex.put("1000","8");
         hex.put("1001","9");
         hex.put("1010","A");
         hex.put("1011","B");
         hex.put("1100","C");
         hex.put("1101","D");
         hex.put("1110","E");
         hex.put("1111","F");
         
         List<String> list= new ArrayList<String>();
         int index = 0;
         String x;
         while (index<s.length()) {
             list.add(s.substring(index, Math.min(index+4,s.length())));
             index=index+4;
         }
         int j=list.size();
            int k=0;
            System.out.println(list);
            while(k<j)
            {
                x=list.get(k).toString();
                hexadecnum +=hex.get(x);
                k++;
            }
            System.out.println(hexadecnum);
            return (hexadecnum);
    }
    public static boolean isData(String s){
        char arr[]=new char[20];
        arr=s.toCharArray();
        if(s.indexOf('[')>=0)
            return false;
        char tmp=arr[s.length()-1];
        if(tmp=='H'){
            return true;
        }
        else{
            return false;
        }
    }
   
    public static boolean isBracket(String s){
        char arr[]=new char[20];
        arr=s.toCharArray();
        if(arr[0]=='['){
            return true;
        }
        else{
            return false;
        }
    }
   
    public static boolean isDirectAdd(String s1, String s2){
        /*if(s1.indexOf('[')>=0 || s2.indexOf('[')>=0)
            return false;*/
        if(s1.matches("EAX|AX|AL|AH") && s2.indexOf('[')>=0 && isData(s2.substring(1,s2.length()-1)))
        	if(s2.matches("EAX|AX|AL|AH"))
        		return false;
        	else
        		return true;
        if(s2.matches("EAX|AX|AL|AH") && s1.indexOf('[')>=0 && isData(s1.substring(1,s1.length()-1)))
        	if(s1.matches("EAX|AX|AL|AH"))
        		return false;
        	else
        		return true;
       
        return false;
    }
   
    public static boolean isDispAdd(String s1, String s2){
        if(s1.matches("EAX|AX|AL|AH") || s2.matches("EAX|AX|AL|AH"))
        	return false;
        if(s1.indexOf('+')>=0 || s2.indexOf('+')>=0)
            return false;
        if(s1.indexOf(':')>=0)
            return true;
        if(s1.indexOf('[')>=0 && s1.indexOf('H')>=0)
            return true;
        if(s2.indexOf(':')>=0)
            return true;
        if(s2.indexOf('[')>=0 && s2.indexOf('H')>=0)
            return true;
       
        return false;
    }
   
    public static boolean isRegIndi(String s1, String s2){
    	
    	if(s1.indexOf('[')>=0 && isData(s1.substring(1,s1.length()-1)))
    		return false;
    	
    	if(s2.indexOf('[')>=0 && isData(s2.substring(1,s2.length()-1)))
    		return false;
    	
    	if(s1.indexOf('+')>=0 || s2.indexOf('+')>=0)
            return false;
        if(s1.indexOf('[')>=0 || s2.indexOf('[')>=0)
            return true;
       
        return false;
       
    }
   
    public static boolean isRegRel(String s1, String s2){
        if(s1.indexOf('+')>=0 && s1.indexOf('[')>=0 && s1.indexOf('H')>=0){
            return true;
        }
        if(s2.indexOf('+')>=0 && s2.indexOf('[')>=0 && s2.indexOf('H')>=0){
            return true;
        }
       
        return false;
    }
   
    public static boolean isScaled(String s1, String s2){
        if(s1.indexOf('*')>=0 || s2.indexOf('*')>=0)
            return true;
        return false;
    }
   
    public static void main(String[] args) {
       
        HashMap<String, String> hm32 = new HashMap<String, String>();
        HashMap<String, String> hm16 = new HashMap<String, String>();
        HashMap<String, String> hm8 = new HashMap<String, String>();
        HashMap<String, String> hm4 = new HashMap<String, String>();
        HashMap<String, String> hm5 = new HashMap<String, String>();
        HashMap<String, String> hm6 = new HashMap<String, String>();
        HashMap<String, String> hmSeg = new HashMap<String, String>();
        HashMap<String, String> hmScale = new HashMap<String, String>();
       
        hm32.put("EAX","000"); hm32.put("ECX","001"); hm32.put("EDX", "010"); hm32.put("EBX", "011"); hm32.put("ESP","100"); hm32.put("EBP","101"); hm32.put("ESI","110"); hm32.put("EDI","111");
        hm16.put("AX","000"); hm16.put("CX","001"); hm16.put("DX", "010"); hm16.put("BX", "011"); hm16.put("SP","100"); hm16.put("BP","101"); hm16.put("SI","110"); hm16.put("DI","111");
        hm8.put("AL","000"); hm8.put("CL","001"); hm8.put("DL", "010"); hm8.put("BL", "011"); hm8.put("AH","100"); hm8.put("CH","101"); hm8.put("DH","110"); hm8.put("BH","111");
        hm4.put("[BX+SI]","000"); hm4.put("[BX+DI]","001"); hm4.put("[BP+SI]", "010"); hm4.put("[BP+DI]", "011"); hm4.put("[SI]","100"); hm4.put("[DI]","101"); hm4.put("[BP]","110"); hm4.put("[BX]","111");
        hm5.put("[EAX]","000"); hm5.put("[ECX]","001"); hm5.put("[EDX]", "010"); hm5.put("[EBX]", "011"); hm5.put("[EBP]","101"); hm5.put("[ESI]","110"); hm5.put("[EDI]","111");
        hm6.put("[EBX+ESI]","000"); hm6.put("[EBX+EDI]","001"); hm6.put("[EBP+ESI]", "010"); hm6.put("[EBP+EDI]", "011"); hm6.put("[ESI]","100"); hm6.put("[EDI]","101"); hm6.put("[EBP]","110"); hm6.put("[BX]","111");
        hmSeg.put("ES","000"); hmSeg.put("CS","001"); hmSeg.put("SS", "010"); hmSeg.put("DS", "011"); hmSeg.put("FS","100"); hmSeg.put("GS","101");
        hmScale.put("1","00"); hmScale.put("2","01"); hmScale.put("4", "10"); hmScale.put("8", "11");
       
        String instn;
        int mode;
        String [] opcode = new String[10];
        String [] operands = new String[5];
       
        Scanner sc = new Scanner(System.in);
       
        System.out.println("Enter the instruction: ");
        instn=sc.nextLine();
       
        System.out.println("Enter the mode of operation: ");
        mode=sc.nextInt();

        opcode=instn.split(" ");
       
        String ans;
        int w=1;
       
        if(opcode.length==2){
            operands=opcode[1].split(",");   
        }
        else{
        	
            if(opcode[2].equals("PTR")){
                if(opcode[1].equals("BYTE")){
                    w=0;
                }
                else if(opcode[1].equals("WORD")){
                    w=1;
                }
                else if(opcode[1].equals("DWORD")){
                    w=1;
                }
            }
            operands=opcode[3].split(",");
        }
        
        String mod="", regPrefix="", addPrefix="";
       
        if(hm32.get(operands[0])!=null && hm32.get(operands[1])!=null){
            ans="10001011";
            mod="11";
            if(mode==16){
                regPrefix="66";
            }
            ans+=mod+hm32.get(operands[0])+hm32.get(operands[1]);

            ans=convertToHexa(ans);
            ans=regPrefix+ans;
            System.out.println(ans);
        }
        else if(hm16.get(operands[0])!=null && hm16.get(operands[1])!=null){
            ans="10001011";
            mod="11";
            if(mode==32){
                regPrefix="66";
            }
            ans+=mod+hm16.get(operands[0])+hm16.get(operands[1]);
            /*Convert to hex here*/
            ans=convertToHexa(ans);
            ans=regPrefix+ans;
            System.out.println(ans);
        }
        else if(hm8.get(operands[0])!=null && hm8.get(operands[1])!=null){
            ans="10001010";
            mod="11";
            ans+=mod+hm8.get(operands[0])+hm8.get(operands[1]);
            ans=convertToHexa(ans);
            /*Convert to hex here*/
            ans=regPrefix+ans;
            System.out.println(ans);
        }
        else if((hm16.get(operands[0])!=null && hmSeg.get(operands[1])!=null) || (hm16.get(operands[1])!=null && hmSeg.get(operands[0])!=null)){
            int flag=0;
            String reg, seg;
            if(hmSeg.get(operands[0])=="001"){  //code seg
                flag=1;
            }
            if(flag==0){
                if(hm16.get(operands[0])!=null){
                    ans="10001110";
                    mod="00";
                    reg=hm16.get(operands[0]);
                    seg=hmSeg.get(operands[1]);
                }
                else{
                    ans="10001100";
                    mod="00";
                    reg=hm16.get(operands[1]);
                    seg=hmSeg.get(operands[0]);
                }
                ans+=mod+seg+reg;
                ans=convertToHexa(ans);
                System.out.println(ans);
            }
            else{
                System.out.println("Invalid Instruction. Cannot move into CS!");
            }
        }
        else if(isData(operands[1])){
            String reg;
            if(hm32.get(operands[0])!=null){
                if(mode==16)
                    regPrefix="66";
                reg=hm32.get(operands[0]);
                ans="10111"+reg;
                ans=convertToHexa(ans);
                ans=regPrefix+ans;
                //ans to hex
               
                   
            }
            else if(hm16.get(operands[0])!=null){
                if(mode==32)
                    regPrefix="66";
                reg=hm16.get(operands[0]);
                ans="10111"+reg;
                String temp="";
                //ans to hex
                if(operands[1].length()<5)
                {
                    for(int q=0;q<5-operands[1].length();q++)
                        temp=temp+"0";
                }
                temp=temp+operands[1];
                ans=convertToHexa(ans);
                ans=ans+temp.substring(temp.length()-3, temp.length()-1)+temp.substring(temp.length()-5, temp.length()-3);
                System.out.println(ans);
            }
            else if(hm8.get(operands[0])!=null){
                reg=hm8.get(operands[0]);
                ans="10110"+reg;
                //ans to hex
                ans=convertToHexa(ans);
                ans=ans+operands[1];
                System.out.println(ans);
            }
            else if(isBracket(operands[0])){
                String disp="";
                String data=operands[1];
                int flag=0;
                String str=operands[0].substring(1, operands[0].length()-1);
                String newOperands[]=new String[5];
                newOperands=str.split("\\+");
                if(isData(newOperands[newOperands.length-1])){
                    disp=newOperands[1];
                    int len=disp.length();
                    if(len==3){
                        mod="01";
                    }
                    else{
                        mod="10";
                    }
                   
                    if(len>5){
                        flag=1;
                    }
                }
                else{
                    mod="00";
                }                   
               
                if(newOperands[0].equals("BX") || newOperands[0].equals("EBX")){
                    if(mode==32 && newOperands[0].equals("BX")){
                        addPrefix="67";
                    }
                    if(mode==16 && newOperands[0].equals("EBX")){
                        addPrefix="67";
                    }
                    ans="1100011"+w+mod+"000"+"111";
                    ans=convertToHexa(ans);
                    // displacement is appended
                    if(mod=="01"){
                        ans+=disp.substring(0, disp.length()-1);
                    }
                    else if(mod=="10"){
                        if(flag==0){
                            ans+=disp.substring(disp.length()-3, disp.length()-1);
                            if(disp.length()==4)
                                ans+="0"+disp.substring(0, 1);
                            else
                                ans+=disp.substring(0, 2);
                        }
                        else{
                            ans+=disp.substring(disp.length()-3, disp.length()-1)+disp.substring(disp.length()-5, disp.length()-3); // smaller byte first
                            if(disp.length()==6)
                                ans+="0"+disp.substring(0, 1);
                            else
                                ans+=disp.substring(0, 2);
                        }
                    }// data is appended
                    if(w==0){
                        ans+=data.substring(0, data.length()-1);
                    }
                    else{
                        flag=0;
                        if(data.length()>5)
                            flag=1;
                        if(flag==0){
                            ans+=data.substring(data.length()-3, data.length()-1);
                            if(data.length()==4)
                                ans+="0"+data.substring(0, 1);
                            else
                                ans+=data.substring(0, 2);
                        }
                        else{
                            ans+=data.substring(data.length()-3, data.length()-1)+data.substring(data.length()-5, data.length()-3);
                            if(disp.length()==6)
                                ans+="0"+data.substring(0, 1);
                            else
                                ans+=data.substring(0, 2);
                        }
                    }
                    ans=addPrefix+ans;
                    System.out.println(ans);
                }
                else{
                    System.out.println("INVALID INSTRUCTION!");
                }
            }
            else{
                System.out.println("INVALID INSTRUCTION!");
            }
        }
        else if(isDispAdd(operands[0],operands[1])){
            int index=0;
            if(isDispAdd(operands[index], ""))
                index++;
           
            w=0;
            String reg="";
           
            if(hm8.get(operands[index])!=null){
                reg=hm8.get(operands[index]);
            }
            if(hm16.get(operands[index])!=null){
                reg=hm16.get(operands[index]);
                if(mode==32){
                    regPrefix="66";
                    w=1;
                }
            }
            if(hm32.get(operands[index])!=null){
                reg=hm32.get(operands[index]);
                if(mode==16){
                    regPrefix="66";
                    w=1;
                }
            }
            /*DS:[BX] is not considered.*/
            ans=regPrefix+convertToHexa("100010"+(index+1)%2+w+"00"+reg+"110")+operands[1].substring(3, 5)+operands[1].substring(1, 3);
           
            System.out.println(ans);
        }
        else if(isRegIndi(operands[0],operands[1])){
            ans="100010";
            int index=0;
  
            if(isRegIndi(operands[index], ""))
                index++;
            w=0;
            String reg="";
           
            if(hm8.get(operands[index])!=null){
                reg=hm8.get(operands[index]);
            }
            if(hm16.get(operands[index])!=null){
                reg=hm16.get(operands[index]);
                if(mode==32){
                    regPrefix="66";
                    w=1;
                }
            }
            if(hm32.get(operands[index])!=null){
                reg=hm32.get(operands[index]);
                if(mode==16){
                    regPrefix="66";
                    w=1;
                }
            }
            if(hm4.get(operands[(index+1)%2])!=null){
                if(mode==32)
                    addPrefix="67";
            }
            if(hm5.get(operands[(index+1)%2])!=null){
                if(mode==16)
                    addPrefix="67";
            }
            if(operands[(index+1)%2].equals("[BP]") || operands[(index+1)%2].equals("[EBP]")){
                /*last zeroes are hexa.*/
                ans=regPrefix+addPrefix+convertToHexa("100010"+(index+1)%2+w+"01"+reg+"110")+"00";
            }
            else{
                if(hm4.get(operands[(index+1)%2])!=null)
                    ans=regPrefix+addPrefix+convertToHexa("100010"+(index+1)%2+w+"00"+reg+hm4.get(operands[(index+1)%2]));
                else if(hm5.get(operands[(index+1)%2])!=null)
                    ans=regPrefix+addPrefix+convertToHexa("100010"+(index+1)%2+w+"00"+reg+hm5.get(operands[(index+1)%2]));
                else{
                	System.out.println("INVALID INSTRUCTION!");
                	System.exit(0);
                }
            }
            System.out.println(ans);
        }
        else if(hm4.get(operands[0])!=null || hm4.get(operands[1])!=null || hm6.get(operands[0])!=null || hm6.get(operands[1])!=null){
            int index=0, flag=0;
            if(hm4.get(operands[index])!=null || hm6.get(operands[index])!=null){
                index++;
                if(hm4.get(operands[index-1])==null)
                    flag=1;
            }
            else{
                if(hm4.get(operands[index+1])==null)
                    flag=1;
            }
            /*d=(index+1)%2*/
            w=0;
            String reg, seg;
            if(hm8.get(operands[index])!=null){
                reg=hm8.get(operands[index]);
                w=0;
            }
            else if(hm16.get(operands[index])!=null){
                reg=hm16.get(operands[index]);
                if(mode==32)
                    regPrefix="66";
                w=1;
            }
            else{
                reg=hm32.get(operands[index]);
                if(mode==16)
                    regPrefix="66";
                w=1;
            }
           
            if(flag==0 && w==1){
                if(mode==32)
                    addPrefix="67";   
            }
            else{
                if(mode==16 && w==1)
                    addPrefix="67";
            }
            if(flag==0){
                seg=hm4.get(operands[(index+1)%2]);
            }
            else{
                seg=hm6.get(operands[(index+1)%2]);
            }
            ans=regPrefix+addPrefix+convertToHexa("100010"+(index+1)%2+w+"00"+reg+seg);
           
            System.out.println(ans);
           
        }
        else if(isRegRel(operands[0], operands[1])){
            int index=0;
           
            if(isRegRel(operands[index], ""))
                index++;
           
            w=0;
            String reg, seg;
            if(hm8.get(operands[index])!=null){
                reg=hm8.get(operands[index]);
                w=0;
            }
            else if(hm16.get(operands[index])!=null){
                reg=hm16.get(operands[index]);
                if(mode==32)
                    regPrefix="66";
                w=1;
            }
            else{
                reg=hm32.get(operands[index]);
                if(mode==16)
                    regPrefix="66";
                w=1;
            }
           
            seg=operands[(index+1)%2];
            
            String arr[]=new String[10];
            seg=seg.substring(0, seg.length()-2);
            arr=seg.split("\\+");
           
            int len=arr.length;
            String data;
           
            if(len==2){   // like MOV [BX+1000H],CX
                seg=arr[0]+"]";
                data=arr[1];
                if(hm4.get(seg)!=null){
                    seg=hm4.get(seg);
                    if(mode==32)
                        addPrefix="67";
                }
                else{
                    seg=hm6.get(seg);
                    if(mode==16)
                        addPrefix="67";
                }
               
            }   //like MOV [BX+SI+1000H],CX   
            else{
                seg=arr[0]+"+"+arr[1]+"]";
                data=arr[2];
                if(hm4.get(seg)!=null){
                    seg=hm4.get(seg);
                    if(mode==32)
                        addPrefix="67";
                }
                else{
                    seg=hm6.get(seg);
                    if(mode==16)
                        addPrefix="67";
                }
            }
           
            len=data.length();
           
            if(len>2)
                mod="10";
            else
                mod="01";

            if(len<=2){
                ans=regPrefix+addPrefix+convertToHexa("100010"+(index+1)%2+w+mod+reg+seg)+data;
            }
            else if(len<=4){
                ans=regPrefix+addPrefix+convertToHexa("100010"+(index+1)%2+w+mod+reg+seg)+data.substring(data.length()-2, data.length())+data.substring(data.length()-4, data.length()-2);
            }
            else{
                ans=regPrefix+addPrefix+convertToHexa("100010"+(index+1)%2+w+mod+reg+seg)+data.substring(data.length()-2, data.length())+data.substring(data.length()-4, data.length()-2)+data.substring(data.length()-6, data.length()-4);
            }
            System.out.println(ans);
        }
        else if(isScaled(operands[0],operands[1])){
            int index=0;
           
            if(isScaled(operands[index], ""))
                index++;
           
            w=0;
            String reg, seg, scaled;
            if(hm8.get(operands[index])!=null){
                reg=hm8.get(operands[index]);
                w=0;
            }
            else if(hm16.get(operands[index])!=null){
                reg=hm16.get(operands[index]);
                if(mode==32)
                    regPrefix="66";
                w=1;
            }
            else{
                reg=hm32.get(operands[index]);
                if(mode==16)
                    regPrefix="66";
                w=1;
            }
           
            int ind=operands[(index+1)%2].indexOf('*');
            scaled=operands[(index+1)%2].substring(ind-1, ind);
            seg=operands[(index+1)%2].substring(0, ind-1)+operands[(index+1)%2].substring(ind+1, operands[(index+1)%2].length());
           
            String indx, base, ss;
            String tmp[]=new String[5];
            seg=seg.substring(1, seg.length()-1);
            tmp=seg.split("\\+");
           
            ss=hmScale.get(scaled);
           
            tmp[0]="["+tmp[0]+"]";
            tmp[1]="["+tmp[1]+"]";
           
            base=tmp[0];
            indx=tmp[1];
           
            seg="";
            seg+=hm5.get(indx)+hm5.get(base);
           
            if(mode==16){
                ans=regPrefix+"67"+convertToHexa("100010"+(index+1)%2+w+"00"+reg+"100"+ss+seg);
            }
            else{
                ans=regPrefix+convertToHexa("100010"+(index+1)%2+w+"00"+reg+"100"+ss+seg);
            }
            System.out.println(ans);
        }
        else if(isDirectAdd(operands[0],operands[1])){
            //System.out.println("asdfasd");
            if(operands[1].indexOf('[')>=0){
                w=0;
                if(operands[0].equals("AX")){
                	if(mode==32)
                		regPrefix="66";
                    w=1;
                }
                if(operands[0].equals("EAX")){
                    if(mode==16)
                    	regPrefix="66";
                    w=1;
                }
                ans=regPrefix+convertToHexa("1010001"+w)+operands[1].substring(3, 5)+operands[1].substring(1, 3);
            }
            else{
                w=0;
                if(operands[1].equals("AX")){
                	if(mode==32)
                		regPrefix="66";
                    w=1;
                }
                if(operands[1].equals("EAX")){
                	if(mode==16)
                		regPrefix="66";
                    w=1;
                }
                ans=regPrefix+convertToHexa("1010000"+w)+operands[0].substring(3, 5)+operands[0].substring(1, 3);   // like MOV AX,[1234H]
            }
            System.out.println(ans);
        }
        else{
            System.out.println("INVALID INSTRUCTION!");
        }
    }

}