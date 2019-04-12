/**
 * header file for class PhysicalNumber 
 * */
#include "Unit.h"
#include <iostream>
using namespace std;

namespace ariel {

    class PhysicalNumber{
    private:
        double value;
        Unit unit;
        
        // private methods
        static PhysicalNumber findGroup(const PhysicalNumber a,const PhysicalNumber b, int op);
        static PhysicalNumber distanceCase(const PhysicalNumber a,const PhysicalNumber b, int op);
        static PhysicalNumber weightCase(const PhysicalNumber a,const PhysicalNumber b, int op);
        static PhysicalNumber timeCase(const PhysicalNumber a,const PhysicalNumber b, int op);

    public:
    /** outline constructors **/
        PhysicalNumber (double value,Unit unit);
    
    /** outline public methods **/
      
        /** unary  methods - change sign - (-a) **/
           const PhysicalNumber operator+()const;
           const PhysicalNumber operator-()const;




        /** binary operator methods **/
        const  PhysicalNumber operator-(const PhysicalNumber& n )const;
        const  PhysicalNumber operator+(const PhysicalNumber& n )const;
        PhysicalNumber& operator+=(const PhysicalNumber& n );
        PhysicalNumber& operator-=(const PhysicalNumber& n );
      

        /** prefix operator increment / decrement -(++a)**/
           PhysicalNumber& operator++();
           PhysicalNumber& operator--();

        /** postfix operator increment / decrement -(a++) **/
           const PhysicalNumber operator++(int dummy_flag_for_postfix_increment);
           const PhysicalNumber operator--(int dummy_flag_for_postfix_decrement);  



        /**  friend bigger/smaller operators - (a < b)...**/
            friend const bool operator<(const PhysicalNumber& a,const PhysicalNumber& b );
            friend const bool operator>(const PhysicalNumber& a,const PhysicalNumber& b );
            friend const bool operator<=(const PhysicalNumber& a,const PhysicalNumber& b );
            friend const bool operator>=(const PhysicalNumber& a,const PhysicalNumber& b );
            friend const bool operator==(const PhysicalNumber& a,const PhysicalNumber& b );
            friend const bool operator!=(const PhysicalNumber& a,const PhysicalNumber& b );

   
        /** output / input stream **/
            friend ostream& operator<<(ostream& os , const PhysicalNumber& n); 
            friend istream& operator>>(istream& is ,  PhysicalNumber& n);    



        



    };




}






