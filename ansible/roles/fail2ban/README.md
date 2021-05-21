Fail2ban
=========

An ansible role for installing fail2ban with basic configuration options

Role Variables
--------------

`packages: [fail2ban]`
* A list of packages to install on the server

`ssh_port: 22`
 * The port SSH where is running on the remote server

`relay_host: "[sub.domain.com]:777"`
`sender_email: "senderemail@domain.com"`
 * The relay to route mail through, and a corresponding email to send as

`email: "email@domain.com"`
 * The email address to send alerts to when an IP is banned or jailed

`nginx_botsearch: "true"`
`nginx_http_auth: "true"`
`nginx_nobinary: "true"`
`nginx_nohome: "true"`
`nginx_noproxy: "true"`
`nginx_wplogin: "true"`
`nginx_noscan: "true"`
`nginx_noenv: "true"`
`nginx_noscript: "true"`
`sshd: "true"`
`sshd_badproto: "true"`
* Each of these variables are an existing fail2ban filter with a corresponding
bool to enable or disable them.


Dependencies
------------

Requires that postfix is configured to send email alerts
on behalf of the `sender_email` address.

Example Playbook
----------------

First, make sure all settings within `defaults/main.yml` are correct for your
server. All settings and their purposes are outline in the section above.

Create a new ansible play. You can name it whatever you want, but this
example play will simply be named `fail2ban.yml`.

```yml
---
- hosts: testserver
  become: yes
  roles:
  - fail2ban
```

Make sure the IP for `testserver` is correct in the `/etc/ansible/hosts` file -
```
[testserver]
123.123.123.123:22
```

Run the play!

```bash
ansible-playbook fail2ban.yml
```

License
-------

BSD

Author Information
------------------

Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0
