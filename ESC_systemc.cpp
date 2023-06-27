#include <systemc.h>
#include <iostream>
#include <cstring>
#include <iomanip>
#include <cstdlib>
#include <ctime>


using namespace sc_core;
using namespace std;



// lưu giá trị của các sensors
class CarSensor
{
private:
    double steering_angle, yaw_rate, speed_car;

public:
    CarSensor(){};
    CarSensor(double steering_angle, double yaw_rate, double speed_car)
    {
        this->steering_angle = steering_angle;
        this->yaw_rate = yaw_rate;
        this->speed_car = speed_car;
    }

    void set_steering_angle(double steering_angle)
    {
        this->steering_angle = steering_angle;
    }

    void set_yaw_rate(double yaw_rate)
    {
        this->yaw_rate = yaw_rate;
    }

    void set_speed_car(double speed_car)
    {
        this->speed_car = speed_car;
    }

    double get_steering_angle()
    {
        return this->steering_angle;
    }
    double get_yaw_rate()
    {
        return this->yaw_rate;
    }
    double get_speed_car()
    {
        return this->speed_car;
    }
};

SC_MODULE (ESC_System) {
// Các khai báo các thành phần của module
  sc_in<double> steering_angle;
  sc_in<double> yaw_rate;
  sc_in<double> speed_car;

  CarSensor c;
// Phương thức xử lý sự kiện
  void control_logic() {
    
    c = CarSensor(5,2,60);
    
    for(int i = 0 ; i <= 19 ; i++ ) {
        if(c.get_steering_angle() == 0 ){
             wait(0.1,SC_SEC);
             cout <<"\n"<<sc_time_stamp()<<"\tXe di thang. "<<endl;
             if(c.get_yaw_rate() == c.get_steering_angle()) {
                 cout <<sc_time_stamp()<<"\tHe thong on dinh."<< endl;
                 double a = c.get_speed_car() + 5;
                 c.set_speed_car(a);
                 cout <<sc_time_stamp()<<"\tTang toc do : "<<  c.get_speed_car() <<"km/h" << endl;
             }else if(c.get_yaw_rate() > c.get_steering_angle()) {
                 cout <<sc_time_stamp()<<"\tPhat hien xe lech phai."<<endl;
                 cout <<sc_time_stamp()<<"\tPhanh banh xe Rear Left."<<endl;
                 double b = c.get_yaw_rate() - 1;
                 c.set_yaw_rate(b);
                 double a = c.get_speed_car() - 5;
                 c.set_speed_car(a);
                 cout <<sc_time_stamp()<<"\tGiam toc do : "<<  c.get_speed_car() <<"km/h" << endl;
             }else {
                 cout <<sc_time_stamp()<<"\tPhat hien xe lech trai."<<endl;
                 cout <<sc_time_stamp()<<"\tPhanh banh xe Rear Right."<<endl;
                 double b = c.get_yaw_rate() + 1;
                 c.set_yaw_rate(b);
                 double a = c.get_speed_car() - 5;
                 c.set_speed_car(a);
                 cout <<sc_time_stamp()<<"\tGiam toc do : "<<  c.get_speed_car() <<"km/h" << endl;
             }
        }else if(c.get_steering_angle() > 0 ) {
             wait(0.1,SC_SEC);
             cout <<"\n"<<sc_time_stamp()<<"\tXe re phai. "<<endl;
             if(c.get_yaw_rate() == c.get_steering_angle()) {
                 cout <<sc_time_stamp()<<"\tHe thong on dinh."<< endl;
                 double a = c.get_speed_car() + 5;
                 c.set_speed_car(a);
                 cout <<sc_time_stamp()<<"\tTang toc do : "<<  c.get_speed_car() <<"km/h" << endl;
             }else if(c.get_yaw_rate() > c.get_steering_angle()) {
                 cout <<sc_time_stamp()<<"\tPhat hien xe thua lai."<<endl;
                 cout <<sc_time_stamp()<<"\tPhanh banh xe Front Left."<<endl;
                 double b = c.get_yaw_rate() - 1;
                 c.set_yaw_rate(b);
                 double a = c.get_speed_car() - 5;
                 c.set_speed_car(a);
                 cout <<sc_time_stamp()<<"\tGiam toc do : "<<  c.get_speed_car() <<"km/h" << endl;
             }else {
                 cout <<sc_time_stamp()<<"\tPhat hien xe thieu lai."<<endl;
                 cout <<sc_time_stamp()<<"\tPhanh banh xe Rear Right."<<endl;
                 double b = c.get_yaw_rate() + 1;
                 c.set_yaw_rate(b);
                 double a = c.get_speed_car() - 5;
                 c.set_speed_car(a);
                 cout <<sc_time_stamp()<<"\tGiam toc do : "<<  c.get_speed_car() <<"km/h" << endl;
        }}else {
             wait(0.1,SC_SEC);
             cout <<"\n"<<sc_time_stamp()<<"\tXe re trai. "<<endl;
             if(c.get_yaw_rate() == c.get_steering_angle()) {
                 cout <<sc_time_stamp()<<"\tHe thong on dinh."<< endl;
                 double a = c.get_speed_car() + 5;
                 c.set_speed_car(a);
                 cout <<sc_time_stamp()<<"\tTang toc do : "<<  c.get_speed_car() <<"km/h" << endl;
             }else if(c.get_yaw_rate() > c.get_steering_angle()) {
                 cout <<sc_time_stamp()<<"\tPhat hien xe thieu lai."<<endl;
                 cout <<sc_time_stamp()<<"\tPhanh banh xe Rear Left."<<endl;
                 double b = c.get_yaw_rate() - 1;
                 c.set_yaw_rate(b);
                 double a = c.get_speed_car() - 5;
                 c.set_speed_car(a);
                 cout <<sc_time_stamp()<<"\tGiam toc do : "<<  c.get_speed_car() <<"km/h" << endl;
             }else {
                 cout <<sc_time_stamp()<<"\tPhat hien xe thua lai."<<endl;
                 cout <<sc_time_stamp()<<"\tPhanh banh xe Front Right."<<endl;
                 double b = c.get_yaw_rate() + 1;
                 c.set_yaw_rate(b);
                 double a = c.get_speed_car() - 5;
                 c.set_speed_car(a);
                 cout <<sc_time_stamp()<<"\tGiam toc do : "<<  c.get_speed_car() <<"km/h" << endl;
        }
    }
  }
  }

// Constructor của module
  SC_CTOR (ESC_System) {
    // Đăng ký các quá trình hoặc các phương thức xử lý sự kiện
    SC_THREAD (control_logic);
    sensitive << steering_angle << yaw_rate << speed_car;
  }
};

int sc_main(int argc, char* argv[]) {
  sc_signal<double> steering_angle, yaw_rate, speed_car;
  // Tạo một instance của module
  ESC_System esc_system("ESC_System");
  esc_system.steering_angle(steering_angle);
  esc_system.yaw_rate(yaw_rate);
  esc_system.speed_car(speed_car);
  
  cout << "\n \t HE THONG ESC O TO \n\n"
         << endl;
  
 // Chạy mô phỏng SystemC
  sc_start();

  return 0;

}
