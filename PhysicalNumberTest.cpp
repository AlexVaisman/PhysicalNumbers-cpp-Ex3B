/**
 * Examples of automatic tests for the exercise on physical numbers.
 *
 * @author Erel Segal-Halevi
 * @since 2019-02
 */

#include <iostream>
#include <sstream>
using std::cout, std::endl, std::istringstream;
#include "PhysicalNumber.h"
using ariel::PhysicalNumber, ariel::Unit;
#include "badkan.hpp"

int main() {
  badkan::TestCase testcase;
  int grade=0;
  int signal = setjmp(badkan::longjmp_buffer);
  if (signal == 0) {

    // BASIC TESTS - DO NOT CHANGE
    PhysicalNumber a(2, Unit::KM);
    PhysicalNumber b(300, Unit::M);
    PhysicalNumber c(2, Unit::HOUR);
    PhysicalNumber d(30, Unit::MIN);

    //Our test values
    PhysicalNumber cm(1,Unit::CM);
    PhysicalNumber meter(1,Unit::M);
    PhysicalNumber km(1,Unit::KM);
    PhysicalNumber sec(1,Unit::SEC);
    PhysicalNumber min(1,Unit::MIN);
    PhysicalNumber hour(1,Unit::HOUR);
    PhysicalNumber gram(1,Unit::G);
    PhysicalNumber kilo(1,Unit::KG);
    PhysicalNumber ton(1,Unit::TON);


    testcase
    .setname("Basic output")
    .CHECK_OUTPUT(a, "2[km]")
    .CHECK_OUTPUT(b, "300[m]")

    .setname("Compatible dimensions")
    .CHECK_OUTPUT(b+a, "2300[m]")
    .CHECK_OUTPUT((a+=b), "2.3[km]")
    .CHECK_OUTPUT(a, "2.3[km]")
    .CHECK_OUTPUT(a+a, "4.6[km]")
    .CHECK_OUTPUT(b-b, "0[m]")
    .CHECK_OUTPUT(c, "2[hour]")
    .CHECK_OUTPUT(d, "30[min]")
    .CHECK_OUTPUT(d+c, "150[min]")

    .setname("Incompatible dimensions")
    .CHECK_THROWS(a+c)
    .CHECK_THROWS(a+d)
    .CHECK_THROWS(b+c)
    .CHECK_THROWS(b+d)

    .setname("Basic input")
    .CHECK_OK(istringstream("700[kg]") >> a)
    .CHECK_OUTPUT((a += PhysicalNumber(1, Unit::TON)), "1700[kg]")

    // YOUR TESTS - INSERT AS MANY AS YOU WANT

    .setname("Our basic check")
    .CHECK_OUTPUT(cm, "1[cm]")
    .CHECK_OUTPUT(meter, "1[m]")
    .CHECK_OUTPUT(km, "1[km]")
    .CHECK_OUTPUT(sec, "1[sec]")
    .CHECK_OUTPUT(hour, "1[hour]")
    .CHECK_OUTPUT(min, "1[min]")
    .CHECK_OUTPUT(gram, "1[g]")
    .CHECK_OUTPUT(kilo, "1[kg]")
    .CHECK_OUTPUT(ton, "1[ton]")


    .setname("Our input check")
    .CHECK_OK(istringstream("1[cm]") >> cm)
    .CHECK_OK(istringstream("1[m]") >> meter)
    .CHECK_OK(istringstream("1[km]") >> km)
    .CHECK_OK(istringstream("1[sec]") >> sec)
    .CHECK_OK(istringstream("1[hour]") >> hour)
    .CHECK_OK(istringstream("1[min]") >> min)
    .CHECK_OK(istringstream("1[g]") >> gram)
    .CHECK_OK(istringstream("1[kg]") >> kilo)
    .CHECK_OK(istringstream("1[ton]") >> ton)

    .setname("Our Compatible dimensions check")
    /** checking cm , meters and km **/
    .CHECK_OUTPUT(cm+cm, "2[cm]")
    .CHECK_OUTPUT(cm+meter, "101[cm]")
    .CHECK_OUTPUT(cm+km, "100001[cm]")

    .CHECK_OUTPUT(meter+cm, "1.01[m]")
    .CHECK_OUTPUT(meter+meter, "2[m]")
    .CHECK_OUTPUT(meter+km, "1001[m]")

    .CHECK_OUTPUT(km+cm, "1.00001[km]")
    .CHECK_OUTPUT(km+meter, "1.001[km]")
    .CHECK_OUTPUT(km+km, "2[km]")

    /** checking sec , min and hour **/
    .CHECK_OUTPUT(sec+sec, "2[sec]")
    .CHECK_OUTPUT(sec+min, "61[sec]")
    .CHECK_OUTPUT(sec+hour, "3601[sec]")

    .CHECK_OUTPUT(min+sec, "1.016667[min]")
    .CHECK_OUTPUT(min+min, "2[min]")
    .CHECK_OUTPUT(min+hour, "61[min]")

    .CHECK_OUTPUT(hour+sec, "1.000278[hour]")
    .CHECK_OUTPUT(hour+min, "1.016667[hour]")
    .CHECK_OUTPUT(hour+hour, "2[hour]")

    /**checking gram , kilo , ton**/
    .CHECK_OUTPUT(gram+gram, "2[g]")
    .CHECK_OUTPUT(gram+kilo, "1001[g]")
    .CHECK_OUTPUT(gram+ton, "1000001[g]")

    .CHECK_OUTPUT(kilo+gram, "1.001[kg]")
    .CHECK_OUTPUT(kilo+kilo, "2[kg]")
    .CHECK_OUTPUT(kilo+ton, "1001[kg]")

    .CHECK_OUTPUT(ton+gram, "1.000001[ton]")
    .CHECK_OUTPUT(ton+kilo, "1.001[ton]")
    .CHECK_OUTPUT(ton+ton, "2[ton]")


    .setname("checking inCompatible dimensions")
    .CHECK_THROWS(cm+sec)
    .CHECK_THROWS(meter+sec)
    .CHECK_THROWS(km+sec)
    .CHECK_THROWS(gram+sec)
    .CHECK_THROWS(kilo+sec)
    .CHECK_THROWS(ton+sec)

    .CHECK_THROWS(cm+min)
    .CHECK_THROWS(meter+min)
    .CHECK_THROWS(km+min)
    .CHECK_THROWS(gram+min)
    .CHECK_THROWS(kilo+min)
    .CHECK_THROWS(ton+min)

    .CHECK_THROWS(cm+hour)
    .CHECK_THROWS(meter+hour)
    .CHECK_THROWS(km+hour)
    .CHECK_THROWS(gram+hour)
    .CHECK_THROWS(kilo+hour)
    .CHECK_THROWS(ton+hour)

    .setname("checking methods")
    /** checking unary minus **/
    .CHECK_OUTPUT(-cm, "-1[cm]")
    .CHECK_OUTPUT(-meter, "-1[m]")
    .CHECK_OUTPUT(-km, "-1[km]")
    .CHECK_OUTPUT(-sec, "-1[sec]")
    .CHECK_OUTPUT(-hour, "-1[hour]")
    .CHECK_OUTPUT(-min, "-1[min]")
    .CHECK_OUTPUT(-gram, "-1[g]")
    .CHECK_OUTPUT(-kilo, "-1[kg]")
    .CHECK_OUTPUT(-ton, "-1[ton]")

    /**checking minus **/
    .CHECK_OUTPUT(cm-cm, "0[cm]")
    .CHECK_OUTPUT(meter-meter, "0[m]")
    .CHECK_OUTPUT(km-km, "0[km]")
    .CHECK_OUTPUT(sec-sec, "0[sec]")
    .CHECK_OUTPUT(hour-hour, "0[hour]")
    .CHECK_OUTPUT(min-min, "0[min]")
    .CHECK_OUTPUT(gram-gram, "0[g]")
    .CHECK_OUTPUT(kilo-kilo, "0[kg]")
    .CHECK_OUTPUT(ton-ton, "0[ton]")

    /** checking change to this (+= / -=)**/
    .CHECK_OUTPUT((cm+=cm), "2[cm]")
    .CHECK_OUTPUT((km+=km), "2[km]")
    .CHECK_OUTPUT((meter+=meter), "2[m]")
    .CHECK_OUTPUT((sec+=sec), "2[sec]")
    .CHECK_OUTPUT((min+=min), "2[min]")
    .CHECK_OUTPUT((hour+=hour), "2[hour]")
    .CHECK_OUTPUT((gram+=gram), "2[g]")
    .CHECK_OUTPUT((kilo+=kilo), "2[kg]")
    .CHECK_OUTPUT((ton+=ton), "2[ton]")

    // checking if change took place
    .CHECK_OUTPUT(cm, "2[cm]")
    .CHECK_OUTPUT(km, "2[km]")
    .CHECK_OUTPUT(meter, "2[m]")
    .CHECK_OUTPUT(gram, "2[g]")
    .CHECK_OUTPUT(kilo, "2[kg]")
    .CHECK_OUTPUT(ton, "2[ton]")
    .CHECK_OUTPUT(sec, "2[sec]")
    .CHECK_OUTPUT(min, "2[min]")
    .CHECK_OUTPUT(hour, "2[hour]")

    .CHECK_OUTPUT((cm-=cm), "0[cm]")
    .CHECK_OUTPUT((km-=km), "0[km]")
    .CHECK_OUTPUT((meter-=meter), "0[m]")
    .CHECK_OUTPUT((sec-=sec), "0[sec]")
    .CHECK_OUTPUT((min-=min), "0[min]")
    .CHECK_OUTPUT((hour-=hour), "0[hour]")
    .CHECK_OUTPUT((gram-=gram), "0[g]")
    .CHECK_OUTPUT((kilo-=kilo), "0[kg]")
    .CHECK_OUTPUT((ton-=ton), "0[ton]")

     // checking if change took place
    .CHECK_OUTPUT(cm, "0[cm]")
    .CHECK_OUTPUT(km, "0[km]")
    .CHECK_OUTPUT(meter, "0[m]")
    .CHECK_OUTPUT(gram, "0[g]")
    .CHECK_OUTPUT(kilo, "0[kg]")
    .CHECK_OUTPUT(ton, "0[ton]")
    .CHECK_OUTPUT(sec, "0[sec]")
    .CHECK_OUTPUT(min, "0[min]")
    .CHECK_OUTPUT(hour, "0[hour]")

    /** checking a++ **/

    .CHECK_OUTPUT(cm++, "0[cm]")
    .CHECK_OUTPUT(km++, "0[km]")
    .CHECK_OUTPUT(meter++, "0[m]")
    .CHECK_OUTPUT(gram++, "0[g]")
    .CHECK_OUTPUT(kilo++, "0[kg]")
    .CHECK_OUTPUT(ton++, "0[ton]")
    .CHECK_OUTPUT(sec++, "0[sec]")
    .CHECK_OUTPUT(min++, "0[min]")
    .CHECK_OUTPUT(hour++, "0[hour]")

    // checking if change took place
    .CHECK_OUTPUT(cm, "1[cm]")
    .CHECK_OUTPUT(km, "1[km]")
    .CHECK_OUTPUT(meter, "1[m]")
    .CHECK_OUTPUT(gram, "1[g]")
    .CHECK_OUTPUT(kilo, "1[kg]")
    .CHECK_OUTPUT(ton, "1[ton]")
    .CHECK_OUTPUT(sec, "1[sec]")
    .CHECK_OUTPUT(min, "1[min]")
    .CHECK_OUTPUT(hour, "1[hour]")

    /** checking ++a **/

    .CHECK_OUTPUT(++cm, "2[cm]")
    .CHECK_OUTPUT(++km, "2[km]")
    .CHECK_OUTPUT(++meter, "2[m]")
    .CHECK_OUTPUT(++gram, "2[g]")
    .CHECK_OUTPUT(++kilo, "2[kg]")
    .CHECK_OUTPUT(++ton, "2[ton]")
    .CHECK_OUTPUT(++sec, "2[sec]")
    .CHECK_OUTPUT(++min, "2[min]")
    .CHECK_OUTPUT(++hour, "2[hour]")

    /** checking bigger / smaller / equle operators **/

    .CHECK_EQUAL(cm<meter,true)
    .CHECK_EQUAL(meter<km,true)
    .CHECK_EQUAL(gram<kilo,true)
    .CHECK_EQUAL(kilo<ton,true)
    .CHECK_EQUAL(sec<min,true)
    .CHECK_EQUAL(min<hour,true)

    .CHECK_EQUAL(cm>meter,false)
    .CHECK_EQUAL(meter>km,false)
    .CHECK_EQUAL(gram>kilo,false)
    .CHECK_EQUAL(kilo>ton,false)
    .CHECK_EQUAL(sec>min,false)
    .CHECK_EQUAL(min>hour,false)


    .CHECK_EQUAL(cm<=meter,true)
    .CHECK_EQUAL(meter<=km,true)
    .CHECK_EQUAL(gram<=kilo,true)
    .CHECK_EQUAL(kilo<=ton,true)
    .CHECK_EQUAL(sec<=min,true)
    .CHECK_EQUAL(min<=hour,true)
    .CHECK_EQUAL(hour<=hour,true)

    .CHECK_EQUAL(cm!=meter,true)
    .CHECK_EQUAL(meter!=km,true)
    .CHECK_EQUAL(gram!=kilo,true)
    .CHECK_EQUAL(kilo!=ton,true)
    .CHECK_EQUAL(sec!=min,true)
    .CHECK_EQUAL(min!=hour,true)
    .CHECK_EQUAL(hour!=hour,false)

    .CHECK_EQUAL(cm==meter,false)
    .CHECK_EQUAL(meter==km,false)
    .CHECK_EQUAL(gram==kilo,false)
    .CHECK_EQUAL(kilo==ton,false)
    .CHECK_EQUAL(sec==min,false)
    .CHECK_EQUAL(min==hour,false)
    .CHECK_EQUAL(hour==hour,true)

    .CHECK_EQUAL(cm>=meter,false)
    .CHECK_EQUAL(meter>=km,false)
    .CHECK_EQUAL(gram>=kilo,false)
    .CHECK_EQUAL(kilo>=ton,false)
    .CHECK_EQUAL(sec>=min,false)
    .CHECK_EQUAL(min>=hour,false)



      .print(cout, /*show_grade=*/false);
      grade = testcase.grade();
    } else {
      testcase.print_signal(signal);
      grade = 0;
    }
    cout <<  "*** Grade: " << grade << " ***" << endl;
    return grade;
}
