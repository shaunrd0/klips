# Following instructions at https://knoats.com/books/linux-admin/page/configure-postfix
sudo postmap /etc/postfix/sasl/sasl_passwd;
sudo chown root:root /etc/postfix/sasl/sasl_passwd /etc/postfix/sasl/sasl_passwd.db;
sudo chmod 600 /etc/postfix/sasl/sasl_passwd /etc/postfix/sasl/sasl_passwd.db;
