####Fail2ban

Be sure to configure mail notifications if you plan to use them.
Found in jail.local -
```bash
# Destination email address used solely for the interpolations in
# jail.{conf,local,d/*} configuration files.
destemail = user@gmail.com

# Sender email address used solely for some actions
sender = admin@hostname

# E-mail action. Since 0.8.1 Fail2Ban uses sendmail MTA for the
# mailing. Change mta configuration parameter to mail if you want to
# revert to conventional 'mail'.
mta = mail

# Default protocol
protocol = tcp
```


Default fail2ban action set to `action = %(action_mwl)s`

These configurations can be used to activate the below jails within fail2ban -
```bash
[nginx-noproxy]

enabled  = true
port     = http,https
filter   = nginx-noproxy
logpath  = /var/log/nginx/access.log
maxretry = 2

[nginx-nohome]

enabled  = true
port     = http,https
filter   = nginx-nohome
logpath  = /var/log/nginx/access.log
maxretry = 2

[nginx-badbots]

enabled  = true
port     = http,https
filter   = nginx-badbots
logpath  = /var/log/nginx/access.log
maxretry = 2

[nginx-noscript]

enabled  = true
port     = http,https
filter   = nginx-noscript
logpath  = /var/log/nginx/access.log
maxretry = 6

[nginx-http-auth]

enabled  = true
filter   = nginx-http-auth
port     = http,https
logpath  = /var/log/nginx/error.log

[sshd]
# To use more aggressive sshd modes set filter parameter "mode" in jail.local:
# normal (default), ddos, extra or aggressive (combines all).
# See "tests/files/logs/sshd" or "filter.d/sshd.conf" for usage example and[Definition]
failregex = ^<HOST> -.*GET.*(\.php|\.asp|\.exe|\.pl|\.cgi|\.scgi)
ignoreregex = details.
#mode   = normal
enabled = true
port    = 22
logpath = %(sshd_log)s
backend = %(sshd_backend)s
```

The following filters are also included, which are required to exist within the `/etc/fail2ban/filter.d/` directory. All other jails within this configuration are provided with the default installation of fail2ban on Ubuntu.

```bash
# /etc/fail2ban/filter.d/nginx-noscript.conf
[Definition]

failregex = ^<HOST> -.*GET.*(\.php|\.asp|\.exe|\.pl|\.cgi|\.scgi)

ignoreregex =

```

```bash
# /etc/fail2ban/filter.d/nginx-nohome.conf
[Definition]

failregex = ^<HOST> -.*GET .*/~.*

ignoreregex =
```

```bash
# /etc/fail2ban/filter.d/nginx-noproxy.conf
[Definition]

failregex = ^<HOST> -.*GET http.*

ignoreregex =
```

To use these configurations, nginx must be running on the host. Run the commands below to apply them.
```bash
git clone https://github.com/shaunrd0/klips;
sudo cp klips/configs/fail2ban/jail.local /etc/fail2ban/jail.local;
sudo cp klips/configs/fail2ban/nginx* /etc/fail2ban/filter.d/;
sudo systemctl restart fail2ban;
sudo fail2ban-client status;
```
