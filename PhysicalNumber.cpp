#include "PhysicalNumber.h"
#include <iostream>
#include <stdexcept>
#include <iomanip>
#include <string> 
using namespace ariel;

/** constructor **/
    PhysicalNumber::PhysicalNumber (double value,Unit unit){
        this->value = value;
        this->unit = unit;
    }   

/** unary  methods - change sign - (-a) **/
    const PhysicalNumber PhysicalNumber::operator+() const{
        return PhysicalNumber(this->value,this->unit);
    }
    const PhysicalNumber PhysicalNumber::operator-() const{
        return PhysicalNumber((-1)*(this->value),this->unit);   
    }
/** binary operator methods - adding to this**/
     const PhysicalNumber PhysicalNumber::operator-(const PhysicalNumber& n )const{
        PhysicalNumber temp = findGroup(*this,n,0);
        return temp;
    }
     const PhysicalNumber PhysicalNumber::operator+(const PhysicalNumber& n )const{
        PhysicalNumber temp = findGroup(*this,n,1);
        return temp;
    }
    PhysicalNumber& PhysicalNumber::operator+=(const PhysicalNumber& n ){
       PhysicalNumber temp = findGroup(*this,n,1);
       this->value=temp.value;
       this->unit=temp.unit;
       return *this;
    }
    PhysicalNumber& PhysicalNumber::operator-=(const PhysicalNumber& n ){
       PhysicalNumber temp = findGroup(*this,n,0);
       this->value=temp.value;
       this->unit=temp.unit;
       return *this;
    }
  
/** prefix operator increment / decrement -(a++)**/
    PhysicalNumber& PhysicalNumber::operator++(){
        
        double val = this->value;
        this->value=(++val);
        return *this;
    }
    PhysicalNumber& PhysicalNumber::operator--(){
        double val = this->value;
        this->value=(--val);
        return *this;
    } 
/** postfix operator increment / decrement -(++a) **/
    const PhysicalNumber PhysicalNumber::operator++(int dummy_flag_for_postfix_increment){
        PhysicalNumber temp(this->value,this->unit);
        double val = this->value;
        val = val+1;
        this->value = val;
        return temp;
    }
    const PhysicalNumber PhysicalNumber::operator--(int dummy_flag_for_postfix_decrement){
        PhysicalNumber temp(this->value,this->unit);
        double val = this->value;
        val = val-1;
        this->value = val;
        return temp;
    }
 /**  friend bigger/smaller operators - (a < b)...**/
    const bool ariel::operator<(const PhysicalNumber& a,const PhysicalNumber& b ){
        PhysicalNumber temp = PhysicalNumber::findGroup(a,b,0);
        cout<<a<<" < "<<b<<endl;//---------------------------
        if(temp.value<0){
            return true;
        }
        return false; 
    }
    const bool ariel::operator>(const PhysicalNumber& a,const PhysicalNumber& b ){
        PhysicalNumber temp = PhysicalNumber::findGroup(a,b,0);
        cout<<a<<" > "<<b<<endl;//---------------------------
        if(temp.value>0){
            return true;
        }
        return false;
    }
    const bool ariel::operator<=(const PhysicalNumber& a,const PhysicalNumber& b ){
        PhysicalNumber temp = PhysicalNumber::findGroup(a,b,0);
        cout<<a<<" <= "<<b<<endl;//---------------------------
        if(temp.value<=0){
            return true;
        }
        return false; 
    }
    const bool ariel::operator>=(const PhysicalNumber& a,const PhysicalNumber& b ){
        PhysicalNumber temp = PhysicalNumber::findGroup(a,b,0);
        cout<<a<<" >= "<<b<<endl;//---------------------------
        if(temp.value>=0){
            return true;
        }
        return false; 
    }
    const bool ariel::operator==(const PhysicalNumber& a,const PhysicalNumber& b ){
        PhysicalNumber test = PhysicalNumber::findGroup(a,b,0);
        cout<<a<<" == "<<b<<endl;//---------------------------
        if(a.value==b.value&&a.unit==b.unit&&test.value==0){
            return true;
        }
        return false;
    }
    const bool ariel::operator!=(const PhysicalNumber& a,const PhysicalNumber& b ){
        PhysicalNumber test = PhysicalNumber::findGroup(a,b,1);
        cout<<a<<" != "<<b<<endl;//---------------------------
        if(a.value!=b.value||a.unit!=b.unit){
            return true;
        }
        return false;
    }


/** output / input stream **/
    ostream& ariel::operator<<(ostream& os , const PhysicalNumber& n){
        int un = n.unit;
      
        string type;
        if(un==0){
            type ="[m]";
        }
        if(un==1){
            type ="[km]";
        }
        if(un==2){
            type ="[cm]";
        }
        if(un==3){
            type ="[sec]";
        }
        if(un==4){
            type ="[min]";
        }
        if(un==5){
            type ="[hour]";
        }
        if(un==6){
            type ="[g]";
        }
        if(un==7){
            type ="[kg]";
        }
        if(un==8){
            type ="[ton]";
        }
      
        os<<  setprecision(6)<<n.value<<type;
        return os;
    }
    istream& ariel::operator>>(istream& is ,  PhysicalNumber& n){
       string temp;
       is>>temp;
       string num;
       string type;
       //checking input
        if(temp[0]!='0'&&temp[0]!='1'&&temp[0]!='2'&&temp[0]!='3'&&temp[0]!='4'&&temp[0]!='5'&&temp[0]!='6'&&temp[0]!='7'&&temp[0]!='8'&&temp[0]!='9'){
            return is;
        }
        if(temp[temp.length()-1]!=']'){
           return is;
        }
       // finding the value and the type
       int j;
       for(int i =0;i<temp.length();i++){
           if(temp[i]=='['){
               j=i+1;
               break;
           }
           num=num+temp[i];
       }

         for(int i =j;i<temp.length();i++){
           if(temp[i]==']'){
               break;
           }
           type=type+temp[i];
       }
      
      double value = std::stod(num);

      //puting the value and the type into the physical number
        Unit unit ;
      if(type=="m"){
          n.value=value;
          n.unit=M;
      }
      else if(type=="cm"){
          n.value=value;
          n.unit=CM;
      }
      else if(type=="km"){
          n.value=value;
          n.unit=KM;
      }
      else if(type=="sec"){
          n.value=value;
          n.unit=SEC;
      }
      else if(type=="min"){
          n.value=value;
          n.unit=MIN;
      }
      else if(type=="hour"){
          n.value=value;
          n.unit=HOUR;
      }
      else if(type=="g"){
          n.value=value;
          n.unit=G;
      }
      else if(type=="kg"){
          n.value=value;
          n.unit=KG; 
      }
      else if(type=="ton"){
          n.value=value;
          n.unit=TON; 
      }
      else{
         return is;
      }
       return is;
    }

/** finds the correct group for the units**/
     PhysicalNumber PhysicalNumber::findGroup(const PhysicalNumber a,const PhysicalNumber b ,int op){
   
        // checks if units part of distance group
        if(a.unit == M||a.unit == KM||a.unit == CM){
          if(b.unit == M||b.unit == KM||b.unit == CM){
            return distanceCase(a,b,op);
          }
        }


        // checks if units part of weight group
        if(a.unit == G||a.unit == KG||a.unit == TON){
          if(b.unit == G||b.unit == KG||b.unit == TON){
            return weightCase(a,b,op);
          }
        }

        // checks if units part of weight group
        if(a.unit == SEC||a.unit == MIN||a.unit == HOUR){
          if(b.unit == SEC||b.unit == MIN||b.unit == HOUR){
            return timeCase(a,b,op);
          }
        }

        //if types are not vaild throws exeption
         throw std::invalid_argument("Cannot perform mathematical operation on invalid unit types");

     }

    /** return number between 1-9 **/
    PhysicalNumber PhysicalNumber::distanceCase(const PhysicalNumber a,const PhysicalNumber b,int op){
        if(a.unit== CM && b.unit== CM){
            if(op == 0) {
                double val = a.value - b.value;
                return  PhysicalNumber (val,a.unit);
            }
            if(op == 1){
                double val = a.value + b.value;
                return  PhysicalNumber (val,a.unit);
            }
            
        }
        if(a.unit== CM && b.unit== M){
            if(op == 0){
                double val = a.value - (b.value*100);
                return  PhysicalNumber (val,a.unit);
            }
             if(op == 1){
                double val = a.value + (b.value*100);
                return  PhysicalNumber (val,a.unit);
            }


        }
        if(a.unit== CM && b.unit== KM){
            if(op == 0){
                double val = a.value - (b.value*100000);
                return  PhysicalNumber (val,a.unit);
            }
            if(op == 1){
                double val = a.value + (b.value*100000);
                return  PhysicalNumber (val,a.unit);
            }
        }


        if(a.unit== M && b.unit== CM){
            if(op == 0){
                double val = a.value - (b.value/100);
                return  PhysicalNumber (val,a.unit);
            }
            if(op == 1){
                double val = a.value + (b.value/100);
                return  PhysicalNumber (val,a.unit);
            }
        }
        if(a.unit== M && b.unit== M){
            if(op == 0){
                double val = a.value - (b.value);
                return  PhysicalNumber (val,a.unit);
            }
            if(op == 1){
                double val = a.value + (b.value);
                return  PhysicalNumber (val,a.unit);
            }
        }
        if(a.unit== M && b.unit== KM){
            if(op == 0){
                double val = a.value - (b.value*1000);
                return  PhysicalNumber (val,a.unit);
            }
            if(op == 1){
                double val = a.value + (b.value*1000);
                return  PhysicalNumber (val,a.unit);
            }
        }


        if(a.unit== KM && b.unit== CM){
            if(op == 0){
                double val = a.value - (b.value/100000);
                return  PhysicalNumber (val,a.unit);
            }
            if(op == 1){
                double val = a.value + (b.value/100000);
                return  PhysicalNumber (val,a.unit);
            }
        }
        if(a.unit== KM && b.unit== M){
            if(op == 0){
                double val = a.value - (b.value/1000);
                return  PhysicalNumber (val,a.unit);
            }
            if(op == 1){
                double val = a.value + (b.value/1000);
                return  PhysicalNumber (val,a.unit);
            }
        }
         if(a.unit== KM && b.unit== KM){
            if(op == 0){
                double val = a.value - (b.value);
                return  PhysicalNumber (val,a.unit);
            }
            if(op == 1){
                double val = a.value + (b.value);
                return  PhysicalNumber (val,a.unit);
            }
        }

        return a;
     }
    /** return number between 10-18 **/
    PhysicalNumber PhysicalNumber::weightCase(const PhysicalNumber a,const PhysicalNumber b,int op){
        
        if(a.unit==G && b.unit==G){
            if(op == 0){
                double val = a.value - (b.value);
                return  PhysicalNumber (val,a.unit);
            }
            if(op == 1){
                double val = a.value + (b.value);
                return  PhysicalNumber (val,a.unit);
            }
        }
        if(a.unit==G && b.unit==KG){
            if(op == 0){
                double val = a.value - (b.value*1000);
                return  PhysicalNumber (val,a.unit);
            }
            if(op == 1){
                double val = a.value + (b.value*1000);
                return  PhysicalNumber (val,a.unit);
            }
        }
        if(a.unit==G && b.unit==TON){
            if(op == 0){
                double val = a.value - (b.value*1000000);
                return  PhysicalNumber (val,a.unit);
            }
            if(op == 1){
                double val = a.value + (b.value*1000000);
                return  PhysicalNumber (val,a.unit);
            }
        }


        if(a.unit==KG && b.unit==G){
            if(op == 0){
                double val = a.value - (b.value/1000);
                return  PhysicalNumber (val,a.unit);
            }
            if(op == 1){
                double val = a.value + (b.value/1000);
                return  PhysicalNumber (val,a.unit);
            }
        }
        if(a.unit==KG && b.unit==KG){
            if(op == 0){
                double val = a.value - (b.value);
                return  PhysicalNumber (val,a.unit);
            }
            if(op == 1){
                double val = a.value + (b.value);
                return  PhysicalNumber (val,a.unit);
            }
        }
        if(a.unit==KG && b.unit==TON){
            if(op == 0){
                double val = a.value - (b.value*1000);
                return  PhysicalNumber (val,a.unit);
            }
            if(op == 1){
                double val = a.value + (b.value*1000);
                return  PhysicalNumber (val,a.unit);
            }
        }


        if(a.unit==TON && b.unit==G){
            if(op == 0){
                double val = a.value - (b.value/1000000);
                return  PhysicalNumber (val,a.unit);
            }
            if(op == 1){
                double val = a.value + (b.value/1000000);
                return  PhysicalNumber (val,a.unit);
            }
        }
        if(a.unit==TON && b.unit==KG){
            if(op == 0){
                double val = a.value - (b.value/1000);
                return  PhysicalNumber (val,a.unit);
            }
            if(op == 1){
                double val = a.value + (b.value/1000);
                return  PhysicalNumber (val,a.unit);
            }
        }
        if(a.unit==TON && b.unit==TON){
            if(op == 0){
                double val = a.value - (b.value);
                return  PhysicalNumber (val,a.unit);
            }
            if(op == 1){
                double val = a.value + (b.value);
                return  PhysicalNumber (val,a.unit);
            }
        }
        return a;
    }

    /** return number between 19-27 **/
    PhysicalNumber PhysicalNumber::timeCase(const PhysicalNumber a,const PhysicalNumber b,int op){
        if(a.unit == SEC && b.unit==SEC){
            if(op == 0){
                double val = a.value - (b.value);
                return  PhysicalNumber (val,a.unit);
            }
            if(op == 1){
                double val = a.value + (b.value);
                return  PhysicalNumber (val,a.unit);
            }
        }
        if(a.unit == SEC && b.unit==MIN){
           if(op == 0){
                double val = a.value - (b.value*60);
                return  PhysicalNumber (val,a.unit);
            }
            if(op == 1){
                double val = a.value + (b.value*60);
                return  PhysicalNumber (val,a.unit);
            }
        }
        if(a.unit == SEC && b.unit==HOUR){
            if(op == 0){
                double val = a.value - (b.value*3600);
                return  PhysicalNumber (val,a.unit);
            }
            if(op == 1){
                double val = a.value + (b.value*3600);
                return  PhysicalNumber (val,a.unit);
            }
        }


        if(a.unit == MIN && b.unit==SEC){
            if(op == 0){
                double val = a.value - (b.value/60);
                return  PhysicalNumber (val,a.unit);
            }
            if(op == 1){
                double val = a.value + (b.value/60);
                return  PhysicalNumber (val,a.unit);
            }
        }
        if(a.unit == MIN && b.unit==MIN){
            if(op == 0){
                double val = a.value - (b.value);
                return  PhysicalNumber (val,a.unit);
            }
            if(op == 1){
                double val = a.value + (b.value);
                return  PhysicalNumber (val,a.unit);
            }
        }
        if(a.unit == MIN && b.unit==HOUR){
            if(op == 0){
                double val = a.value - (b.value*60);
                return  PhysicalNumber (val,a.unit);
            }
            if(op == 1){
                double val = a.value + (b.value*60);
                return  PhysicalNumber (val,a.unit);
            }
        }



        if(a.unit == HOUR && b.unit==SEC){
            if(op == 0){
                double val = a.value - (b.value/3600);
                return  PhysicalNumber (val,a.unit);
            }
            if(op == 1){
                double val = a.value + (b.value/3600);
                return  PhysicalNumber (val,a.unit);
            }
        }
        if(a.unit == HOUR && b.unit==MIN){
            if(op == 0){
                double val = a.value - (b.value/60);
                return  PhysicalNumber (val,a.unit);
            }
            if(op == 1){
                double val = a.value + (b.value/60);
                return  PhysicalNumber (val,a.unit);
            }
        }
        if(a.unit == HOUR && b.unit==HOUR){
            if(op == 0){
                double val = a.value - (b.value);
                return  PhysicalNumber (val,a.unit);
            }
            if(op == 1){
                double val = a.value + (b.value);
                return  PhysicalNumber (val,a.unit);
            }
        }
    return a;
    }



