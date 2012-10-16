# x-acl

x-acl provides a lightweight and flexible access control list (ACL) implementation for privileges management. 
In general, an application may utilize such ACL's to control access to certain protected objects by other requesting objects.

---

## Required Packages

* g++/gcc *4.3 is the minimum version*
* GNU Make
* Boost *1.37 is the minimum version*

## Configuration Access Controls 

x-acl manage only from configuration file.

For example:

    [guest]
    view:news
    view:comments

Or:

    [guest]
    view:news       = allow
    view:comments   = allow

We created the role guest and resources view:news and view:comments
Each resource must has delimiter symbol :

If we want give role guest access for both resources we can write rule:

    [guest]
    view:*

Where symbol * means anything.

If you would deny access to resource you write:

    [guest]
    view:comments:add   = deny

## How to build

Linux:

    mkdir ~/src
    cd ~/src
    git clone https://github.com/AlexeyParhomenko/x-acl.git
    cd x-acl/Release
    make

Once this is done you'll see:

    Finished building target: x-acl
    
## How to use

After build you can execute the binary file

    ./x-acl
    
and see some options to control process.
To check access you can execute

    ./x-acl -c x-acl.example.conf -g guest -r view:wall:comment:28
    
You'll see:

    Access denied

Try other combination and make your rules.
Good luck! :)