Postfix
=========

An ansible role to install and configure Postfix on a remote host.
This can be used to configure a server to send mail on your behalf.

Should you have any questions on basic Postfix configurations, see 
[Knoats - Configuring Postfix](https://knoats.com/books/linux-admin/page/configure-postfix#bkmrk-create-google-app-to)

Requirements
------------

None.

Role Variables
--------------

`packages: [mailutils, postfix]`
 * A list of packages to install on the server


`relay_host: "[sub.domain.com]:777"`
 * The relay to route mail through. Presumably, this could be GMail's -
  `[smtp.gmail.com]:587`
   
`email: "email@domain.com"`
 * The email address that Postfix will route mail through. Instead of 
   `root@SERVER_IP`, mail send with Postfix will use `email@domain.com` 
   as the sender
   
`sasl_passwd: "xxxxxxxxxxxxx"`
 * The sasl password generated for the email account we selected. 
    If you are unsure how to do this, see [Knoats - Configuring Postfix](https://knoats.com/books/linux-admin/page/configure-postfix#bkmrk-create-google-app-to)

Dependencies
------------

A list of other roles hosted on Galaxy should go here, plus any details in regards to parameters that may need to be set for other roles, or variables that are used from other roles.

Example Playbook
----------------

First, make sure all settings within `defaults/main.yml` are correct for your
server. All settings and their purposes are outline in the section above.

Create a new ansible play. You can name it whatever you want, but this
example play will simply be named `postfix.yml`.

```yml
---
- hosts: testserver
  become: yes
  roles:
  - postfix
```

Make sure the IP for `testserver` is correct in the `/etc/ansible/hosts` file -
```
[testserver]
123.123.123.123:22
```

Run the play!

```bash
ansible-playbook postfix.yml
```

License
-------

BSD

Author Information
------------------

Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0
