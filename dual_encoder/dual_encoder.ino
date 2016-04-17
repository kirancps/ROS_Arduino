
#define LEFT            0
#define RIGHT           1
#define LEFT_ENC_PIN_A PD2  //pin 2
  #define LEFT_ENC_PIN_B PD3  //pin 3
  
  //below can be changed, but should be PORTC pins
#define RIGHT_ENC_PIN_A PC4  //pin A4
#define RIGHT_ENC_PIN_B PC5   //pin A5

volatile long left_enc_pos = 0L;
volatile long right_enc_pos = 0L;
static const int8_t ENC_STATES [] = {0,1,-1,0,-1,0,0,1,1,0,0,-1,0,-1,1,0};  //encoder lookup table

long readEncoder(int i);
void resetEncoder(int i);
void resetEncoders();


void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
    DDRD &= ~(1<<LEFT_ENC_PIN_A);
    DDRD &= ~(1<<LEFT_ENC_PIN_B);
    DDRC &= ~(1<<RIGHT_ENC_PIN_A);
    DDRC &= ~(1<<RIGHT_ENC_PIN_B);
    
    //enable pull up resistors
    PORTD |= (1<<LEFT_ENC_PIN_A);
    PORTD |= (1<<LEFT_ENC_PIN_B);
    PORTC |= (1<<RIGHT_ENC_PIN_A);
    PORTC |= (1<<RIGHT_ENC_PIN_B);
    
    // tell pin change mask to listen to left encoder pins
    PCMSK2 |= (1 << LEFT_ENC_PIN_A)|(1 << LEFT_ENC_PIN_B);
    // tell pin change mask to listen to right encoder pins
    PCMSK1 |= (1 << RIGHT_ENC_PIN_A)|(1 << RIGHT_ENC_PIN_B);
    
    // enable PCINT1 and PCINT2 interrupt in the general interrupt mask
    PCICR |= (1 << PCIE1) | (1 << PCIE2);

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(readEncoder(RIGHT));
  delay(100);
  Serial.println(readEncoder(LEFT));
  delay(100);

}




ISR (PCINT2_vect){
    static uint8_t enc_last=0;
        
  enc_last <<=2; //shift previous state two places
  enc_last |= (PIND & (3 << 2)) >> 2; //read the current state into lowest 2 bits
  
    left_enc_pos += ENC_STATES[(enc_last & 0x0f)];
  }
  
  /* Interrupt routine for RIGHT encoder, taking care of actual counting */
  ISR (PCINT1_vect){
        static uint8_t enc_last=0;
            
  enc_last <<=2; //shift previous state two places
  enc_last |= (PINC & (3 << 4)) >> 4; //read the current state into lowest 2 bits
  
    right_enc_pos += ENC_STATES[(enc_last & 0x0f)];
  }
  
  /* Wrap the encoder reading function */
  long readEncoder(int i) {
    if (i == LEFT) return left_enc_pos;
    else return right_enc_pos;
  }

  /* Wrap the encoder reset function */
  void resetEncoder(int i) {
    if (i == LEFT){
      left_enc_pos=0L;
      return;
    } else { 
      right_enc_pos=0L;
      return;
    }
  }

  void resetEncoders() {
  resetEncoder(LEFT);
  resetEncoder(RIGHT);
}
