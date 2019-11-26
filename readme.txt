2109-11-25
	Known HW issue:
		1) KEY1 should be soldered 90 rotation, otherwise MCU keep reset.
		2) LCD package a little bit small.
		3) Q1 package wrong, B and E should be exchanged.
		4) Zilog logo miss.

		
	first version SW done:
		1) TA as the Buzzer 1KHz PWM output.
		2) T1 as the 1ms systick.
		3) touch Key not been optimized, poor performance.
		
2019-11-26
	Known HW issue:
    	1) should extend the leg to double length.
		2) R6 should be removed, make system working at 3.3V
		
	2nd version SW:
		1) modify GSR to lower value, not to trigger X4 threshold.
		2) adjust the sensitivity of each key.
		3) make code smartoption, and set LVR to 2.3V.