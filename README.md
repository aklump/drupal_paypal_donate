SUMMARY: Adds a block with various paypal donation options. This module will
create a block with paypal donation buttons of varied amounts linked to your
paypal account. It uses javascript, which degrades nicely, to make sure users
don't submit values less than or equal to zero. There is currently no reporting
or recording of donations either to the system or to a user's record. All of
that can be done through PayPal.


INSTALLATION:
* Download and unzip this module into your modules directory.
* Goto Administer > Site Building > Modules and enable this module.
* Configure the module from the settings page.
* Give the permission make donations to one or more roles.
* Enable the created block.
* Execute a test donation to make sure everything works.

Alternatively, use the force paypal url:
* After creating at least on block, you may ping: paypal-donate/donate/%/%
* The first argument is the block delta.
* The second is an optional donation amount, leave it blank for user input.


CONFIGURATION:
* Most customization can occur using css; there are several other customization
  and configuration options on the settings page for the module.


--------------------------------------------------------
CONTACT:
In the Loft Studios
Aaron Klump - Web Developer
PO Box 29294 Bellingham, WA 98228-1294
aim: theloft101
skype: intheloftstudios

http://www.InTheLoftStudios.com
