# JSFX plugins for VCV Rack

Caution: Extremely experimental. This plugin will probably kick your dog.

This plugin allows you to use JSFX plugins from the Reaper DAW as VCV Rack modules.

JSFX is Reaper's programming language, reference here: https://www.reaper.fm/sdk/js/js.php
This plugin uses JsusFX as its engine to interpret the langauge and do the real work: https://github.com/asb2m10/jsusfx
If a script isn't supported by JsusFX, it won't be supported in this plugin.

The plugin will create a module menu entry for every JSFX script it finds.
It does this by scanning for files in the `jsfx` directory, which you'll find directly next to your `plugins` directory.
The plugin will auto-generate a UI with all the knobs, inputs and outputs defined in the script.
Every knob also has a tunable CV input.

If a module supports graphics, a second module entry will be made which will include a screen to display the graphics.
All support is very basic at the moment, graphics support is doubly so.

