# Proparking-system-using-IOT-
Fully automated Parking system

PROBLEM : Nowadays its very hard to find a parking spot. We all spend roughly 20 minutes just to find a parking spot daily. It not only waste our precious time but also increases the pollution. The number of vehicles in our road increases day by day and the problem is getting worse.  

SOLUTION: In this project I present a soluton for this problem. In this project we use an app, build using MIT app inventor. The data is stored in the firebase database. 

DETAILS : Here user have to download and run the app first . At first there is a sign up page using his mobile number and password. If the user already have an account he can sign in using his phone number and password.

After that he can select the parking area which contains few number for parking slots.

The distance betwwen user and parking area will be displayed

The user can book a slot for a particular time duration . After payment have done the user will recieve an OTP . The user can then use this OTP  to enter the parking slot. The user also have to enter the otp to exit the exit gate also ( There are two gates entry and exit) .

Here I create a parking area model using NODEMCU, SERVO MOTOR ,IR SENSOR and LCD DISPLAY.

When the user approches the gate and enter the opt in the app the gate will we open and user can park inside it.

If the user exceeds the time limit he will be fined automatically while exiting the gate. 

Total number of slot and number of available slot is displayed on the lcd screen.

The user can also cancel the booking but the amount will not be refunded.

There is also a button which will open up the google map and automatically select your current position and the parking area position.Then it will show the route.

I have uploaded 3 files :
 1. ProParking.ino : This is an ARDUINO file. 
 2. ProParking.apk : This is the apk file to be installed
 3. Proparking.aia : This is the MIT app inventor file extension. You can upload this file into MIT app inventor to see how I build the app and can make neccessary changes. 

To working model of the project is build using:
 1.NODEMCU,
 2.Servo motors (here 2 servo motors are used. One for entry gate and one for exit gate)
 3. IR sensors (here 2 IR sensors are used. One for entry gate and one for exit gate.
