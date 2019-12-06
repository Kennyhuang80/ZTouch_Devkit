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
		
2019-11-27
	3rd version SW:
		1) modify REFUTH to avoid touch keep triggering.		
		
2019-12-4
	目前发现的第一版8L16 dev-kit硬件bugs如下：

		1） reset按键会一直拉低。
		2） LCD 的封装和实物有些微差异，导致难插入。
		3） Q1三极管的B和E脚需要对调。
		4） R6不需要焊接。
		5） 塑胶立柱高度增加至两倍。
		6） P1和P2的丝印需对调了。


	除了上述bugs以外，第二版还需更新的地方：
		1） 在板子正面左上方增加下列公司信息丝印:
				Copyright 2019 zilog A Littelfuse Company
				ZTA8016 Evaluation Board
				Zilog PCA: 99C1507-001G


		2） 在板子正面空白位置添加下列图标：
				PB free and Rohs compliant

		3） 在板子背面增加下列信息丝印:
				Zilog FAB: 98C1507-001G

		4） 原理图的“Title block”修改为以下信息（蓝色部分）：
				 In the Title line:         ZTA8016 Evaluation board

		In the Number line:        96C1507-00G
		
2019-12-6
     modify the naming of registers to align with Zilog spec.		