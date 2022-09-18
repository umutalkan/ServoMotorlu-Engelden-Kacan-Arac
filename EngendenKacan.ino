#include <Servo.h>
#include <NewPing.h>
 //motor pinleri belirleme
#define SolMotorileri 9
#define SolMotorGeri 10
#define SagMotorileri 11
#define SagMotorGeri 12
//sensör pinleri belirleme
#define USTrigger 6
#define USEcho 7
#define Maksimum_uzaklik 100
Servo servo; //servo motor tanımlama

NewPing sonar(USTrigger, USEcho, Maksimum_uzaklik); //ultrasonik sensör 

unsigned int uzaklik;
unsigned int on_uzaklik;
unsigned int sol_uzaklik;
unsigned int sag_uzaklik;
unsigned int zaman;

// program ilk çalıştığında sadece bir kez çalışacak 
void setup() {
  //motor çıkışları
  pinMode(SolMotorileri, OUTPUT);
  pinMode(SolMotorGeri, OUTPUT);
  pinMode(SagMotorileri, OUTPUT);
  pinMode(SagMotorGeri, OUTPUT);
  servo.attach(4); //servo pin tanımı
}
void loop() {
  delay(500);
  servo.write(90);
  sensor_olcum();
  on_uzaklik = uzaklik;
  if (on_uzaklik > 30 || on_uzaklik == 0) {
    ileri();
  } else {
    dur();

    servo.write(180);
    delay(500);
    sensor_olcum();

    sol_uzaklik = uzaklik;
    servo.write(0);
    delay(500);
    sensor_olcum();

    sag_uzaklik = uzaklik;
    servo.write(90);
    delay(500);

    if (sag_uzaklik > sol_uzaklik) {
      sag();
      delay(500);
      ileri();
    } else if (sol_uzaklik > sag_uzaklik) {
      sol();
      delay(500);
      ileri();
    } else {
      geri();
    }
  }
}

// robotun yön komutları
void ileri() {
  digitalWrite(SolMotorGeri, LOW);
  digitalWrite(SolMotorileri, HIGH);
  digitalWrite(SagMotorGeri, LOW);
  digitalWrite(SagMotorileri, HIGH);
}

// geri
void geri() {
  digitalWrite(SolMotorileri, LOW);
  digitalWrite(SolMotorGeri, HIGH);
  digitalWrite(SagMotorileri, LOW);
  digitalWrite(SagMotorGeri, HIGH);
}

// sol
void sol() {
  digitalWrite(SolMotorileri, LOW);
  digitalWrite(SolMotorGeri, HIGH);
  digitalWrite(SagMotorGeri, LOW);
  digitalWrite(SagMotorileri, HIGH);
}

// sag
void sag() {
  digitalWrite(SolMotorGeri, LOW);
  digitalWrite(SolMotorileri, HIGH);
  digitalWrite(SagMotorileri, LOW);
  digitalWrite(SagMotorGeri, HIGH);
}

//dur
void dur() {
  digitalWrite(SolMotorGeri, LOW);
  digitalWrite(SolMotorileri, LOW);
  digitalWrite(SagMotorileri, LOW);
  digitalWrite(SagMotorGeri, LOW);
}
// sensörün mesafe ölçümü
void sensor_olcum() {
  delay(50);
  zaman = sonar.ping();
  uzaklik = zaman / US_ROUNDTRIP_CM;
}
