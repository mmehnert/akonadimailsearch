A small program that I created to have email address completion for notmuch via akonadi.

Usage: akonadimailsearch [search] 

    git clone https://github.com/mmehnert/akonadimailsearch

Install the development packages for kdepim on your system. Enter the cloned repository and create a build directory:

    mkdir build
    cd build
    cmake ..; make;

You will find the akonadimailsearch binary in the build/src directory. Copy it to ~/bin .

You can now add the following settings to your notmuch init file:

    (require 'notmuch-address)
    (setq notmuch-address-command "~/bin/akonadimailsearch")
    (notmuch-address-message-insinuate)


