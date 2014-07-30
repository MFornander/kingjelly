/*
 * KingJelly 2014
 * Teensy 3.0 Control Box Code
 *
 * Read values on ADC A0 through A8 and transmit them over Serial-1 as ascii commands.
 * One ADC input is sampled each frame so 9 frames are needed to read all values.  At 50 fps we
 * still sample them each 5+ times a second.
 */

const int kAnalogCount = 9;      // Only read the first 9 ADCs: 4 pots, 4 buttons, and 1 enable switch 
const int kHysteresis = 100;     // Require a delta of 100 compared to the last transmitted value to send new
const int kEdgeClamp = 50;       // Clamp small values to 0 and large to kMaxValue
const int kMaxValue = 1023;      // Max reading from analogRead
const int kFrameRate = 50;       // Samples per seconds
const int kSecsBetweenPings = 3; // Ping the line every 3 seconds

// Persistent values between loop()
int gOldValue[kAnalogCount];
unsigned int gFrame = 0;

void setup()
{
  // Allow blinking on LED13
  pinMode(13, OUTPUT);
  
  // Initialize serial communications at 9600 bps:
  Serial1.begin(9600);
  
  // Init values to out of range to trigger an initial command for all inputs
  for (int index = 0; index < kAnalogCount; ++index)
    gOldValue[index] = -kHysteresis;
}

void loop()
{
  // Cycle over all inputs
  int adcIndex = gFrame % kAnalogCount;
  int value = analogRead(adcIndex);
  
  // Clamp close to edge values to capture 0 and 100%
  if (value < kEdgeClamp)
    value = 0;
  else if (value > (kMaxValue - kEdgeClamp))
    value = kMaxValue;

  // Send a command if a new value exceeds hysteresis threshold or is an edge value
  if (value != gOldValue[adcIndex]  &&
     (abs(value - gOldValue[adcIndex]) >= kHysteresis || value == 0 || value == kMaxValue))
  { 
    setValue(adcIndex, value);
  }

  // Retransmit values every few seconds to signal we are alive
  // ADC8 should be connected to the enable switch on the control box
  gFrame++;
  if (!(gFrame % (kFrameRate * kSecsBetweenPings)))
    setValue(8, gOldValue[8]);
    
  // Wait before the next loop for the analog-to-digital
  // converter to settle after the last reading
  delay(1000 / kFrameRate);
  Serial1.flush();
  digitalWrite(13, LOW);
}

void setValue(int index, int value)
{
  gOldValue[index] = value;
  
  // Format commands as "a50" for analog0 at 50% or "b12" for analog1 at 12%
  // and transform the 0-1023 ADC range to 0-100
  char channel;
  int number;

  if (index < 4) // 0,1,2,3
  {
    channel = 'a' + index;
    number = 100 - value * 100 / kMaxValue;
  }
  else if (index < 8) // 4,5,6,7
  {
    channel = 'A' + index - 4;
    number = (value > kMaxValue/2) ? 1 : 0;  
  }
  else
  {
    channel = ':';
    number = (value > kMaxValue/2) ? 1 : 0;
  }

  Serial1.print(channel);
  Serial1.print(number);
  Serial1.print("\n");
  
  // Flash LED13 every time we transmit a value
  digitalWrite(13, HIGH);
}
