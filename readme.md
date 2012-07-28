ArdFeedback
===========

ArdFeedback is a simple arduino sketch that allow to light leds following info given via Serial com.

Goal
----
This sketch is use in an extrem feedback device project.
The project aim to light leds depending of current status of jenkins build (see jenkins-ci.org to know what i'm talking about :).


Serial Commands
-----
Commands are receive from serial port. They are a single char.

The skectch understand these commands :
* R : light on red led only
* Y : light on yellow led only
* G : light on green led only
* B : blink. Well, it's more a wave. All Leds are light on sequentially.


Todo
====
* clean things
* add electronic schema