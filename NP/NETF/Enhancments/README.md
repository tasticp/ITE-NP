Enhancement number 1: HTTP web server & DNS
•	Server with a static IP address with its respective subnet mask, default gateway, and DNS
•	Used DNS Service with a created Domain name for the web server
•	Host an Interactive Web server that the other PCs can go to

Enhancement number 2: SSH for a Secure Remote Access to the Router
•	Setting a Minimum Length for Passwords
•	Setting a Banner to warn those Unauthorized
•	Setting Up Passwords
  o	Console line password
  o	Privilege password
  o	Time-out limits
    	To not leave open ports if the operator has left (inactivity)
    	Exec Timeout 10 minutes (in vty 0 4)
    	Exec Timeout 5 minutes (in console line)
  o	Attempt limits before time out
    	Login lock for 1 min (60 secs) after 10 failed attempts
•	Set up SSH tunnel for Encrypted Remote Router Managements
  o	SSH is more secure than telnet as telnet is plain-text while ssh is encrypted

Enhancement number 3: Wider Network with wireless
•	A work from home type situation where remote users can reach HQ and Branch
•	Extra Routers, Cloud, 2 Laptop, Modem, Wireless Router
