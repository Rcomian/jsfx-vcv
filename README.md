# JSFX plugins for VCV Rack

**Caution: Extremely experimental.** _This plugin will probably kick your dog._

This plugin allows you to use JSFX scripts from the Reaper DAW as VCV Rack modules.

JSFX is Reaper's embedded programming language, reference here: https://www.reaper.fm/sdk/js/js.php
This plugin uses JsusFX as its engine to interpret the langauge and do the real work: https://github.com/asb2m10/jsusfx
If a script isn't supported by JsusFX, it won't be supported in this plugin.

The plugin will create a module menu entry for every JSFX script it finds in the `jsfx` directory, which you'll find directly next to your `plugins` directory.
The plugin will auto-generate a UI with all the knobs, inputs and outputs defined in the script.
Every knob also has a tunable CV input.

If a script supports graphics, a second module entry will be made which will include all the knobs, inputs, outputs, and a screen to display the graphics.
All support is very basic at the moment, graphics support is doubly so.

## Installing JSFX scripts

Scripts are loaded from the `jsfx` folder. The location of this folder will depend on your platform:

* `Documents/Rack/jsfx` on Mac
* `My Documents/Rack/jsfx` on Windows
* `~/.Rack/jsfx` on Linux

Scripts are compiled when VCV Rack starts up in order to determine if they can be run. Scripts are then compiled again when a module is created - this is necessary to create a new engine. The side effect of this is that you can edit the file, delete a module and re-insert it to see if your edits worked as expected.

You can reload the script without re-patching all the cables by saving your patch as a whole and then pressing the "Revert patch" button.

## Getting JSFX scripts

JsusFX is distributed with some example Liteon scripts. https://github.com/asb2m10/jsusfx/tree/master/scripts/liteon.
I've included these scripts in the `res` folder of this plugin.

If you've got a copy of Reaper, you can copy the scripts supplied with Reaper from its data directory.

* `~/.config/REAPER/Effects/` on Linux

You can modify these scripts. This is necessary in some cases. For example, some scripts don't request a large enough screen to show all their graphics. If this is the case, find the line starting with `@gfx` in the script and increase the numbers there to get a bigger screen.

## Uses of this plugin

This plugin can be used to port your favourite Reaper effect into VCV, and to massively increase the effects available to VCV. You can also use JSFX to prototype an effect you want to create before you create a fully customized UI for your module. We can also share and distribute our own JSFX scripts just as we share and distribute patches.

## Tempo

Some plugins use the Tempo to do some calculation. To support this, every module has a "BPM" input in the top left. This takes a BPM as output by the `Clocked` module. Other formats may be added in the future.

**Example BPM Values:**

* 30 BPM = -2V
* 60 BPM = -1V
* 120 BPM = 0V
* 130 BPM = 0.115V
* 140 BPM = 0.222V
* 240 BPM = 1V

**Conversions:**

V = log(BPM/120, 2)
BPM = pow(2,V) * 120

## Inputs & CV Control

Inputs are divided by 5 before being sent to the JsusFX engine and outputs are multiplied by 5 before being given back to VCV Rack. This was done to make the VU meters show approximately the same audio values in the Scripts and native VCV modules. I assume that JSFX treats audio as a stream of values between -1 & 1, whereas VCV treats it more normally as between -5 & 5 (although there are no standards here).

Every parameter can be CV controlled. CV is expected to be a value between -5 & 5. A value at either end of this range will always be enough to take a parameter from its lowest value to its highest or vice-versa. For example, if a parameter knob can be between 0Hz and 5000Hz and it's manually set to 0Hz, a CV value of +5 (unattenuated) will modify the parameter to 5000Hz. If the control is manually set to 5000Hz, -5V of CV will bring it back to 0Hz. Values are clamped to the range of the parameters, CV cannot drive the parameters outside that range. Manually setting the control to 5000Hz and driving it with +5V of CV, will keep the setting at 5000Hz.

All CV inputs have an attenuverter associated with them. By default, the attenuverter is set to 0, meaning that the CV input will have no value. As is convention, the attenuverter can multiply the CV input between -1 & -1.

Values entered through turning the knobs and switches are always quantized to the nearest step value for the paramter. CV offsets are *not* quantized this way and allow smooth control. If a particular script doesn't support this, you'll have to constrain your CV values carefully.


## Performance

Although the scripts are written in a high level language, the engine that runs them is c++ and seems to work reasonably well, that said, depending on the script, they can get pretty heavy.

JSFX is different to VCV Rack in that it expects to work on a block of samples at a time wherease VCV always works on a single sample at a time. Because of this, samples are buffered up and then given to the engine in blocks of 64 - so there's a 64 sample latency through a JSFX module rather than the usual 1 sample latency. This is easily changed in code and most scripts will work just fine on blocks of 1 sample, however, Reaper says the minimum block size is 64, so I would expect some scripts to rely on that. Also, operating on blocks of 1 sample can significantly increase the CPU usage of the module, so for now, it's left as a block of 64. This may become configurable.

## Limitations

The strongest limitation comes from the JsusFX implementation. Not all JSFX instructions are available and some that are available are just there to let the script compile without actually doing anything. An example of this is `slider_next_chg`. It's available, the script will run but it won't do anything.

The next strongest limitation is graphics support. I've implemented a basic rendering engine that does some basic and text into SVG, but not everything is supported. There are some behavioural differences as well as outright bugs in how graphics are rendered. I've been through Reapers default plugins and done my best to support all of those. Don't expect great things from the graphics.

Finally, JSFX supports MIDI, file access, serialisation, etc. None of those things are supported in VCV Rack as yet, and probably never will be. (this is code for "I've no idea how to do it and it sounds hard").




