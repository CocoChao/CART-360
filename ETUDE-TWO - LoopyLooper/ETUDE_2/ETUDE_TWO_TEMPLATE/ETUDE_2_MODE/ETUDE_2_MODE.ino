/**********************ETUDE 3 CART 360 2020*******************************
 * WELCOME! 
 * THE PURPOSE OF THIS EXERCISE IS TO DESIGN A VERY SIMPLE KEYBOARD (4 KEYS)
 * WHICH ALLOWS YOU TO PLAY LIVE, RECORD, AND PLAYBACK SINGLE NOTES (NO CHORDS OR TIMING). 
 * THERE WILL BE A BUTTON WHICH WHEN PRESSED WILL TAKE THE USER TO THE NEXT MODE:
 * THERE ARE 5 POSSIBLE MODES
 * 0 ==  reset    ==   led off == also resets
 * 1 ==  live     ==   led BLUE
 * 2 ==  record   ==   led RED
 * 3 ==  play     ==   led GREEN
 * 4 ==  looper   ==   led PURPLE
 * 
 * ADDITIONALLY - WHEN THE USER CHANGES MODE, 
 * THE RGB LED WILL CHANGE COLOR (ACCORDING TO THE SPECIFICATIONS)

 * PLEASE FOLLOW THE INSTRUCTIONS IN THE COMMENTS:
 * DO NOT ADD ANY MORE FUNCTION DEFINITIONS 
 * ONLY IMPLEMENT THE FUNCTION DEFINITIONS SUPPLIED
 * THERE IS NO NEED TO ADD ANY NEW VARIABLES OR CONSTANTS
 * PROVIDE COMMENTS FOR ANY OF THE CODE IMPLEMENTED
 * GOOD LUCK!
 */
/**** CONSTANTS ********************************************************/

#define BUTTON_MODE_PIN 2 // Button to change the mode

// constants for RGB LED
#define LED_PIN_B 9  // B PIN
#define LED_PIN_G 10 // G PIN
#define LED_PIN_R 11 // R PIN

// constant for note in (button-resistor ladder on breadboard)
# define NOTE_IN_PIN A0

//constant for max number of notes in array
#define MAX_NOTES 16

// duration for a single played note
const int duration = 200;

// constant for pin to output for buzzer 
#define BUZZER_PIN 3 // PWM

/******** VARIABLES *****************************************************/
// counter for how many notes we have
int countNotes = 0;
int mode = 0; // start at off
// array to hold the notes played (for record/play mode)
int notes [MAX_NOTES]; 

/*************************************************************************/


/**********************SETUP() DO NOT CHANGE*******************************/
// Declare pin mode for the single digital input
void setup()
{
  pinMode(BUTTON_MODE_PIN, INPUT);
}

/**********************LOOP() DO NOT CHANGE *******************************
 * INSTRUCTIONS: 
 * There is NO NEED to change the loop - it establishes the flow of the program
 * We call here 3 functions repeatedly:
 * 1: chooseMode(): this function will determine the mode that your program is in 
 * based on if the button (linked to the BUTTON_MODE_PIN) was pressed
 * 2: setRGB(): will set the color of the RGB LED based on the value of the mode variable
 * 3: selectMode(): will determine which function to call based on the value of the mode variable

**************************************************************************/
void loop()
{
  chooseMode();
  setRGB();
  selectMode();
}
/******************CHOOSEMODE(): IMPLEMENT *********************************
 * INSTRUCTIONS:
 * Read the value from the Button (linked to the BUTTON_MODE_PIN) and 
 * if is being pressed then change the mode variable.
 * REMEMBER:
 * mode == 0 is reset 
 * mode == 1 is live
 * mode == 2 is record
 * mode == 3 is play
 * mode == 4 is loopMode
 * Every time the user presses the button, the program will go to the next mode,
 * once it reaches 4, it should go back to mode == 0. 
 * (i.e. if mode ==2 and we press, then mode ==3) ...
**************************************************************************/
void chooseMode(){
  // if reset mode is on when pressed, turn into live mode
  if (mode = 0){ 
    mode ==1;
  }
  // if live mode is on when pressed, turn into record mode
  else if (mode == 1){ 
    mode ==2;
  }
  // if record mode is on when pressed, turn into play mode
  else if (mode == 2){ 
    mode ==3;
  }
  // if play mode is on when pressed, turn into loop mode
  else if (mode == 3){ 
    mode ==4;
  }
  // if loop mode is on when pressed, turn into reset mode
  else if (mode == 4){ 
    mode ==0;
  }
  // Add a delay of 1000 milliseconds to avoid modes overlappings each other.
  delay(1000); 
}

/******************SETRGB(): IMPLEMENT *********************************
 * INSTRUCTIONS:
 * Depending on the value of the mode variable:
 * if the mode is 0 - RGB LED IS OFF
 * if the mode is 1 - RGB LED IS BLUE
 * if mode is 2 - RGB LED IS RED
 * if mode is 3 - RGB LED IS GREEN
 * if mode is 4 - RGB LED iS PURPLE
 * YOU MUST USE A SWITCH CASE CONSTRUCT (NOT A SERIES OF IF / ELSE STATEMENTS
**************************************************************************/
void setRGB()
{
   switch (mode){
    case 0: // RGB LED is off when in reset mode
      analogWrite(LED_PIN_R, 0);    
      analogWrite(LED_PIN_G, 0);    
      analogWrite(LED_PIN_B, 0);    
      break;
    case 1: // RGB LED is Blue when in live mode
      analogWrite(LED_PIN_R, 0);    
      analogWrite(LED_PIN_G, 0);    
      analogWrite(LED_PIN_B, 255);    
      break;
    case 2: // RGB LED is Red when in record mode
      analogWrite(LED_PIN_R, 255);    
      analogWrite(LED_PIN_G, 0);    
      analogWrite(LED_PIN_B, 0);    
      break;
    case 3: // RGB LED is Green when in play mode
      analogWrite(LED_PIN_R, 0);    
      analogWrite(LED_PIN_G, 255);    
      analogWrite(LED_PIN_B, 0); 
      break;
    case 4: // RGB LED is Purple when in looper mode
      analogWrite(LED_PIN_R, 255);    
      analogWrite(LED_PIN_G, 0);    
      analogWrite(LED_PIN_B, 255);    
      break;
  // "default" specifies some code to run if there is no case match   
  }
}
/**********************SELECTMODE() DO NOT CHANGE *******************************
 * INSTRUCTIONS: 
 * There is NO NEED to change this function - it selects WHICH function should run based on the mode variable
 * There are 4 possibilities
 * 1: reset(): this function will reset any arrays etc, and will do nothing else
 * 2: live(): this function will play the corresponding notes 
 * to the user pressing the respective buttons. 
 * NOTE:: the notes played are NOT stored
 * 3: record(): this function will play the corresponding notes 
 * to the user pressing the respective buttons
 * AND will STORE up to 16 consecutive notes in an array.
 * 4: play(): this function will playback any notes stored in the array that were recorded
 * in the previous mode
 * 5: loopMode(): this function will playback any notes stored in the array that were recorded, 
 * BUT unlike the previous mode, you can choose in which sequence the notes are played.
 * REQUIRED: only play notes from the array (no live stuff)

******************************************************************************/
void selectMode()
{
  if(mode == 0) { 
    reset();
  }
  else if(mode == 1) {
    live();
  }
  else if(mode == 2) {
    record();
  }
  
  else if(mode == 3) {
    play();
  }
   
   else if(mode == 4) {
    looper();
  }
}
/******************RESET(): IMPLEMENT **************************************
 * INSTRUCTIONS:
 * this function should ensure that any notes recorded are no longer available
**************************************************************************/
void reset()
{
  // Code from : https://stackoverflow.com/questions/2789735/memset-on-array-of-structures-in-c 
  memset(notes, -1, sizeof(notes)); // overwrite all the notes to invalid values stored in the array. 
  countNotes = 0; // set note count to 0
}
/******************LIVE(): IMPLEMENT **************************************
 * INSTRUCTIONS:
 * this function will play the corresponding notes 
 * to the user pressing the respective buttons
 * NOTE:: the notes played are NOT stored
 * SO: you need read in the input from the analog input (linked to the button-resistor ladder combo)
 * THEN - output the note to the buzzer using the tone() function
**************************************************************************/
void live()
{
  // int thisNote = analogRead(NOTE_IN_PIN); // retrieve the present value identified by NOTE_IN_PIN
  // int resultNote; // Play the retrieved note
  //if(thisNote > 200){ // if the present value is higher than 200 
    //  if (thisNote <= 500){ // if the retrieved value is within the range of values
    //    resultNote = 300;
   // }
   // tone(BUZZER_PIN, thisNote, duration); // buzzer pin 3 plays the retrieved note 
  //}
  int resultNote; // Integer to store and play the retrieved note
  if((analogRead(NOTE_IN_PIN))>200) { // if the value from NOTE_IN_PIN is higher than 200 or within the range
    if ((analogRead(NOTE_IN_PIN))<=500){
      resultNote = 300; // play note
    }
  tone(BUZZER_PIN, (analogRead(NOTE_IN_PIN)), duration); // buzzer pin 3 plays the retrieved note 
  }
}
// use fade in and fade out if statements in lectures 1-2-3
/******************RECORD(): IMPLEMENT **********************************
 * INSTRUCTIONS:
 * this function will play the corresponding notes 
 * to the user pressing the respective buttons
 * AND will STORE up to 16 consecutive notes in an array.
 * SO:you need read in the input from the analog input (linked to the button-resistor ladder combo)
 * AND - output the note to the buzzer using the tone() function
 * THEN store that note in the array  - BE CAREFUL - you can only allow for up to MAX_NOTES to be stored
**************************************************************************/
void record()
{
  if (countNotes < MAX_NOTES); { // if the number of notes is less than 16 
    if ((analogRead(NOTE_IN_PIN)) >= 200) {
     tone(BUZZER_PIN, (analogRead(NOTE_IN_PIN)), duration);
     notes[countNotes] = (analogRead(NOTE_IN_PIN));
     countNotes++;
    }
  //Serial.println(analogRead(NOTE_IN_PIN)); when pressing the right most button (check the small amount happening.
  }
}
/******************PLAY(): IMPLEMENT ************************************
 * INSTRUCTIONS:
 * this function will playback any notes stored in the array that were recorded
 * in the previous mode
 * SO: you need to go through the array of values (be careful - the user may not have put in MAX_NOTES)
 * READ each value IN ORDER
 * AND output each note to the buzzer using the tone() function
 * ALSO: as long as we are in this mode, the notes are played over and over again
 * BE CAREFUL: make sure you allow for the user to get to another mode from the mode button...
**************************************************************************/
void play()
{
  if (analogRead(NOTE_IN_PIN)){
   tone(BUZZER_PIN, 3);
   notes [MAX_NOTES] = 16;
  } 
  notes [MAX_NOTES] = 16;

}
/******************LOOPMODE(): IMPLEMENT *********************************
 * INSTRUCTIONS:
 * this function will playback any notes stored in the array that were recorded
 * in the previous mode
 * SO: you need to go through the array of values (be careful - the user may not have put in MAX_NOTES)
 * READ values IN ANY ORDERING (You MUST use the array - but you can determine your own sequence)
 * AND output each note to the buzzer using the tone() function
 * ALSO: as long as we are in this mode, the notes are played over and over again
 * BE CAREFUL: make sure you allow for the user to get to another mode from the mode button...
**************************************************************************/
void looper()
{
  int 
  for (int i - 0; i <= countNotes; i++){
    notes [MAX_NOTES] = 16;
  }
  int notes [16];
}

/**************************************************************************/
/*****************************PART TWO**********************************/
