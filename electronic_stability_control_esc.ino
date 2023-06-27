#include <Adafruit_LiquidCrystal.h>

Adafruit_LiquidCrystal lcd(0);

void setup()
{

  //khởi tạo các chân output
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(11, OUTPUT);

  // cấu hình timer 2 để thiếp lập tốc độ của xe với OCR2A là thanh ghi 8 bit (0-255) lưu giá trị tốc độ xe được khởi tạo là 255
  TCCR2A = _BV(COM2A1) | _BV(COM2B1) | _BV(WGM21) | _BV(WGM20);
  TCCR2B = _BV(CS22);
  OCR2A = 255;
  // khởi tạo lcd
  lcd.begin(16, 2);
  lcd.setCursor(5, 0);
  lcd.print("WELCOME");
  // Khởi tạo Serial Monitor
  Serial.begin(9600);
  Serial.println("Welcome");
  delay(1000); // delay 1s
}

void loop()
{

  // Đọc giá trị từ các cảm biến analog
  int K = analogRead(A1);  // cảm biến góc lái
  int Steering = analogRead(A0); // cảm biến góc lái của vô lăng
  int Speed = analogRead(A2);  // cảm biến tốc độ xe
  int Old_Speed;

  Serial.print("K: ");
  Serial.println(K);
  Serial.print("Steering: ");
  Serial.println(Steering);
  Serial.print("Speed: ");
  Serial.println(Speed);
  Serial.print("Old_Speed: ");
  Serial.println(Old_Speed);


  lcd.setCursor(0, 0);
  lcd.print("NORMAL MODE   ");
  Serial.print("NORMAL MODE. SPEED: ");
  lcd.setCursor(0, 1);
  lcd.print("SPEED");
  lcd.setCursor(7, 1);
  lcd.print(OCR2A);
  Serial.println(OCR2A);

  if (OCR2A <= 99)
  {
    lcd.setCursor(9, 1);
    lcd.print("      ");
  }
  else
  {
    lcd.setCursor(11, 1);
    lcd.print("        ");
  }

  /*
     với Old_Speed không thay đổi và cảm biến góc lái
     trong khoảng từ (450;550) thì xe ở trạng thái NORMAL
     nghĩa là không xảy ra thừa hoặc thiếu lái,
     khi đó sẽ liên tục đọc giá trị K
  */

  while (Old_Speed == analogRead(A2) && (K > 450 && K < 550))
  {
    K = analogRead(A1);
    Serial.print("K: ");
    Serial.println(K);
    lcd.setCursor(10, 1);
    lcd.print("      ");
  }
  // set tốc độ xe
  if (Speed >= 0 && Speed < 200)
  {
    OCR2A = 50;
  }
  else if (Speed > 200 && Speed <= 400)
  {
    OCR2A = 100;
  }
  else if (Speed > 400 && Speed <= 600)
  {
    OCR2A = 150;
  }
  else if (Speed > 600 && Speed <= 800)
  {
    OCR2A = 200;
  }
  else if (Speed > 800 && Speed <= 1024)
  {
    OCR2A = 255;
  }

  // gán cho counter = 0 để khi có thừa lái hoặc thiếu lái thì sẽ gán Old_Speed = Speed, sau đó khi thay đổi K trong khỏa
  // cho phép sẽ kiểu tra nếu tốc độ xe giữ nguyên thì về trạng thái bình thường


  // trường hợp K < 450 nghĩa là đang thừa lái
  int counter = 0;
  while (K < 450)
  {
    if (counter == 0)
    {
      Old_Speed = Speed;
      counter += 1;
    }

    Steering = analogRead(A0);
    Serial.print("Steering: ");
    Serial.println(Steering);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("OVERSTEER DTCTED");
    lcd.setCursor(0, 1);
    lcd.print("SPEED");
    lcd.setCursor(7, 1);
    Serial.print("OVERSTEER DTCTED. SPEED: ");
    Serial.println(OCR2A);
    lcd.print(OCR2A);
    lcd.setCursor(11, 1);
    lcd.print("BRKING");

    /* Nếu cảm biến vô lăng nhỏ hơn 512 nghĩa là đang thừa lái bên phải, đèn bên phải phía trước sẽ báo hiệu
      và ngược lại .........lớn....................................trái,.........trái.......................
      Sau đó xe sẽ giảm tốc độ
    */
    if (Steering < 512)
    {
      digitalWrite(10, LOW);
      digitalWrite(9, HIGH);
    }
    if (Steering >= 512)
    {
      digitalWrite(9, LOW);
      digitalWrite(10, HIGH);
    }
    // giảm tốc độ xe
    if (OCR2A > 24)
    {
      OCR2A = OCR2A - 25;
    }
    delay(200);
    K = analogRead(A1);
  }
  // khi được điều chỉnh thừa lái xong, xe về trạng thái normal 2 đèn báo phía trước sẽ về trạng thái off
  digitalWrite(10, LOW);
  digitalWrite(9, LOW);

  counter = 0;

  // trường hợp đang thiếu lái
  while (K > 550)
  {
    if (counter == 0)
    {
      Old_Speed = Speed;
      counter += 1;
    }

    Steering = analogRead(A0);
    Serial.print("Steering: ");
    Serial.println(Steering);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("UNDERSTER DTCTED");
    lcd.setCursor(0, 1);
    lcd.print("SPEED");
    lcd.setCursor(7, 1);
    Serial.print("UNDERSTEER DTCTED. SPEED: ");
    Serial.println(OCR2A);
    lcd.print(OCR2A);
    lcd.setCursor(11, 1);
    lcd.print("BRKING");

    /* Nếu cảm biến vô lăng nhỏ hơn 512 nghĩa là đang thiếu lái bên phải, đèn bên trái phía sau sẽ báo hiệu
      và ngược lại .........lớn....................................trái,.........trái......................
      Sau đó xe sẽ giảm tốc độ
    */
    if (Steering < 512)
    {
      digitalWrite(12, LOW);
      digitalWrite(13, HIGH);
    }
    if (Steering >= 512)
    {
      digitalWrite(13, LOW);
      digitalWrite(12, HIGH);
    }

    // xe giảm tốc độ
    if (OCR2A > 24)
    {
      OCR2A = OCR2A - 25;
    }

    delay(200);
    K = analogRead(A1);
  }
  // khi được điều chỉnh thừa lái xong, xe về trạng thái normal 2 đèn báo phía sau sẽ về trạng thái off
  digitalWrite(13, LOW);
  digitalWrite(12, LOW);
}
