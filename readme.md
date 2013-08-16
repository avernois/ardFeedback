ArdFeedback
===========

ArdFeedback is a simple arduino sketch that allow to light leds following info given via Serial com.

Goal
----
This sketch is use in an extrem feedback device project.
The project aim to light leds depending of current status of jenkins build (see jenkins-ci.org to know what i'm talking about :).

It is intend to be used with [ArdFeeback-Control](https://github.com/avernois/ardFeedback-control).


Serial Commands
-----
Commands are receive from serial port. They are a single char.

The skectch understand these commands :
* 'R' or 'F' : light on failure led only (usually red)
* 'Y' or 'U' : light on unstable leds only (usually yellow)
* 'G' or 'S' : light on success leds only (usually green (or blue for [jenkins' friend](http://jenkins-ci.org)))
* 'B' : blink. Well, it's more like a wave. All Leds are light on sequentially.
* 'C' : make the current status blinking (really blinking this time


Schema
------
A schema of the prototyping board can be found in _schema_ directory in [Fritzing](http://fritzing.org) format

![Scheme](https://github.com/avernois/ardFeedback/raw/master/img/ardfeedback_bb.png "ArdFeedback scheme")



Todo
====
* clean things
