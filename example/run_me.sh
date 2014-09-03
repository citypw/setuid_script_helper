#!/bin/sh

cd .. && make && cp setuid_script_helper ./example && cd -
chown root:shawn setuid_script_helper
chmod 750 setuid_script_helper
chmod u+s setuid_script_helper
chmod 750 2.sh
chown root:shawn 2.sh
chmod u+s 2.sh
